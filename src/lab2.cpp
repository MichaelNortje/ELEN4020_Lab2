#include <chrono>
#include <assert.h>
#include "utilities.h"
#include "transpose.h"

using namespace std;
using namespace std::chrono;

using row = shared_ptr<vector<uint32_t>>;
using matrix = shared_ptr<vector<row>>;

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

    vector<int> sizes = {128, 1024, 2048, 4096};
    // vector<int> sizes = {3, 5, 6, 8};
    // vector<int> sizes = {8};

    for (auto& N : sizes)
    {
        shared_ptr<vector<row>> A = generate2d(N);
        string validationFile = "data.txt";
        writeMatrixToFile(validationFile, A);

        steady_clock::time_point t1 = steady_clock::now();
        transposeMatrixSerial(A, N);
        steady_clock::time_point t2 = steady_clock::now();
        auto timer_serial = duration_cast<duration<double>>(t2 - t1);
        transposeMatrixSerial(A, N);
        assert(matricesAreEqual(A, readMatrixfromFile(validationFile)));

        t1 = steady_clock::now();
        transposeMatrixSimpleOpenMP(A, N);
        t2 = steady_clock::now();
        auto timer_simple_OpenMP = duration_cast<duration<double>>(t2 - t1);
        transposeMatrixSerial(A, N);
        assert(matricesAreEqual(A, readMatrixfromFile(validationFile)));

        t1 = steady_clock::now();
        transposeMatrixDiagonalOpenMP(A, N);
        t2 = steady_clock::now();
        auto timer_diagonal_OpenMP = duration_cast<duration<double>>(t2 - t1);
        transposeMatrixSerial(A, N);
        assert(matricesAreEqual(A, readMatrixfromFile(validationFile)));

        t1 = steady_clock::now();
        transposeMatrixBlockOpenMP(A, N);
        t2 = steady_clock::now();
        auto timer_block_OpenMP = duration_cast<duration<double>>(t2 - t1);
        // transposeMatrixSerial(A, N);
        // assert(matricesAreEqual(A, readMatrixfromFile(validationFile)));

        t1 = steady_clock::now();
        transposeMatrixDiagonalPThread(A, N);
        t2 = steady_clock::now();
        auto timer_diagonal_PThread = duration_cast<duration<double>>(t2 - t1);
        // transposeMatrixSerial(A, N);
        // assert(matricesAreEqual(A, readMatrixfromFile(validationFile)));

        t1 = steady_clock::now();
        transposeMatrixBlockPThread(A, N);
        t2 = steady_clock::now();
        auto timer_block_PThread = duration_cast<duration<double>>(t2 - t1);
        // transposeMatrixSerial(A, N);
        // assert(matricesAreEqual(A, readMatrixfromFile(validationFile)));


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