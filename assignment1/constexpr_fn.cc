/**
 * @file constexpr_fn.cc
 * @brief  5614 Assignment 1 2023. Used for Q7 c. 
 * 	Feel free to play around with the constexpr and const to see what compiles and what does not compile
 * 	e.g. does it compile if we have constexpr double square(constexpr double n)
 * 	You can read a bit more here https://isocpp.org/blog/2013/01/when-does-a-constexpr-function-get-evaluated-at-compile-time-stackoverflow
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

	const double x {square(1.234)};
	const double y {square(dist(rd))};
	std::cout << "1.234 squared = " << x  << '\n'
		<< "random squared = " << y  << std::endl;
	
	return 0;
}
