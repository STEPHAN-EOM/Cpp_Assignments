/**
 * @file matrix.h
 * @brief Templated Matrix class for Assignment 3 of 5614 C++ programming
 * @author Chanho Eom
 * @date 24-Mar-2023
 */

#ifndef MATRIX_H_FIYNRKOJ
#define MATRIX_H_FIYNRKOJ

#include <iostream>
#include <iomanip>
#include <fstream>
#include "hpc_concepts.h"
#include "logging.h"

namespace HPC
{
	template <Number T>
		class Matrix {
			public:
				Matrix() = delete; 								// Delete default constructor. Really only a comment.
				Matrix(std::size_t const rows, std::size_t const cols); 			// Overloaded Constructor
				Matrix(std::string const file); 						// Overloaded Constructor. Read data from file.
				T& operator() (std::size_t const row_num, std::size_t const col_num);        	// non-const version which can be used to modify objects
				T  operator() (std::size_t const row_num, std::size_t const col_num) const;  	// Const version to be called on const objects

				~Matrix();                              // Destructor
				Matrix(Matrix const& m);               	// Copy constructor
				Matrix& operator=(Matrix const& m);   	// Assignment operator
				Matrix(Matrix && in); 			// Move Constructor
				Matrix& operator=(Matrix&& in); 	// Move Assignment operator

				// Note: Need the template brackets here in declaration.
				friend std::ostream& operator<< <>(std::ostream& os, Matrix<T> const& in);

				std::size_t get_num_rows() const{ return rows;};
				std::size_t get_num_cols() const{ return cols;};

			private:
				std::size_t rows, cols;
				T* data;
		};


	/**
	 * @brief Basic overloaded constructor for Matrix<T> class
	 * 		Note that this will set the values in data to zero.
	 * 		Don't need to check for negative values as size_t will be unsigned.
	 *
	 * @tparam T 	Number type that the matrix contains
	 * @param[in] num_rows Number of rows in created matrix
	 * @param[in] num_cols Number of columns in created matrix.
	 */
	template <Number T>
		Matrix<T>::Matrix(std::size_t const num_rows, std::size_t const num_cols)
		: rows {num_rows}
		, cols {num_cols}
		, data {new T [rows * cols]{}}
	{
		std::cout << "Constructing " << rows << "x" << cols << " Matrix\n";
	}

// Desctuctor
template <Number T>
Matrix<T>::~Matrix(){
std::cout << "Calling destructor for matrix " << rows << "x" << cols << " Matrix" << std::endl;

delete[] data;
}

/**
 * @brief: overloaed constructor to read the matrix files
 * @input: string, file 
 * @output: read a file
 * */
template <Number T>
Matrix<T>::Matrix(std::string const file){

std::ifstream fin(file);
if (!fin.is_open()){
std::cerr << "Could not open the file" << file << "\n";
exit(-1);}

fin >> rows >> cols;
data = new T[rows * cols];

for (std::size_t i = 0; i < rows * cols; ++i){
fin >> data[i];}
fin.close();

std::cout << "Constructing Matrix with data read from file matrix_" << rows << "x" << cols << ".txt" << std::endl;
}


// Copy Constuctor
template <Number T>
Matrix<T>::Matrix(Matrix const& m) : rows(m.rows), cols(m.cols), data(new T[rows * cols]) {
std::cout << "Copy Constructor" << "\n";

std::copy(m.data, m.data + rows * cols, data);
}

// Copy Assignment
template <Number T>
Matrix<T>& Matrix<T>::operator=(Matrix const& m) {
std::cout << "Copy Assignment operator" << "\n";

if (this == &m){
std::cout << "Self copy!\n";
return *this;}

if (this != &m){
delete[] data;
rows = m.rows;
cols = m.cols;
data = new T[rows * cols];
std::copy(m.data, m.data + rows * cols, data);}

return *this;
}

// Move Constructor
template <Number T>
Matrix<T>::Matrix(Matrix && in): rows{in.rows}, cols{in.cols}, data{in.data} {
std::cout << "Move Constructor" << std::endl;

in.rows = 0;
in.cols = 0;
in.data = nullptr;
}

// Move Assignment
template <Number T>
Matrix<T>& Matrix<T>::operator=(Matrix && in){
std::cout << "Move Assignment" << std::endl;

if (this != &in){
delete[] data;
data = in.data;
rows = in.rows;
cols = in.cols;

in.data = nullptr;
in.rows = 0;
in.cols = 0;}

return *this;
}

template <Number T>
T& Matrix<T>::operator() (std::size_t const row_num, std::size_t const col_num){
return data[row_num * cols + col_num];
}


template <Number T>
T Matrix<T>::operator() (std::size_t const row_num, std::size_t const col_num) const{
return data[row_num * cols + col_num];
}

// print the matrix 
template <Number T>
std::ostream& operator<<(std::ostream& os, const Matrix<T>& in) {

os << std::fixed << std::setprecision(2);
for (std::size_t i = 0; i < in.get_num_rows(); i++){
os << "|\t";
for (std::size_t j = 0; j < in.get_num_cols(); j++){
os << in(i, j) << "\t";}
os << "|";
os << std::endl;}

return os;
}

// Matrix Summation
template <Number T1, Number T2>
auto operator+(HPC:: Matrix<T1> const& M1, HPC:: Matrix<T2> const& M2) {

static_assert(std::is_arithmetic_v<T1> && std::is_arithmetic_v<T2>, "T1 and T2 must be arithmetic types");

using R = std::common_type_t<T1, T2>;
HPC::Matrix<R> result(M1.get_num_rows(), M1.get_num_cols());

// Matrix Summation
for (std::size_t i = 0; i < M1.get_num_rows(); ++i){
for (std::size_t j = 0; j < M1.get_num_cols(); ++j){
result(i, j) = static_cast<R>(M1(i, j)) + static_cast<R>(M2(i, j));}}

return result;
}

// Matrix Multiplication
template <Number T1, Number T2>
//auto operator*(HPC::Matrix<T1> const& M1, HPC::Matrix<T2> const& M2) {
auto operator*(HPC::Matrix<T1> const& M1, HPC::Matrix<T2> const& M2) -> HPC::Matrix<std::common_type_t<T1, T2>> {

// Define the size of the new matrix(AB)
std::size_t const rows = M1.get_num_rows();
std::size_t const cols = M2.get_num_cols();

// Check the size of matrices for multiplication
if (M1.get_num_cols() != M2.get_num_rows()) {
std::cerr << "Error for matching Matrices size for multiplication"<< "\n";  
return HPC::Matrix<std::common_type_t<T1, T2>>(0, 0);}

HPC::Matrix<std::common_type_t<T1, T2>> result(rows, cols);

// Matrix Multiplication
for (std::size_t i = 0; i < rows; ++i){
for (std::size_t j = 0; j < cols; ++j){
std::common_type_t<T1, T2> dot = 0;
for (std::size_t k = 0; k < M1.get_num_cols(); ++k){
dot += M1(i, k) * M2(k, j);}
result(i, j) = dot;
}}

return result;
}


// Make an Identity Matrix
template <Number T>
//void identity(auto& in) {
void identity(Matrix<T>& in){

std::size_t n = std::min(in.get_num_rows(), in.get_num_cols());
//in = T(n, n);
in = Matrix<T>(n, n);
for (std::size_t i = 0; i < n; ++i){
in(i, i) = 1;}
}

} /*  HPC */ 
#endif /* end of include guard: MATRIX_H_FIYNRKOJ */
