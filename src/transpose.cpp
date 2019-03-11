#include "transpose.h"

/// \brief Transposes a matrix, using serial algorithm
void transposeMatrixSerial(matrix A, int N){
    for (auto i = 0; i < N; i++){
        for (auto j = 0; j < i; j++){
            if (i!=j) {
                swap(A->at(j)->at(i), A->at(i)->at(j)); // Don't reinvent the wheel
                // swap() is in in move.h 
                // Uses temp variable to peform swap
                // Highly optimized in modern compilers
            }
        }
    }
}

/// \brief Transposes a matrix, using OpenMP Naive threaded algorithm
void transposeMatrixSimpleOpenMP(matrix A, int N){
    #pragma omp parallel for
    for (auto i = 0; i < N; i++){
        #pragma omp parallel for
        for (auto j = 0; j < i; j++){
            if (i!=j) {
                swap(A->at(j)->at(i), A->at(i)->at(j));
            }
        }
    }
}

/// \brief Transposes a matrix, using OpenMP threaded algorithm
//  which swaps row/columns, with a thread per diagonal entry
void transposeMatrixDiagonalOpenMP(matrix A, int N){
    #pragma omp parallel for
    for (auto i = 0; i < N; i++){
        for (auto j = i + 1; j < N; j++){
            swap(A->at(j)->at(i), A->at(i)->at(j));
        }
    }
}

/// \brief Transposes a matrix, using OpenMP threaded version of Eklundh's algorithm
void transposeMatrixBlockOpenMP(matrix A, int N){

}

/// \brief Transposes a matrix, using PThreaded algorithm which swaps row/columns along diagonal
void transposeMatrixDiagonalPThread(matrix A, int N){

}

/// \brief Transposes a matrix, using PThreaded version of Eklundh's algorithm
void transposeMatrixBlockPThread(matrix A, int N){

}