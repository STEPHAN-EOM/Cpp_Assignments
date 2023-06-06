/**
 * @file assignment2a.cc
 * @author Chanho Eom
 * @date 28 Feb 2023
 */

#include <iostream>
#include <iomanip>

// Use this, and std::numbers::pi if you have C++20
//#include <numbers>

// Use this if you don't have C++20
#include <cmath>
const double A = M_PI;


/**
 * @brief Shape struct for assignment2a. This will be a base struct you 
 * 	can derive the Cube and Cylinder structs from. You don't need to change this struct.
 */
struct Shape
{
	Shape () 			= delete; 	// Delete default constructor 
	// Overloaded Constructor
	Shape (double v, double sa) : volume {v}, surface_area{sa} {
		std::cout << "Constructing Shape with volume = " << volume 
			<< " and surface area = " << surface_area << std::endl; 
	} 	
	// Destructor
	~Shape () {
		std::cout << "Destroying Shape with volume = " << volume
			<< " and surface area = " << surface_area << std::endl; 
	}

	Shape(const Shape&) 		= default; 	// Copy constructor
	Shape(Shape&&) 			= default; 	// Move constructor. Will actually be the same as copy for this class

	// Delete assignment operations
	Shape& operator=(const Shape &) = delete;
	Shape& operator=(Shape &&) 	= delete;

	// Member variables. 
	const double volume; 		//!< Holds the volume of the Shape
	const double surface_area; 	//!< Holds surface area of the Shape
};

// TODO:
// (1) Write struct Cube which inherits from Shape. It will have a const member variable "side"
// (2) Write struct Cylinder which inherits from Shape. It will have const member variables "radius" and "height"


/**
 * @name: struct Cube
 * @param: double side l
 * @brief: sub-struct of Shape
 * @outcome: Volume and Surface Area
 * */
struct Cube : public Shape{

// Constructor and define volume and surface area by using a member variable
Cube (double l) : Shape{l * l * l, 6 * l * l}, side{l} {
	std::cout << "Constructing Cube with side = " << side << std::endl;  
}

// Destructor
~Cube () {
	std::cout << "Destroying Cube with side = " << side  << std::endl;
}

// Const Member Variable of Cube
const double side;
};


/**
 * @name: struct Cylinder
 * @param: double radius r, double height h
 * @brief: sub-struct of Shape
 * @outcome: Volume and Surface Area
 * */
struct Cylinder : public Shape{

// Constructor and define volume and surface area by using member variables
Cylinder (double r, double h) : Shape{A * r * r * h, (2 * A * r * h + 2 * A * r * r)}, radius{r}, height{h} {
	std::cout << "Constructing Cylinder with radius = " << radius
		  << " and height = " << height << std::endl;
}

// Destructor
~Cylinder () {
	std::cout << "Destroying Cylinder with radius = " << radius
		  << " and height = " << height << std::endl;
}

// Const Member Variables of Cylinder
const double radius;
const double height;
};




/// END: You shouldn't need to edit below here.

int main()
{
	const int w1{26}, w2{10}; 	// For formatting output
	std::cout << std::fixed << std::setprecision(3);
	
	// Cube {side_length}
	const Cube cube {1.2};
	std::cout<<std::setw(w1) << std::left << "\nSide of cube:"       << std::setw(w2) << std::right << cube.side         << '\n' 
		<< std::setw(w1) << std::left << "Volume of cube:"       << std::setw(w2) << std::right << cube.volume       << '\n' 
		<< std::setw(w1) << std::left << "Surface area of cube:" << std::setw(w2) << std::right << cube.surface_area << "\n\n\n";

	// Cylinder {radius, height}
	const Cylinder cylinder {3.4, 5.0};
	std::cout<<std::setw(w1) << std::left << "\nHeight of cylinder:"     << std::setw(w2) << std::right << cylinder.height       << '\n' 
		<< std::setw(w1) << std::left << "Radius of cylinder:"       << std::setw(w2) << std::right << cylinder.radius       << '\n' 
		<< std::setw(w1) << std::left << "Volume of cylinder:"       << std::setw(w2) << std::right << cylinder.volume       << '\n' 
		<< std::setw(w1) << std::left << "Surface area of cylinder:" << std::setw(w2) << std::right << cylinder.surface_area << "\n\n\n";

	return 0;
}
