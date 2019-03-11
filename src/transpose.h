#ifndef TRANSPOSE_H
#define TRANSPOSE_H

#include "utilities.h"
#include "omp.h"

using namespace std;
using row = shared_ptr<vector<uint32_t>>;
using matrix = shared_ptr<vector<row>>;

/// \brief Transposes a matrix, using serial algorithm
void transposeMatrixSerial(matrix A, int N);

/// \brief Transposes a matrix, using OpenMP Naive threaded algorithm
void transposeMatrixSimpleOpenMP(matrix A, int N);

/// \brief Transposes a matrix, using OpenMP threaded algorithm which swaps row/columns along diagonal
void transposeMatrixDiagonalOpenMP(matrix A, int N);

/// \brief Transposes a matrix, using OpenMP threaded version of Eklundh's algorithm
void transposeMatrixBlockOpenMP(matrix A, int N);

/// \brief Transposes a matrix, using PThreaded algorithm which swaps row/columns along diagonal
void transposeMatrixDiagonalPThread(matrix A, int N);

/// \brief Transposes a matrix, using PThreaded version of Eklundh's algorithm
void transposeMatrixBlockPThread(matrix A, int N);

#endif