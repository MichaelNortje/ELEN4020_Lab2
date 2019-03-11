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
    ofstream outputFile(fileName, ios::out);
    if (!outputFile.is_open()) {
        cout << "Unable to open file:" << fileName << endl;
    }
    const auto N = A->size();
    const auto M = A->at(0)->size();

    outputFile << N << "\t" << M << endl;

    for (auto i = 0; i < N; i++){
            for (auto j = 0; j < M; j++){
                outputFile << A->at(i)->at(j) << "\t";
            }
        outputFile << endl;
        }

    outputFile.close();
}

matrix readMatrixfromFile(string fileName){
    ifstream inputFile(fileName, ios::in);
    if (!inputFile.is_open()) {
        cout << "Unable to open file:" << fileName << endl;
    }
    inputFile.seekg(0, ios::beg);
    
    matrix A = make_shared<vector<row>>();
    int N, M;
    uint32_t val;

    inputFile >> N >> M;

    for (int i = 0; i < N; i++){
        vector<uint32_t> row;
        for (int j = 0; j < M; j++){
            inputFile >> val;
            row.push_back(val);
        }
        auto row_ptr = make_shared<vector<uint32_t>> (row);
        A->push_back(row_ptr);
    }

    return A;
}

bool matricesAreEqual(matrix A, matrix B){    
    const auto N = A->size();
    const auto M = A->at(0)->size();
    const auto NB = B->size();
    const auto MB = B->at(0)->size();

    if ((N!=NB) || (M!=MB)) {
        cout << "Error: Matrix sizes do not match" << endl;
        return -1;
    }
    
    for (auto i = 0; i < N; i++){
        for (auto j = 0; j < M; j++){
            if (A->at(i)->at(j) != B->at(i)->at(j)) {
                cout << "Error: Matrix sizes do not match at (" << i << "," << j << ")" << endl;
                return -1;
            }
        }
    }

    return 1;
}
