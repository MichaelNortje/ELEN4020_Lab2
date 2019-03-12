#ifndef TRANSPOSE_H
#define TRANSPOSE_H

#include "utilities.h"
#include "omp.h"

using namespace std;

/// \brief Transposes a matrix, using serial algorithm
/// \param A A single dimension of the square matrix to compaet
/// \param A B single dimension of the square matrix
void transposeMatrixSerial(Matrix A, int N);

/// \brief Transposes a matrix, using OpenMP Naive threaded algorithm
void transposeMatrixSimpleOpenMP(Matrix A, int N);

/// \brief Transposes a matrix, using OpenMP threaded algorithm
//  which swaps row/columns, with a thread per diagonal entry
void transposeMatrixDiagonalOpenMP(Matrix A, int N);

/// \brief Recursively swaps sub-matrices
void swapMatrixBlockRecursive(Matrix A, int row_beg, int row_end, int col_beg, int col_end);

/// \brief Recursively transposes a matrix
void transposeMatrixBlockRecursive(Matrix A, int start, int finish);

/// \brief Transposes a matrix, using PThreaded algorithm which swaps row/columns along diagonal
void transposeMatrixDiagonalPThread(Matrix A, int N);

/// \brief Transposes a matrix, using PThreaded version of Eklundh's algorithm
void transposeMatrixBlockPThread(Matrix A, int N);

#endif