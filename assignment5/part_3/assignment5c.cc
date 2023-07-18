/**
 * @file assignment5c.cc
 * @brief Main function for 5614 Assignment 5 Part 3.
 * @author C. Eom
 * @date 17-May-2023
 */
#include <iostream>
#include <vector>
#include <random>
#include <functional>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <chrono>
#include <future>

#include "point.h"
#include "ConvexHull.h"

 // Use below two lines to seed from random device
std::random_device rd;
std::default_random_engine rng{ rd() };
// Use the below with some seed for a fixed seed
// std::default_random_engine rng {1234};

const auto policy = std::launch::async;
// const auto policy = std::launch::deferred;

int main(void)
{
// Initialize Boost.MPI
boost::mpi::environment env;
boost::mpi::communicator world;

if (world.rank() == 0) {
// You can change number of points if you want for timing purposes
//const int n {10'000'000};
const int n {50000};


std::vector<Point> points(n);
auto gaussian_rv = std::bind(std::normal_distribution<> {0, 1}, std::ref(rng));


// Assign random coordinates to each point.
for (auto& p : points) {
p.x = gaussian_rv();
p.y = gaussian_rv();
}

// sort Points in order of increasing x-coordinate. You wrote this function in points.cc
sort_points(points);

// Construct a convex hull from these points. You wrote this constructor
ConvexHull CH{ std::begin(points), std::end(points) };

auto start = std::chrono::steady_clock::now();
CH.generate_hull();     // Generate hull. You wrote this function
auto end = std::chrono::steady_clock::now();

std::cout << "Serial time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms\n\n";

write_to_file(std::string("points_mpi.txt"), CH.get_points());     // Write all points to file
write_to_file(std::string("serial_mpi.txt"), CH.get_hull());         // Write hull points to file
     
         /*
          * Create three ConvexHull objects below here.
          * ConvexHull CH_left from the leftmost one-third of points from CH above
          * ConvexHull CH_mid from the middle one-third of points from CH above
          * ConvexHull CH_right from the rightmost one-third of points from CH above
          */
    
int third = points.size() / 3;

std::vector<Point> points_rank0(std::begin(points), std::begin(points) + third);
            std::vector<Point> points_rank1(std::begin(points) + third, std::begin(points) + third * 2);
std::vector<Point> points_rank2(std::begin(points) + third * 2, std::end(points));

start = std::chrono::steady_clock::now();

world.send(1, 0, points_rank1);
world.send(2, 1, points_rank2);
ConvexHull CH_left{ points_rank0.begin(), points_rank0.end() };
CH_left.generate_hull();

ConvexHull CH_mid{ points_rank1.begin(), points_rank1.end() };
ConvexHull CH_right{ points_rank2.begin(), points_rank2.end() };

std::vector<Point> hull_mid;
std::vector<Point> hull_right;

world.recv(1, 2, hull_mid);
world.recv(2, 3, hull_right);

CH_mid.movehull(std::move(hull_mid));
CH_right.movehull(std::move(hull_right));

write_to_file(std::string("left_hull_mpi.txt"), CH_left.get_hull());
write_to_file(std::string("mid_hull_mpi.txt"), CH_mid.get_hull());
write_to_file(std::string("right_hull_mpi.txt"), CH_right.get_hull());

CH_left.merge_to_right(CH_mid);
write_to_file(std::string("after_first_merge_mpi.txt"), CH_left.get_hull());

CH_left.merge_to_right(CH_right);   // Merge other hull into CH_right

write_to_file(std::string("after_second_merge_mpi.txt"), CH_left.get_hull());

end = std::chrono::steady_clock::now();
std::cout << "Parallelised time " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms\n\n";


}else if (world.rank() == 1) {
std::vector<Point> points_mid;
world.recv(0, 0, points_mid);
ConvexHull CH_rank1{ points_mid.begin(), points_mid.end()};
CH_rank1.generate_hull();
std::vector<Point> hull_rank1 = CH_rank1.get_hull();
world.send(0, 2, hull_rank1);
}else if (world.rank() == 2) {
std::vector<Point> points_right;
world.recv(0, 1, points_right);
ConvexHull CH_rank2{ points_right.begin(), points_right.end() };
CH_rank2.generate_hull();
std::vector<Point> hull_rank2 = CH_rank2.get_hull();
world.send(0, 3, hull_rank2);
}

return 0;
}
