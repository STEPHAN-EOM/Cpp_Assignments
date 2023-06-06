/**
 * @file grid.cc
 * @author Chanho Eom
 * date 5 May 2023
 */

#include <iostream>
#include "grid.h"

// @brief Overloading constructor
Grid::Grid(int x, int y, int z) : width{x}, height{y}, orig_population{z}{

data.resize (static_cast<std::vector<int>::size_type>(width));
for (long unsigned int i = 0; i < static_cast<std::vector<int>::size_type>(width); ++i){

data[i].resize(static_cast<std::vector<int>::size_type>(height));
}}

// Simple clear the list at each site in between each turn
void Grid::reset_grid() {

for (long unsigned int i = 0; i < static_cast<std::vector<int>::size_type>(width); ++i){
for (long unsigned int j = 0; j < static_cast<std::vector<int>::size_type>(height); ++j){

data[i][j].clear();
}}}


// @brief Interates through the population and checks the current location of each
// @brief It update the corresponding Grid data container so that it holds the index of the Person for the corresponding coordinates.
// @param pop	vector of Person
void Grid::update_grid_counts(std::vector<Person>& pop){

reset_grid();

currently_infected = 0;

for (long unsigned int i = 0; i < pop.size(); ++i){
data[static_cast<std::vector<int>::size_type>(pop[i].current_location.x)][static_cast<std::vector<int>::size_type>(pop[i].current_location.y)].push_back(i);

if (pop[i].infected)
currently_infected ++;
}}


// @brief Print the grid to screen with the counts of the number of Person at each site
// @param 	os: output stream
// @param 	in: Grid that we want to print
// @result	Reference to output stream
std::ostream& operator<< (std::ostream & os, Grid & in){

for (long unsigned int i = 0; i < static_cast<std::vector<int>::size_type>(in.width); ++i){
for (long unsigned int j = 0; j < static_cast<std::vector<int>::size_type>(in.height); ++j){
os << " " << in.data[i][j].size() << "";}
os << "\n";}
return os;}


// @brief Update the health status of each Person
// @param 	pop: vector of person
void Grid::update_health_status(std::vector<Person>& pop) {

for (auto it = pop.begin(); it != pop.end();) {
if (it->infected){
it->days_to_recovery--;
it->days_to_death--;

if (it->days_to_recovery == 0){
it->immune = true;
it->infected = false;
--currently_infected;
++recovered;
++it;
} else if (it->days_to_death <= 0){
// return the iterator of next element. No using it++ here
pop.erase(it);
--currently_infected;
++dead;
} else{
++it;}} else{
++it;}}
}


// @brief Update the configuration after all of the moves between grid sites have been made
// @param 	pop
void Grid::update_configuration(std::vector<Person>& pop){

// Newly infected person can not immediately infect another in the same turn
update_grid_counts(pop);

std::uniform_real_distribution<> infdis(0, 1);

std::vector<long unsigned int> newly_inf(pop.size());

// 0 = Not the new infected. 1 = the new infected
std::fill(newly_inf.begin(), newly_inf.end(), 0);

for (long unsigned int i = 0; i < pop.size(); ++i){

if (pop[i].infected){
if (newly_inf[i] == 0){

long unsigned int num_people = data[static_cast<std::vector<int>::size_type>(pop[i].current_location.x)][static_cast<std::vector<int>::size_type>(pop[i].current_location.y)].size();

if (num_people >= 2){

for (long unsigned int j = 0; j < num_people; ++j){
long unsigned int idx_people = static_cast<long unsigned int>(data[static_cast<std::vector<int>::size_type>(pop[i].current_location.x)][static_cast<std::vector<int>::size_type>(pop[i].current_location.y)][j]);

if (!pop[idx_people].infected && !pop[idx_people].immune && newly_inf[idx_people] == 0 && infdis(gen) <= pop[idx_people].params->transmission_prob) {

infect_on_grid(pop[idx_people]);
newly_inf[idx_people] = 1;
}
}}}}}

update_health_status(pop);
}


// @brief Print the statistics at each turn to a file. When the function is called, it should append the appropriate stats to the end of the input file.
// @params 	in: filename 
// @params 	i: interation count
void Grid::print_stats(std::string in, int i){

std::ofstream file;
file.open(in, std::ios_base::app);	// Append instead of overwiting

if (!file){
std::cerr << "Error for opening the file" << std::endl;}

// Contents: iteration count | population | currently infected | recovered | dead| can not be catched |
if (file.is_open()){
file << i << ", " << orig_population << ", " << currently_infected << ", " << recovered << ", " << dead << ", " <<orig_population - currently_infected - recovered - dead << std::endl;}
}


