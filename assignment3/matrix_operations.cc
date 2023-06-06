/**
 * @file: matrix_operations.cc 
 * @author: Chanho Eom
 * @date: 26-Mar-2023
 * */

#include "matrix.h"
#include "hpc_concepts.h"
#include "matrix_operations.h"

/**
 * @function: Gauss Jordan Elimination
 * @input: Matrix A, Identity Matrix I
 * @output: Inverse Matrix of A
 * */
template <Number T, Number U>
HPC::Matrix<double> gaussjordan(HPC::Matrix<T> const& A, HPC::Matrix<U> const& B){

// Check that A is a square matrix
if (A.get_num_rows() != A.get_num_cols()) {
throw std::invalid_argument("Matrix A must be a square matrix");}

// Check the size of Matrices of A, B
if (A.get_num_rows() != B.get_num_rows()) {
throw std::invalid_argument("Matrices A and B must have the same number of rows");}

// Create an augmented matrix with A, B
HPC::Matrix<double> AB(A.get_num_rows(), A.get_num_cols() + B.get_num_cols());
for (std::size_t i = 0; i < A.get_num_rows(); ++i) {
for (std::size_t j = 0; j < A.get_num_cols(); ++j) {
AB(i, j) = static_cast<double>(A(i, j));}
for (std::size_t j = 0; j < B.get_num_cols(); ++j) {
AB(i, A.get_num_cols() + j) = static_cast<double>(B(i, j));
}}

// Perform Gaussian Elimination on the augmented matrix
for (std::size_t i = 0; i < AB.get_num_rows(); ++i) {
std::size_t pivot_row = i;
double max_value = std::abs(AB(i, i));
for (std::size_t j = i + 1; j < AB.get_num_rows(); ++j) {
double value = std::abs(AB(j, i));
if (value > max_value) {
max_value = value;
pivot_row = j;}}

// Swap the currunt row with the pivor row
if (pivot_row != i) {
for (std::size_t j = 0; j < AB.get_num_cols(); ++j) {
std::swap(AB(i, j), AB(pivot_row, j));
}}

// Make reading entries as 1
double pivot_element = AB(i, i);
for (std::size_t j = 0; j < AB.get_num_cols(); ++j) {
AB(i, j) /= pivot_element;}

// Subtract the pivot row multiplied by a factor from all other rows
for (std::size_t j = 0; j < AB.get_num_rows(); ++j) {
if (j != i) {
double factor = AB(j, i);
for (std::size_t k = 0; k < AB.get_num_cols(); ++k) {
AB(j, k) -= factor * AB(i, k);}}}}

// Extract Inverse Matrix of A
HPC::Matrix<double> X(A.get_num_rows(), B.get_num_cols());
for (std::size_t i = 0; i < A.get_num_rows(); ++i) {
for (std::size_t j = 0; j < B.get_num_cols(); ++j) {
X(i, j) = AB(i, A.get_num_cols() + j);}}

return X;

}

template HPC::Matrix<double> gaussjordan(HPC::Matrix<int> const& A, HPC::Matrix<int> const& B);
template HPC::Matrix<double> gaussjordan(HPC::Matrix<int> const& A, HPC::Matrix<double> const& B);
template HPC::Matrix<double> gaussjordan(HPC::Matrix<double> const& A, HPC::Matrix<int> const& B);
template HPC::Matrix<double> gaussjordan(HPC::Matrix<double> const& A, HPC::Matrix<double> const& B);



