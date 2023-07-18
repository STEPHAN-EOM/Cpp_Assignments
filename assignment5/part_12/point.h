/**
 * @file point.h
 * @brief Class definition for Point class needed for 5614 Assignment 5.
 * 		Write the necessary function definitions in point.cc
 * @author Chanho Eom
 * @date 16-May-2023
 */
#ifndef POINT_H_OMJSZLDH
#define POINT_H_OMJSZLDH
#include <iostream>
#include <iomanip>
#include <vector>
#include <fstream>
#include <algorithm>


/**
 * @brief Simple structure to store coordinates of a point on the grid
 */
struct Point {
    double x;                                      //!< x-coordinate 
    double y;                                      //!< y-coordinate 

    Point() = default;
    Point(double inx, double iny) : x{inx}, y{iny}{};  //!< Constructor

    // Write the definition of this in point.cc
    bool operator==(const Point & rhs); 
};

/**
 * @brief Overloading output stream operator for a Point.
 * The operator should simply print the x and y coordinates of Point "in"
 *
 * @param os    Reference to output stream
 * @param in    Reference to Point which we want to print.
 *
 * @return      Reference to output stream
 */
inline std::ostream & operator<<(std::ostream & os,const Point & in){
    os << std::fixed << std::setw(9) << in.x << ", " << std::setw(9) << in.y;
    return os; 
}

// Write the definition of the 3 below functions in point.cc
void write_to_file(std::string fn, std::vector<Point> pts);
bool cross_prod(Point p1, Point p2, Point p3);
void sort_points(std::vector<Point>& points);

#endif /* end of include guard: POINT_H_OMJSZLDH */
