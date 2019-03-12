#include "transpose.h"

/// \brief Transposes a matrix, using serial algorithm
void transposeMatrixSerial(Matrix A, int N){
    for (auto i = 0; i < N; i++){
        for (auto j = 0; j < i; j++){
            if (i!=j) {
                A.swap(i, j);
            }
        }
    }
}

/// \brief Transposes a matrix, using OpenMP Naive threaded algorithm
void transposeMatrixSimpleOpenMP(Matrix A, int N){
    #pragma omp parallel for
    for (auto i = 0; i < N; i++){
        #pragma omp parallel for
        for (auto j = 0; j < i; j++){
            if (i!=j) {
                A.swap(i, j);
            }
        }
    }
}

/// \brief Transposes a matrix, using OpenMP threaded algorithm
//  which swaps row/columns, with a thread per diagonal entry
void transposeMatrixDiagonalOpenMP(Matrix A, int N){
    #pragma omp parallel for
    for (auto i = 0; i < N; i++){
        for (auto j = i + 1; j < N; j++){
            A.swap(i, j);
        }
    }
}

/// \brief Transposes a matrix, using OpenMP threaded version of Eklundh's algorithm
void transposeMatrixBlockOpenMP(Matrix A, int N){

}

/// \brief Transposes a matrix, using PThreaded algorithm which swaps row/columns along diagonal
void transposeMatrixDiagonalPThread(Matrix A, int N){

}

/// \brief Transposes a matrix, using PThreaded version of Eklundh's algorithm
void transposeMatrixBlockPThread(Matrix A, int N){

}