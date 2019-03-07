#include <iostream>
#include <vector>
#include <memory>
#include <climits>
#include <chrono>
#include "omp.h"

using namespace std;
using namespace std::chrono;

/// \brief Generates an NxN matrix with random int values between 0 and N
shared_ptr<vector<shared_ptr<vector<uint32_t>>>> generate2d(int N){
    srand(time(NULL));
    shared_ptr<vector<shared_ptr<vector<uint32_t>>>> A = make_shared<vector<shared_ptr<vector<uint32_t>>>>();
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
void print2d(shared_ptr<vector<shared_ptr<vector<uint32_t>>>> A){
    const auto N = A->size();
    const auto M = A->at(0)->size();
    cout << N << "x" << "M" << endl;
    for (auto i = 0; i < N; i++){
        for (auto j = 0; j < M; j++){
            cout << A->at(i)->at(j) << "\t";
        }
        cout << endl;
    }
}

/// \brief Transposes a matrix, using serial algorithm
void transposeMatrixSerial(shared_ptr<vector<shared_ptr<vector<uint32_t>>>> A, int N){
    for (auto i = 0; i < N; i++){
        for (auto j = 0; j < i; j++){
            // overflow check
            if (A->at(i)->at(j) > (INT_MAX - A->at(j)->at(i))) {
                auto temp = A->at(i)->at(j);
                A->at(i)->at(j) = A->at(j)->at(i);
                A->at(j)->at(i) = temp;
            } else {
                // In-place swap
                A->at(j)->at(i) += A->at(i)->at(j);
                A->at(i)->at(j) = A->at(j)->at(i) - A->at(i)->at(j);
                A->at(j)->at(i) -= A->at(i)->at(j);
            }
        }
    }
}

/// \brief Transposes a matrix, using OpenMP Naive threaded algorithm
void transposeMatrixSimpleOpenMP(shared_ptr<vector<shared_ptr<vector<uint32_t>>>> A, int N){
    #pragma omp parallel for
    for (auto i = 0; i < N; i++){
        #pragma omp parallel for
        for (auto j = 0; j < i; j++){
            // overflow check
            if (A->at(i)->at(j) > (INT_MAX - A->at(j)->at(i))) {
                auto temp = A->at(i)->at(j);
                A->at(i)->at(j) = A->at(j)->at(i);
                A->at(j)->at(i) = temp;
            } else {
                // In-place swap
                A->at(j)->at(i) += A->at(i)->at(j);
                A->at(i)->at(j) = A->at(j)->at(i) - A->at(i)->at(j);
                A->at(j)->at(i) -= A->at(i)->at(j);
            }
        }
    }
}

int main(){
    
    vector<int> sizes = {128, 1024, 2048, 4096};
    // vector<int> sizes = {2, 4, 6, 8};
    vector<duration<double>> timer_serial;
    vector<duration<double>> timer_simple_OpenMP;

    for (auto& N : sizes)
    {
        shared_ptr<vector<shared_ptr<vector<uint32_t>>>> A = generate2d(N);
        // print2d(A);

        steady_clock::time_point t1 = steady_clock::now();
        transposeMatrixSerial(A, N);
        steady_clock::time_point t2 = steady_clock::now();
        timer_serial.push_back(duration_cast<duration<double>>(t2 - t1));
        // print2d(A);

        t1 = steady_clock::now();
        transposeMatrixSimpleOpenMP(A, N);
        t2 = steady_clock::now();
        timer_simple_OpenMP.push_back(duration_cast<duration<double>>(t2 - t1));
        // print2d(A);
    }

    // Output
    cout << endl << "Serial (Naive): \n";
    auto i = 0;
    for (auto& N : sizes){
        cout << N << "x" << N << ": " << timer_serial.at(i).count() << " seconds";
        cout << endl;
        i++;
    }

    cout << endl << "OpenMP (Naive): \n";
    i = 0;
    for (auto& N : sizes){
        cout << N << "x" << N << ": " << timer_simple_OpenMP.at(i).count() << " seconds";
        cout << endl;
        i++;
    }

    return 0;
}