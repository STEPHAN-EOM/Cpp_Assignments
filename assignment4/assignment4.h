/**
 * @file assignment4.h
 * @brief Header file containing some structures for assignment4
 * @author Chanho Eom
 * @date 4-May-2023
 */
#ifndef ASSIGNMENT4_H_BAPBFPZN
#define ASSIGNMENT4_H_BAPBFPZN

#include <random>
#include <fstream>
#include <iostream>

extern std::default_random_engine gen;

/**
 * @brief Structure to hold parameters needed by program
 */
struct Params{
    int xdim 			= 100;   	//!< width of the grid
    int ydim 			= 100; 		//!< height of the grid
    double spring_constant   	= 0.5; 		//!< "Spring constant" which controls attraction to "home". See assignment document.
     
    int time_to_recovery     	= 14; 		//!< Number of days until a person recovers. This will be set to a constant
    double death_percentage    	= 0.2; 		//!< Percentage of infected people who die before time_to_recovery
    double transmission_prob 	= 0.2;  	//!< Probability that a sick person will infect another person at same grid site on each iteration.
};

/**
 * @brief Simple structure to store coordinates of a point on the grid
 */
struct Point {
    int x; 					//!< x-coordinate 
    int y; 					//!< y-coordinate 
};


/**
 * @brief Overloading output stream operator for a Point.
 * The operator should simply print the x and y coordinates of Point "in"
 *
 * @param os 	Reference to output stream
 * @param in 	Reference to Point which we want to print.
 *
 * @return  	Reference to output stream
 */

inline std::ostream & operator<<(std::ostream & os,const Point & in){

os << in.x << ", " << in.y;
return os;
}


#endif /* end of include guard: ASSIGNMENT4_H_BAPBFPZN */
