#include "transpose.h"

struct matrix_args{
         Matrix *matrix;
         int row;
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

void *transposeMatrixThread(void *args)
{
    matrix_args *values = (matrix_args *) args;
    int i = values->row;
    for (auto j = i + 1; j < values->matrix->size(); j++) {
        if (i!=j) {
            values->matrix->swap(i, j);
        }
    }
    free(values);
    pthread_exit(0);
}

void transposeMatrixDiagonalPThread(Matrix A)
{
    auto num_threads = getNumThreadsEnvVar();   // get Max threads for fairness
    pthread_t tid[num_threads];                 // The thread IDs
    pthread_attr_t attr;                        // Thread attributes
    pthread_attr_init(&attr);                   // initialise default attributes
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE); // make joinable
    for(auto t = 0; t < num_threads; t++){
            matrix_args *values = (matrix_args*)malloc(sizeof(matrix_args));
            values->matrix = &A;
            values->row = t;
            pthread_create( &tid[t],
                            &attr,
                            transposeMatrixThread,
                            (void*)values); 
    }
    pthread_attr_destroy(&attr);                // remove attribute variable
    for(auto t = 0; t < num_threads; t++){      // wait for all threads to complete
        pthread_join(tid[t], NULL);
    }
    
}

void transposeMatrixBlockPThread(Matrix A)
{
    auto N = A.size();
}