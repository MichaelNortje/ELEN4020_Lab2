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
    #pragma omp parallel for // collapse(2)
    for (auto i = 0; i < N; i++) {
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
                swapMatrixBlockRecursive(A, row_beg,  row_mid,  col_beg,  col_mid);
                swapMatrixBlockRecursive(A, row_beg,  row_mid,  col_mid,  col_end);
                swapMatrixBlockRecursive(A, row_mid,  row_end,  col_beg,  col_mid);
                swapMatrixBlockRecursive(A, row_mid,  row_end,  col_mid,  col_end);
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

void transposeMatrixBlockOpenMP(Matrix A, int N)
{
        auto stride = 2;
        // #pragma omp parallel
        for(auto row = 0; row < N; row+=stride) {
            for(auto col = 0; col <= row; col+=stride) {
                if (row == col) {
                    uint32_t temp1 = A.at(row+1, col);
                    A.set(row+1, col, A.at(row, col+1));
                    A.set(row, col+1, temp1);
                } else {
                    // Chunk into blocks:
                    // Matrix B(2); // temp
                    // Matrix C(2); // temp
                    for(auto i = 0; i < stride; i++){
                        for(auto j = 0; j < stride; j++) {
                            uint32_t temp = A.at(col+j, row+i);
                            A.set(col+j, row+i, A.at(row+i, col+j));
                            A.set(row+i, col+j, temp);
                            // B.set(j, i, A.at(col+j, row+i));
                            // C.set(i, j, A.at(row+i, col+j));
                        }
                    }
                    // printf("B = A_%d%d : \n", col, row);
                    // print2d(B);
                    // printf("C = A_%d%d : \n", row, col);
                    // print2d(C);
                }
            }
        }
        // Transpose in each block:
        // #pragma omp parallel
        // for(auto i = 0; i < N; i+=2) {
        //     for(auto j = 1; j < N; j+=2) {
        //         A.swap(i,j);
        //     }
        // }
    // cout << "Count = " << count << endl;
}

void transposeMatrixDiagonalPThread(Matrix A, int N)
{

}

void transposeMatrixBlockPThread(Matrix A, int N)
{

}