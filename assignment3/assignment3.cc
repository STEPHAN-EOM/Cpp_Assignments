/**
* @file assignment3.cc
* @brief Assignment 3 for 5614 C++ programming 2023
*	You will write your own templated matrix class and associated functions.
*	I also include some tests you can use for some checking.
* @author Chanho Eom
* @date 24-Mar-2023
*/
#include <iostream>	
#include "matrix_operations.h"
#include "matrix.h"

int main()
{
	try {
		HPC::Matrix <double> const M1 {std::string {"matrix_4x4.txt"} };
		HPC::Matrix <double> const V1 {std::string {"vector_4x1.txt"} };
		HPC::Matrix <int> const M2 {std::string {"matrix_4x3.txt"} };
		HPC::Matrix <int> const M3 {std::string {"matrix_4x4_int.txt"} };

		/// Use the below as some ideas for your testing.
		/*
		 *                // Test 0: This should be caught by Number Concept at compile time if uncommented
		 *                HPC::Matrix <std::string> V2 {std::string {"vector.txt"}};
		 *
		 * 		  // Test 1:  Should throw error as file does not exist
		 *		  HPC::Matrix <double> X1 {std::string {"matrix_10x10.txt"}};
		 *
		 *                // Test 2: This should throw an out-of-range error for operator()
		 *                HPC::Matrix <double> E {10,10};
		 *                E(99,1) = 1.0;
		 *
		 *                // Test 3: Should throw error due to incompatible dimensions
		 *                std::cout << "M1+M2:\n" << M1+M2  << std::endl;
		 *
		 *                // Test 4: Should throw error due to incompatible dimensions
		 *                std::cout << "V1xM1:\n" << V1*M1 << '\n';
		 *
		 *                // Test 5: Should give error due to non-square matrix
		 *                HPC::Matrix<int> I2{M2.get_num_cols(), M2.get_num_rows()};
		 *                HPC::identity(I2);
		 * 		
		 * 		  // Test 6. Should give compilation error due to narrowing
		 * 		  HPC::Matrix<int> X2{-10, 10};
		 *
		 *		  // Test 7. Should throw a std::bad_alloc
		 *		  HPC::Matrix<int> X3{100'000, 100'000};
		 *
		 * 	          // Test 8. Should throw an error as not enough data in file
		 * 		  HPC::Matrix<double> X4{std::string {"matrix_4x4_corrupt.txt"} };
		 *	
		 * 		  // Test 9. not possible for different numbers of rows
		 *		  HPC::Matrix<double> X5{ std::string{"matrix_5x5.txt"}};
		 *		  gaussjordan(M1, X); 	
		 *
		 * 		  // Test10. Need square matrix for GJ to calculate inverse
		 * 		  gaussjordan(M2, V1);
		 */

		// Print input data to screen
		std::cout << "\nM1:\n" << M1 << '\n';
		std::cout << "\nV1:\n" << V1 << '\n';
		std::cout << "\nM2:\n" << M2 << '\n';
		std::cout << "\nM3:\n" << M3 << '\n';

		// Will call Copy constructor
		auto M1copy {M1};
		// Should call move constructor
		auto M1move {std::move(M1copy)};

		// Will call operator+
		std::cout << "\nM1+M3:\n" << M1+M3  << std::endl;

		// Will call operator*
		std::cout << "\nM1xV1:\n" << M1*V1 << '\n';
		std::cout << "\nM1xM2:\n" << M1*M2 << '\n';


		// Find inverse of M1
		HPC::Matrix<double> I{M1.get_num_rows(), M1.get_num_cols()}; 	// Construct a rows x cols Matrix
		HPC::identity(I); 						// Make the above into an identity matrix
		auto M1inv {gaussjordan(M1, I)};
		std::cout << "\nM1 Inverse:\n"  << M1inv; 			// Calculate and print M^(-1)
		std::cout << "\nCheck M1*M1inv:\n" << M1inv*M1;

		// Solve M1*x = V1 for x
		auto x {gaussjordan(M1, V1)};
		std::cout << "\nSolve M1*x = V1\n"  << x;
		std::cout << "\nCheck M1*x:\n"  << M1*x;

		// Do the same for M3 (Matrix of ints)
		HPC::Matrix<int> I3{M3.get_num_rows(), M3.get_num_cols()};
		HPC::identity(I3);
		auto M3inv {gaussjordan(M3, I3)};
		std::cout << "\nM3: Inverse:\n"  << M3inv;
		auto x2 {gaussjordan(M3, V1)};
		std::cout << "\nSolve M3*x = V1\n"  << x2;
		std::cout << "\nCheck M3*x:\n"  << M3*x2;


	}catch(const std::out_of_range& outofrange) { 	// Out of range error
		std::cerr << "Out of range error: " << outofrange.what() << '\n';
	}catch(const std::string& str){ 		// Catch a std::string
		std::cerr << "Exception string caught: " << str << '\n';
	}catch(const char * str) { 			// Catch a C-style string
		std::cerr << "Exception string caught: " << str << '\n';
	}catch(std::bad_alloc & exception){ 
		std::cerr << "bad_alloc detected: " << exception.what(); 
	}catch(...){
		std::cerr << "Unknown error caught\n";
	}

	return 0;
}
