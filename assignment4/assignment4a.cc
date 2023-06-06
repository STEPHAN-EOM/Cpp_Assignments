/**
 * @file assignment4a.cc
 * @brief Assignment 4 for 5614. First part
 * Plot the path of a person following a modified "random walk" on a grid.
 * @author Chanho Eom
 * @date 4 May 2023
 */

#include <iostream>

#include "assignment4.h"
#include "person.h"


// Need to have RNG as global variable.
std::default_random_engine gen(4321);


int main(int argc, char *argv[])
{
    const int DIM {10};
    const int NUM_TURNS{100};

    auto p = std::make_shared<Params>();
    p->xdim = DIM;
    p->ydim = DIM;
    Point home {5,5};

 	/*
	 * Add a try catch block
	 */
try{
	// If more than one argument, read second argument as spring constant
	if(argc>1){
	    if(sscanf(argv[1],"%lf", &(p->spring_constant))!=1){
		throw "Error reading from argv[1]";
	    }
	}

	// Create a person object
	Person A {home, p};

	std::cout << A << '\n';
	// Evolve the system for NUM_TURNS steps
	for(auto i = 0; i< NUM_TURNS; ++i){
	    A.propose_move();
	    std::cout << A << '\n';
	}
}catch (std::exception& e){
std::cerr << "Exception caught: " << e.what() << "\n";
}catch (const char* st){
std::cerr << "Exception caught: " << st << "\n";
}catch (...){
std::cerr << "Unknown Exception caught \n";
}

return 0;
}
