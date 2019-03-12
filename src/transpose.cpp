#include "transpose.h"

void transposeMatrixSerial(Matrix A, int N)
{
    for (auto i = 0; i < N; i++) {
        for (auto j = 0; j < i; j++) {
            if (i!=j) {
                A.swap(i, j);
            }
        }
    }
}

void transposeMatrixSimpleOpenMP(Matrix A, int N)
{
    #pragma omp parallel for
    for (auto i = 0; i < N; i++) {
        #pragma omp parallel for
        for (auto j = 0; j < i; j++) {
            if (i!=j) {
                A.swap(i, j);
            }
        }
    }
}

void transposeMatrixDiagonalOpenMP(Matrix A, int N)
{
    #pragma omp parallel for
    for (auto i = 0; i < N; i++) {
        for (auto j = i + 1; j < N; j++) {
            A.swap(i, j);
        }
    }
}

void swapMatrixBlockRecursive(Matrix A, int row_beg, int row_end, int col_beg, int col_end)
{
        if (row_end - row_beg > 2 && col_end - col_beg > 2) {
            int row_mid = (row_beg + row_end) / 2;
            int col_mid = (col_beg + col_end) / 2;
            {
                // #pragma omp task shared(A)
                swapMatrixBlockRecursive(A, row_beg,  row_mid,  col_beg,  col_mid);
                // #pragma omp task shared(A)
                swapMatrixBlockRecursive(A, row_beg,  row_mid,  col_mid,  col_end);
                // #pragma omp task shared(A)
                swapMatrixBlockRecursive(A, row_mid,  row_end,  col_beg,  col_mid);
                // #pragma omp task shared(A)
                swapMatrixBlockRecursive(A, row_mid,  row_end,  col_mid,  col_end);
                // #pragma omp taskwait
            }
        } else {
            for (auto i = row_beg; i < row_end; i++) {
                for (auto j = col_beg; j < col_end; j++) {
                    A.swap(i, j);
                }
            }
        }
}

void transposeMatrixBlockRecursive(Matrix A, int start, int finish)
{
        if (finish - start > 2) {
            auto middle = (start + finish) / 2;
            transposeMatrixBlockRecursive(A, start, middle);
            transposeMatrixBlockRecursive(A, middle, finish);
            swapMatrixBlockRecursive(A, middle, finish, start, middle);
        } else {
            for (auto i = start; i < finish; i++) {
                for (auto j = start+1; j < finish; j++) {
                    A.swap(i, j);   
                }
            }
        }
}

void transposeMatrixDiagonalPThread(Matrix A, int N)
{

}

void transposeMatrixBlockPThread(Matrix A, int N)
{

}