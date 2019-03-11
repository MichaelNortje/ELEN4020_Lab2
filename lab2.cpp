#include <iostream>
#include <iomanip>
#include <stdio.h>
#include <fstream>
#include <vector>
#include <memory>
#include <climits>
#include <chrono>
#include "omp.h"

using namespace std;
using namespace std::chrono;

/// \brief Generates an NxN matrix with random int values between 0 and N
shared_ptr<vector<shared_ptr<vector<uint32_t>>>> generate2d(int N){
    srand (static_cast<unsigned int>(time(NULL)));
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
    cout << N << "x" << M << endl;
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
void transposeMatrixSimpleOpenMP(shared_ptr<vector<shared_ptr<vector<uint32_t>>>> A, int N){
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
void transposeMatrixDiagonalOpenMP(shared_ptr<vector<shared_ptr<vector<uint32_t>>>> A, int N){
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
void transposeMatrixBlockOpenMP(shared_ptr<vector<shared_ptr<vector<uint32_t>>>> A, int N){

}

/// \brief Transposes a matrix, using PThreaded algorithm which swaps row/columns along diagonal
void transposeMatrixDiagonalPThread(shared_ptr<vector<shared_ptr<vector<uint32_t>>>> A, int N){

}

/// \brief Transposes a matrix, using PThreaded version of Eklundh's algorithm
void transposeMatrixBlockPThread(shared_ptr<vector<shared_ptr<vector<uint32_t>>>> A, int N){

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
//		                                           Main
////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main(){
    // overall system time elapsed
	clock_t start_time = clock();

    /* Output setup */
	string fileOutName = "timings.txt";
	ofstream output_file(fileOutName, ios::out | ios::trunc);
	if (!output_file.is_open()) { cerr << "Unable to open file:" << fileOutName << endl; return -1;}

    /* Output column titles */
	auto width = 20;
	output_file << setw(width) << left << "#N0=N1";
	output_file << setw(width) << left << "Serial";
	output_file << setw(width) << left << "OpenMP:Naive";
    output_file << setw(width) << left << "OpenMP:Diagonal";
	output_file << setw(width) << left << "OpenMP:Block";
    output_file << setw(width) << left << "PThreads:Diagonal";
	output_file << setw(width) << left << "PThreads:Block";
	output_file << endl;
    
    auto print = false;

    vector<int> sizes = {128, 1024, 2048, 4096, 8192};
    // vector<int> sizes = {3, 5, 6, 8};
    // vector<int> sizes = {8};

    for (auto& N : sizes)
    {
        shared_ptr<vector<shared_ptr<vector<uint32_t>>>> A = generate2d(N);
        if (print) print2d(A);

        steady_clock::time_point t1 = steady_clock::now();
        transposeMatrixSerial(A, N);
        steady_clock::time_point t2 = steady_clock::now();
        auto timer_serial = duration_cast<duration<double>>(t2 - t1);
        if (print) print2d(A);

        t1 = steady_clock::now();
        transposeMatrixSimpleOpenMP(A, N);
        t2 = steady_clock::now();
        auto timer_simple_OpenMP = duration_cast<duration<double>>(t2 - t1);
        if (print) print2d(A);

        t1 = steady_clock::now();
        transposeMatrixDiagonalOpenMP(A, N);
        t2 = steady_clock::now();
        auto timer_diagonal_OpenMP = duration_cast<duration<double>>(t2 - t1);
        if (print) print2d(A);

        t1 = steady_clock::now();
        transposeMatrixBlockOpenMP(A, N);
        t2 = steady_clock::now();
        auto timer_block_OpenMP = duration_cast<duration<double>>(t2 - t1);
        if (print) print2d(A);

        t1 = steady_clock::now();
        transposeMatrixDiagonalPThread(A, N);
        t2 = steady_clock::now();
        auto timer_diagonal_PThread = duration_cast<duration<double>>(t2 - t1);
        if (print) print2d(A);

        t1 = steady_clock::now();
        transposeMatrixBlockPThread(A, N);
        t2 = steady_clock::now();
        auto timer_block_PThread = duration_cast<duration<double>>(t2 - t1);
        if (print) print2d(A);


        /* Output Time */
		output_file << setw(width) << left << N;
		output_file << setw(width) << left << setprecision(7) << fixed << timer_serial.count();
		output_file << setw(width) << left << setprecision(7) << fixed << timer_simple_OpenMP.count();
        output_file << setw(width) << left << setprecision(7) << fixed << timer_diagonal_OpenMP.count();
        output_file << setw(width) << left << setprecision(7) << fixed << "N/A";//timer_block_OpenMP.count();
        output_file << setw(width) << left << setprecision(7) << fixed << "N/A";//timer_diagonal_PThread.count();
        output_file << setw(width) << left << setprecision(7) << fixed << "N/A";//timer_block_PThread.count();
        output_file << endl;
    }

	output_file.close();

	cout << "Executable Runtime: " << double( clock() - start_time) / (double) CLOCKS_PER_SEC << " seconds" << endl;
	cout << "Processing complete: created timings.txt" << endl;
}