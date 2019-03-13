#ifndef TRANSPOSE_H
#define TRANSPOSE_H
/// \file
/// \brief The in-place matrix transposition algorithms

#include "utilities.h"
#include "omp.h"

using namespace std;

/// \brief Transposes a matrix, using serial algorithm
/// \param The matrix to transpose
/// \param The number of row/columns
void transposeMatrixSerial(Matrix A, int N);

/// \brief Transposes a matrix, using OpenMP Naive threaded algorithm
/// \param N The number of row/columns
/// \param The matrix to transpose
/// \param The number of row/columns
void transposeMatrixSimpleOpenMP(Matrix A, int N);

/// \brief Transposes a matrix, using OpenMP threaded algorithm
//  which swaps row/columns, with a thread per diagonal entry
/// \param The matrix to transpose
/// \param The number of row/columns
void transposeMatrixDiagonalOpenMP(Matrix A, int N);

/// \brief Recursively swaps sub-matrices in a block-oriented method
/// \param The matrix to transpose
/// \param The start row to treat as the start of the block
/// \param The end row to treat as the end of the block
/// \param The starting column to treat as the start of the block
/// \param The end column to treat as the end of the block
void swapMatrixBlockRecursive(Matrix A, int row_beg, int row_end, int col_beg, int col_end);

/// \brief Recursively transposes a matrix in a block-oriented method
/// \param The matrix to transpose
/// \param The starting entry to treat as the start of the block
/// \param The ending entry to treat as the end of the block
void transposeMatrixBlockRecursive(Matrix A, int start, int finish);

/// \brief Transposes a matrix, using PThreaded algorithm which swaps row/columns along diagonal
/// \param The matrix to transpose
/// \param The number of row/columns
void transposeMatrixDiagonalPThread(Matrix A, int N);

/// \brief Transposes a matrix, using PThreaded version of block-oriented method
/// \param The matrix to transpose
/// \param The number of row/columns
void transposeMatrixBlockPThread(Matrix A, int N);

#endif