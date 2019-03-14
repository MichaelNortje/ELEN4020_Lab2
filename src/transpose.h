#ifndef TRANSPOSE_H
#define TRANSPOSE_H
/// \file
/// \brief The in-place matrix transposition algorithms

#include "utilities.h"
#include "omp.h"

using namespace std;

/// \brief Transposes a matrix, using serial algorithm
/// \param The matrix to transpose
void transposeMatrixSerial(Matrix A);

/// \brief Transposes a matrix, using OpenMP Naive threaded algorithm
/// \param N The number of row/columns
/// \param The matrix to transpose
void transposeMatrixSimpleOpenMP(Matrix A);

/// \brief Transposes a matrix, using OpenMP threaded algorithm
//  which swaps row/columns, with a thread per diagonal entry
/// \param The matrix to transpose
void transposeMatrixDiagonalOpenMP(Matrix A);

// \brief Transposes a matrix, using OpenMP block-oriented algorithm
//  with a thread per "block"
/// \param The matrix to transpose
void transposeMatrixBlockOpenMP(Matrix A);

/// \brief Transposes a matrix, using PThreaded algorithm which swaps row/columns along diagonal
/// \param The matrix to transpose
void transposeMatrixDiagonalPThread(Matrix A);

/// \brief Transposes a matrix, using PThreaded version of block-oriented method
/// \param The matrix to transpose
void transposeMatrixBlockPThread(Matrix A);

#endif