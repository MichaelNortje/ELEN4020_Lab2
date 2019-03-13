#ifndef TRANSPOSE_H
#define TRANSPOSE_H
/// \file
/// \brief The in-place matrix transposition algorithms

#include "utilities.h"
#include "omp.h"

using namespace std;

/// \brief Transposes a matrix, using serial algorithm
/// \param A single dimension of the square matrix to compare
/// \param B single dimension of the square matrix 
void transposeMatrixSerial(Matrix A, int N);

/// \brief Transposes a matrix, using OpenMP Naive threaded algorithm
void transposeMatrixSimpleOpenMP(Matrix A, int N);

/// \brief Transposes a matrix, using OpenMP threaded algorithm
//  which swaps row/columns, with a thread per diagonal entry
void transposeMatrixDiagonalOpenMP(Matrix A, int N);

/// \brief Recursively swaps sub-matrices in a block-oriented method
void swapMatrixBlockRecursive(Matrix A, int row_beg, int row_end, int col_beg, int col_end);

/// \brief Recursively transposes a matrix in a block-oriented method
void transposeMatrixBlockRecursive(Matrix A, int start, int finish);

/// \brief Transposes a matrix, using PThreaded algorithm which swaps row/columns along diagonal
void transposeMatrixDiagonalPThread(Matrix A, int N);

/// \brief Transposes a matrix, using PThreaded version of block-oriented method
void transposeMatrixBlockPThread(Matrix A, int N);

#endif