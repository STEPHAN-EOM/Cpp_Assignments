/**
 * @file matrix_operations.h
 * @brief Contains function declaration for a function to perform Gauss-Jordan elimination.
 * @author Chanho Eom
 * @date 26-Mar-2023
 */
#ifndef MATRIX_OPERATIONS_H_A4QKSOWJ
#define MATRIX_OPERATIONS_H_A4QKSOWJ

#include "matrix.h"
#include "hpc_concepts.h"

template <Number T, Number U>
HPC::Matrix<double> gaussjordan(HPC::Matrix<T> const& A, HPC::Matrix<U> const& B);


#endif /* end of include guard: MATRIX_OPERATIONS_H_A4QKSOWJ */
