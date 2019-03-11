#ifndef UTILITIES_H
#define UTILITIES_H

#include <iostream>
#include <iomanip>
#include <stdio.h>
#include <fstream>
#include <vector>
#include <memory>

using namespace std;
using row = shared_ptr<vector<uint32_t>>;
using matrix = shared_ptr<vector<row>>;

/// \brief Generates an NxN matrix with random int values between 0 and N
matrix generate2d(int N);

/// \brief Prints an NxM matrix
void print2d(shared_ptr<vector<row>> A);

/// \brief Caches a matrix to disk
void writeMatrixToFile(string fileName, matrix A);

/// \brief Reads a matrix into memory from disk
matrix readMatrixfromFile(string fileName);

/// \brief Compares two matrices to check if all elements are equal
bool matricesAreEqual(matrix A, matrix B);

#endif