/**
 * @file assignment4b.cc
 * @brief Main function for second part of Assignment 4
 * @author Chanho Eom
 * @date 5 May 2023
 */
#include <iostream>
#include <vector>

#include "assignment4.h"
#include "person.h"
#include "grid.h"

std::default_random_engine gen(4321);


int main(int argc, char *argv[])
{

    const int NUM_POPULATION {10000};
    const int NUM_INITIAL_INFECTED {100};
    auto p = std::make_shared<Params>();

try {
    // If more than one argument, read second argument as spring constant
    // For those that did not take 5613, I will go over this briefly in lecture
    if(argc>1){
	if(sscanf(argv[1],"%lf", &(p->spring_constant))!=1){
	    throw "Error reading from argv[1]";
	}
    }
    // Create object of type Grid
    Grid grid(p->xdim, p->ydim, NUM_POPULATION);

    // Vector of Persons.
    std::vector<Person> population;

    // Create name for output file
    std::ofstream f1;
    std::stringstream fname;
    fname << p->xdim << "x" << p->ydim << "_p" << NUM_POPULATION << "_i"<< NUM_INITIAL_INFECTED << "_k" <<p->spring_constant  << "_d" << p->death_percentage << "_t" << p->transmission_prob << ".txt";

    // Open exisiting file if it exists and truncate it.
    f1.open(fname.str(), std::ios::trunc);
    if(f1.is_open()){
	f1.close();
    }

    // Two uniform integer distributions. One for each dimension
    auto uix = std::uniform_int_distribution<>(0,p->xdim-1);
    auto uiy = std::uniform_int_distribution<>(0,p->ydim-1);

    // Create Person objects at randomly generated coordinates.
    for (int i = 0; i < NUM_POPULATION; i++) {
	population.emplace_back(Point{uix(gen), uiy(gen)}, p);
    }

    for (unsigned int i = 0; i < NUM_INITIAL_INFECTED; i++) {
	grid.infect_on_grid(population[i]); 
    }
    // Update the status of population on Grid
    grid.update_configuration(population);

    int i=0;
    grid.print_stats(fname.str(), i);
    while(grid.still_infected()){
	// Uncomment line below to print grid to screen
	//	std::cout << grid << '\n';
	for(auto it = population.begin(); it!= population.end(); ++it){
	    it->propose_move();
	}
	grid.update_configuration(population);
	grid.print_stats(fname.str(), i);
	++i;
    }

    // Uncomment line below to print grid to screen
    //std::cout << grid << '\n';

}catch (std::exception& e){
std::cerr << "Exception caught: " << e.what() << "\n";
}catch (const char* st){
std::cerr << "Exception caught: " << st << "\n";
}catch (...){
std::cerr << "Unknown Exception caught\n";
}


return 0;
}
