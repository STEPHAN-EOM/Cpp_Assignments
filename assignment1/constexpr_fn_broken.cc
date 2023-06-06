/**
 * @file constexpr_fn_broken.cc
 * @brief  5614 Assignment 1 2023. Used for Q7 c. 
 * 		This is a version of constexpr_fn.cc with some slight changes. Why will it not compile?
 * 
 * @author Chanho Eom
 * @date 14 February 2023
 */

#include <iostream>
#include <random>

/**
 * @brief Function to return the square of a number
 *
 * @param[in] n The number that we want to square 
 *
 * @return n*n The input value squared
 */
//constexpr
constexpr double square(const double n){
	return n*n;
}

int main()
{
	// std::random_device is basically an abstraction that should return an integer from
	// a random hardware device if it available on the system. But, depending on the
	// implementation it might actually be a PRNG
	std::random_device rd;

	// dist will transform the integer passed in to a double on [0,1)
	std::uniform_real_distribution<> dist {0, 1};

	constexpr double x {square(1.234)};
	constexpr double y {square(dist(rd))};
	std::cout << "1.234 squared = " << x  << '\n'
		<< "random squared = " << y  << std::endl;
	
	return 0;
}
