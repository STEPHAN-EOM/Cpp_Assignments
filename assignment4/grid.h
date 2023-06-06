/**
 * \file grid.h
 * \brief File to hold class definition for Grid class
 * \author R. Morrin
 * \version 3.0
 * \date 2022-03-28
 */
#ifndef GRID_H_XXELF1GY
#define GRID_H_XXELF1GY

#include <iostream>
#include "assignment4.h"
#include "person.h"
#include <iomanip>

/**
 * \brief  Class to represent a Grid
 */
class Grid
{
    public:
	Grid (int x, int y, int z);

	/*
	 * Implement the rule of 5 defaults here
	 */


	// Public member function declarations
	void update_configuration(std::vector<Person> & pop);
	void print_stats(std::string in, int i);

	friend std::ostream& operator<< (std::ostream & os, Grid & in);


	/**
	 * \brief This function will cause a Person to be marked as "infected" and increment the corresponding grid counter
	 *
	 * \param p  Person to infect.
	 */
	void infect_on_grid(Person & p){
	    p.infect();
	    ++currently_infected;
	}

	/**
	 * \brief Simple function to determine whether there are any Persons still infected on the grid
	 *
	 * \return  true if infected people remain on the grid
	 */
	bool still_infected(){
	    return(currently_infected>0);
	}

    private:
	void reset_grid();
	void update_grid_counts(std::vector<Person> & pop);
	void update_health_status(std::vector<Person> & pop);
	int width; 		//!< Width of the grid. i.e. number of sites in x direction	
	int height; 		//!< Height of thei grid. i.e. number of sites in y direction
	int orig_population; 	//!< Number of people on grid at start of simulation
	std::vector<std::vector<std::vector<int>>> data; //!< Store locations as vector-of-vectors. Each location has vector of Persons

	int currently_infected = 0; 	//<! Holds number of currently infected Persons
	int dead = 0; 			//<! Holds number of dead Persons
	int recovered = 0; 		//<! Holds number of recovered Persons
};

#endif /* end of include guard: GRID_H_XXELF1GY */
