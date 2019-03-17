#include <math.h>
#include "transpose.h"
/// \file
/// \brief The in-place matrix transposition algorithms  (Implementation)

struct matrix_args{
         Matrix *matrix;
         int row_start;
         int row_end;
};

void transposeMatrixSerial(Matrix A)
{
    auto N = A.size();
    for (auto i = 0; i < N; i++) {
        for (auto j = 0; j < i; j++) {
            if (i!=j) {
                A.swap(i, j);
            }
        }
    }
}

void transposeMatrixSimpleOpenMP(Matrix A)
{ 
    auto N = A.size();
    #pragma omp parallel for // collapse(2)
    for (auto i = 0; i < N; i++) {
        for (auto j = 0; j < i; j++) {
            if (i!=j) {
                A.swap(i, j);
            }
        }
    }
}

void transposeMatrixDiagonalOpenMP(Matrix A)
{
    auto N = A.size();
    #pragma omp parallel for
    for (auto i = 0; i < N; i++) {
        for (auto j = i + 1; j < N; j++) {
            A.swap(i, j);
        }
    }
}

void transposeMatrixBlockOpenMP(Matrix A)
{
    auto N = A.size();
    auto stride = 2;
    #pragma omp parallel for
    for(auto row = 0; row < N; row+=stride) {
        for(auto col = 0; col <= row; col+=stride) {
            if (row == col) {
                uint32_t temp1 = A.at(row+1, col);
                A.set(row+1, col, A.at(row, col+1));
                A.set(row, col+1, temp1);
            } else {
                for(auto i = 0; i < stride; i++){
                    for(auto j = 0; j < stride; j++) {
                        uint32_t temp = A.at(col+j, row+i);
                        A.set(col+j, row+i, A.at(row+i, col+j));
                        A.set(row+i, col+j, temp);
                    }
                }
            }
        }
    }
}

void *diagonalThreadAction(void *args)
{
    matrix_args *values = (matrix_args *) args;
    Matrix *A = values->matrix;
    auto N = A->size();
    auto i = values->row_start;
    auto finish = values->row_end;
    for(; i < finish; i++){
        for (auto j = i + 1; j < N; j++) {
            if (i!=j) {
                values->matrix->swap(i, j);
            }
        }
    }
    free(values);
    pthread_exit(0);
}

void transposeMatrixDiagonalPThread(Matrix A)
{
    auto N = A.size();
    auto num_threads = getNumThreadsEnvVar();   // get Max threads for fairness
    auto chunk = floor(N/num_threads);          // number of chunks for each thread to do
    pthread_t tid[num_threads];                 // The thread IDs
    pthread_attr_t attr;                        // Thread attributes
    pthread_attr_init(&attr);                   // initialise default attributes
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE); // make joinable
    int start = 0;
    int offset = 0;
    for(auto t = 0; t < num_threads; t++){
            matrix_args *values = (matrix_args*)malloc(sizeof(matrix_args));
            values->matrix = &A;
            start = offset;
            offset = start + chunk;
            values->row_start = start;
            values->row_end = offset;
            pthread_create( &tid[t],
                            &attr,
                            diagonalThreadAction,
                            (void*)values); 
    }
    pthread_attr_destroy(&attr);                // remove attribute variable
    for(auto t = 0; t < num_threads; t++){      // wait for all threads to complete
        pthread_join(tid[t], NULL);
    }
}

void *blockThreadAction(void *args)
{
    matrix_args *values = (matrix_args *) args;
    Matrix *A = values->matrix;
    // auto N = A->size();
    auto row = values->row_start;
    auto finish = values->row_end;
    auto stride = 2;
    for(; row < finish; row+=stride) {
        for(auto col = 0; col <= row; col+=stride) {
            if (row == col) {
                uint32_t temp1 = A->at(row+1, col);
                A->set(row+1, col, A->at(row, col+1));
                A->set(row, col+1, temp1);
            } else {
                for(auto i = 0; i < stride; i++){
                    for(auto j = 0; j < stride; j++) {
                        uint32_t temp = A->at(col+j, row+i);
                        A->set(col+j, row+i, A->at(row+i, col+j));
                        A->set(row+i, col+j, temp);
                    }
                }
            }
        }
    }
    free(values);
    pthread_exit(0);
}

void transposeMatrixBlockPThread(Matrix A)
{
    auto N = A.size();
    auto num_threads = getNumThreadsEnvVar();   // get Max threads for fairness
    auto chunk = floor(N/num_threads);          // number of chunks for each thread to do
    pthread_t tid[num_threads];                 // The thread IDs
    pthread_attr_t attr;                        // Thread attributes
    pthread_attr_init(&attr);                   // initialise default attributes
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE); // make joinable
    int start = 0;
    int offset = 0;
    for(auto t = 0; t < num_threads; t++){
            matrix_args *values = (matrix_args*)malloc(sizeof(matrix_args));
            values->matrix = &A;
            start = offset;
            offset = start + chunk;
            values->row_start = start;
            values->row_end = offset;
            pthread_create( &tid[t],
                            &attr,
                            blockThreadAction,
                            (void*)values); 
    }
    pthread_attr_destroy(&attr);                // remove attribute variable
    for(auto t = 0; t < num_threads; t++){      // wait for all threads to complete
        pthread_join(tid[t], NULL);
    }
}