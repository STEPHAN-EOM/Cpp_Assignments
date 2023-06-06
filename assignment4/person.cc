/**
 * @file person.cc
 * @author Chanho Eom
 * @date 4-May-2023
 */

#include <iostream>
#include "person.h"
#include <cmath>
#include <random>

// @brief Overloading constructor
Person::Person(Point s, std::shared_ptr<Params> p) : current_location{s}, original_location{s}, params{p} {

// Deactivate the following line to print the result briefly
//std::cout << "Person constructor is created" << std::endl;
}

// @brief Printing the current location point from p
// @params os	output stream
// @params p	person whom we want print the his/her current location
// @return 	output stream
std::ostream& operator<<(std::ostream& os, const Person& p){

os << "Current location(x, y) = " << "("<< p.current_location.x << ", " << p.current_location.y << ")"  << std::endl;
return os;
}

// @brief Ramdomly propose a move for each square and accept or reject the move with probability
void Person::propose_move() {

int x_left{current_location.x}, x_right{current_location.x};
int y_up{current_location.y}, y_down{current_location.y};

int move_x, move_y;
double prob;

std::cout << "x_left = " << x_left << ", x_right = " << x_right << ", y_up = " << y_up << ", y_down = " << y_down << std::endl;


double r1;	// r1 = sqrt((old_x - home_x)^2 + (old_y - home_y)^2);
double r2;	// r2 = sqrt((new_x - home_x)^2 + (new_y - home_y)^2);
double k = params->spring_constant;

// Set the grid of moving
if (current_location.x > 0)
x_left --;
if (current_location.x < params->xdim -1)
x_right ++;
if (current_location.y > 0)
y_up--;
if (current_location.y < params->ydim -1)
y_down++;


// Possible location after moving
std::uniform_int_distribution<> xdis{x_left, x_right};
std::uniform_int_distribution<> ydis{y_up, y_down};

move_x = xdis(gen);
move_y = ydis(gen);

int old_x = current_location.x - original_location.x;
int old_y = current_location.y - original_location.y;
int new_x = move_x - original_location.x;
int new_y = move_y - original_location.y; 

// Accept of Reject
r1 = std::sqrt(pow(old_x, 2) + pow(old_y, 2));
r2 = std::sqrt(pow(new_x, 2) + pow(new_y, 2));

prob = exp(-k * (pow(r2, 2) - pow(r1, 2)));
std::uniform_real_distribution<> p_accept(0, 1);

// If r2 < r1, accept the move
// Otherwise, accept the move with probability
if (r2 <= r1) {
current_location.x = move_x;
current_location.y = move_y;
} else if (p_accept(gen) < prob) {
current_location.x = move_x;
current_location.y = move_y;
}
}

// @brief Set the member bool infected to true for the person and randomly assign the days_to_death variable for that person.
// @brief Copy the time_to_recovery from the params class to the member variable days_to_recovery
void Person::infect() {
infected = true;
std::uniform_int_distribution<> death_dis(0, 365);
days_to_death = death_dis(gen);
days_to_recovery = params->time_to_recovery;
}

