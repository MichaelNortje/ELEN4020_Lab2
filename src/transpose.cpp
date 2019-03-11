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

/// \brief Transposes a matrix, using OpenMP threaded algorithm which swaps row/columns along diagonal
void transposeMatrixDiagonalOpenMP(shared_ptr<vector<row>> A, int N){
    int i, j, tid;
    int num_threads = omp_get_num_threads();

    #pragma omp parallel shared(A, N, num_threads) private(tid, i, j) 
    {
        /* An Unneccesary optimization?:
        if (num_threads > N) {
            omp_set_num_threads(N);
            num_threads = N;  
        }
        */

        tid = omp_get_thread_num();
        auto start_thread_num = tid/num_threads;                // the row/column start value in the for loops

        for (i = start_thread_num; i < N; i++){                 // For row entry from the diagonal out
                for(j = start_thread_num; i < N; i++) {         // iterate through each column entry
                    if (i!=j) {                                 // skip equal entries
                            swap(A->at(j)->at(i), A->at(i)->at(j));
                            /* printf("Thread %d did (%d,%d)->(%d,%d) \n%", tid, j, i, i, j); */
                        }
                }
        }
    }
}

/// \brief Transposes a matrix, using OpenMP threaded version of Eklundh's algorithm
void transposeMatrixBlockOpenMP(shared_ptr<vector<row>> A, int N){

}

/// \brief Transposes a matrix, using PThreaded algorithm which swaps row/columns along diagonal
void transposeMatrixDiagonalPThread(shared_ptr<vector<shared_ptr<vector<uint32_t>>>> A, int N){

}

/// \brief Transposes a matrix, using PThreaded version of Eklundh's algorithm
void transposeMatrixBlockPThread(shared_ptr<vector<shared_ptr<vector<uint32_t>>>> A, int N){

}