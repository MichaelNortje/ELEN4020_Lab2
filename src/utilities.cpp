#include "utilities.h"

matrix generate2d(int N){
    srand (static_cast<unsigned int>(time(NULL)));
    matrix A = make_shared<vector<row>>();
    for (int i = 0; i < N; i++){
        vector<uint32_t> row;
        for (int j = 0; j < N; j++){
            row.push_back(rand() % N);
            // row.push_back(INT_MAX - (rand() % 10)); // Overflow condition
        }
        auto row_ptr = make_shared<vector<uint32_t>> (row);
        A->push_back(row_ptr);
    }
    return A;
}

/// \brief Prints an NxM matrix
void print2d(matrix A){
    const auto N = A->size();
    const auto M = A->at(0)->size();
    cout << N << "x" << M << endl;
    for (auto i = 0; i < N; i++){
        for (auto j = 0; j < M; j++){
            cout << A->at(i)->at(j) << "\t";
        }
        cout << endl;
    }
}

void writeMatrixToFile(string fileName, matrix A){

}

matrix readMatrixfromFile(string fileName){
    matrix A;
    return A;
}

bool matricesAreEqual(matrix A, matrix B){
    return 1;
}
