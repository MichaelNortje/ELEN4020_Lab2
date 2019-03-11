#include <chrono>
#include <assert.h>
#include <functional>
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
	// output_file << setw(width) << left << "OpenMP:Block";
    // output_file << setw(width) << left << "PThreads:Diagonal";
	// output_file << setw(width) << left << "PThreads:Block";
	output_file << endl;
    
    vector<function<void (matrix, int)>> vector_of_transpose_functions;     // vector of pointers to functions

    vector_of_transpose_functions.push_back(transposeMatrixSerial);
    vector_of_transpose_functions.push_back(transposeMatrixSimpleOpenMP);
    vector_of_transpose_functions.push_back(transposeMatrixDiagonalOpenMP);
    // vector_of_transpose_functions.push_back(transposeMatrixBlockOpenMP);
    // vector_of_transpose_functions.push_back(transposeMatrixDiagonalPThread);
    // vector_of_transpose_functions.push_back(transposeMatrixBlockPThread);

    vector<int> sizes = {2, 4, 8, 16, 32, 64, 128, 512, 1024, 2048, 4096, 8196};
    // vector<int> sizes = {3, 5, 6, 8, 10};
    // vector<int> sizes = {3};
    
    int i = 0;
    for (auto& N : sizes)
    {
        matrix A = generate2d(N);
        string validationFile = "data.txt";
        writeMatrixToFile(validationFile, A);
        matrix B = readMatrixfromFile(validationFile);

        output_file << setw(width) << left << N;
        auto num_of_functions = vector_of_transpose_functions.size();
        
        for(auto i = 0; i < num_of_functions; i++) {
            steady_clock::time_point t1 = steady_clock::now();
            vector_of_transpose_functions[i](A, N);                         // perform the algorithm
            steady_clock::time_point t2 = steady_clock::now();
            auto time_taken = duration_cast<duration<double>>(t2 - t1);     // record the time delta
            transposeMatrixSerial(A, N);                                    // restore the original matrix
            assert(matricesAreEqual(A, B));                                 // confirm the algorithm works
            output_file << setw(width) << left << setprecision(7) << fixed << time_taken.count();
        }
        output_file << endl;
    }

	output_file.close();

	cout << "Executable Runtime: " << double( clock() - start_time) / (double) CLOCKS_PER_SEC << " seconds" << endl;
	cout << "Processing complete: created timings.txt" << endl;
}