/**
 * @file hpc_concepts.h
 * @brief File containing definition of "Number" concept to be used in Assignment 3 of 5614
 * @author Chanho Eom
 * @date 24-Mar-2023
 */

#ifndef HPC_CONCEPT_H_HVOQ9YUB
#define HPC_CONCEPT_H_HVOQ9YUB

// Define a Concept called Number
// Limit types to those that support standard arithmetic operators.
template <typename T>
concept Number = requires(T a, T b){
	a+b;
	a-b;
	a*b;
	a/b;
	a+=b;
	a-=b;
	a*=b;
	a/=b;
};

#endif /* end of include guard: HPC_CONCEPT_H_HVOQ9YUB */
