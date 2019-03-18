#ifndef TRANSPOSE_H
#define TRANSPOSE_H
/// \file
/// \brief The in-place matrix transposition algorithms (Definitions)

#include <omp.h>
#include <pthread.h>
#include "utilities.h"

using namespace std;

/// \brief Transposes a matrix, using serial algorithm
/// \param The matrix to transpose
void transposeMatrixSerial(Matrix A);

/// \brief Transposes a matrix, using OpenMP Naive threaded algorithm
/// \param The matrix to transpose
void transposeMatrixNaiveOpenMP(Matrix A);

/// \brief Transposes a matrix, using OpenMP threaded algorithm
//  which swaps row/columns, with a thread per diagonal entry
/// \param The matrix to transpose
void transposeMatrixDiagonalOpenMP(Matrix A);

// \brief Transposes a matrix, using OpenMP block-oriented algorithm
//  with a thread per "block"
/// \param The matrix to transpose
void transposeMatrixBlockOpenMP(Matrix A);

/// \brief Per-thread niave matrix transpose function
/// \brief A pointer to a struct containing the arguments for the function
void *naiveThreadAction(void *args);

/// \brief Transposes a matrix, using PThreaded naive threaded algorithm
/// \param The matrix to transpose
void transposeMatrixNaivePThread(Matrix A);

/// \brief Per-thread diagonal matrix transpose function
/// \brief A pointer to a struct containing the arguments for the function
void *diagonalThreadAction(void *arg);

/// \brief Transposes a matrix, using PThreaded algorithm which swaps row/columns along diagonal
/// \param The matrix to transpose
void transposeMatrixDiagonalPThread(Matrix A);

/// \brief Per-thread block-oriented matrix transpose function
/// \brief A pointer to a struct containing the arguments for the function
void *blockThreadAction(void *args);

/// \brief Transposes a matrix, using PThreaded version of block-oriented method
/// \param The matrix to transpose
void transposeMatrixBlockPThread(Matrix A);

#endif