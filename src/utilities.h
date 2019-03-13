#ifndef UTILITIES_H
#define UTILITIES_H
/// \file
/// \brief Various output and validation methods for confirming transposition

#include <iostream>
#include <iomanip>
#include <stdio.h>
#include <fstream>
#include <vector>
#include "Matrix.h"

using namespace std;

/// \brief Generates an NxN matrix with random int values between 0 and N
/// \param The number of row/columns
Matrix generate2d(int N);

/// \brief Prints an NxM matrix
/// \param The matrix to print
void print2d(Matrix A);

/// \brief Caches a matrix to disk
/// \param Path to the cache file to write (replaces contents)
/// \param The matrix to cache to disk
void writeMatrixToFile(string fileName, Matrix A);

/// \brief Reads a matrix into memory from disk
/// \param Path to the cache file to read
Matrix readMatrixfromFile(string fileName);

/// \brief Compares two matrices to check if all elements are the same
/// \param The first matrix to compare to
/// \param The second matrix to compare with
bool matricesAreEqual(Matrix A, Matrix B);

#endif