/// \file
/// \brief Main file for comparing time performance of in-place matrix transposition algorithms

#include <chrono>
#include <assert.h>
#include <functional>
#include "utilities.h"
#include "transpose.h"
#include "Matrix.h"

using namespace std;
using namespace std::chrono;

int main()
{
    // Overall system time elapsed
	clock_t start_time = clock();

    // Output setup
	string fileOutName = "timings.txt";
	ofstream output_file(fileOutName, ios::out | ios::trunc);
	if (!output_file.is_open()) { cerr << "Unable to open file:" << fileOutName << endl; return -1;}

    // Output column titles
	auto width = 20;
	output_file << setw(width) << left << "#N0=N1";
	output_file << setw(width) << left << "Serial";
	output_file << setw(width) << left << "OpenMP:Naive";
    output_file << setw(width) << left << "OpenMP:Diagonal";
    output_file << setw(width) << left << "Recursive Block";
	// output_file << setw(width) << left << "OpenMP:Block";
    // output_file << setw(width) << left << "PThreads:Diagonal";
	// output_file << setw(width) << left << "PThreads:Block";
	output_file << endl;

    // vector<int> sizes = {2, 4, 8, 16, 32, 64, 128, 512, 1024, 2048, 4096, 8196, 16348};
    vector<int> sizes = {128, 1024, 2048, 4096};
    // vector<int> sizes = {2, 4, 6, 8, 10};
    // vector<int> sizes = {3};

    int num_of_functions = 4;
    auto display = false;
    
    for (auto& N : sizes)
    {
        Matrix A(N);
        Matrix B(N);

        A.randomizeValues();
        string validationFile = "data.txt";
        writeMatrixToFile(validationFile, A);
        B = readMatrixfromFile(validationFile);

        output_file << setw(width) << left << N;

        if (display) { printf("\nN = %d: \n---------\n", N);}

        
        for(auto i = 0; i < num_of_functions; i++)
        {
            if (display){printf("Timing algorithm %d/%d... \n", i+1, num_of_functions);}
            
            steady_clock::time_point t1 = steady_clock::now();
            switch (i)                                                     // perform the relevant algorithm
            {
                case 0:
                    transposeMatrixSerial(A, N);
                    break;
                case 1:
                    transposeMatrixSimpleOpenMP(A, N);
                    break;
                case 2:
                    transposeMatrixDiagonalOpenMP(A, N);
                    break;
                case 3:
                    transposeMatrixBlockRecursive(A, 0, N);
                    break;
                case 4:
                    break;
                case 5:
                    break;
                default:
                    break;
            }
            steady_clock::time_point t2 = steady_clock::now();
            auto time_taken = duration_cast<duration<double>>(t2 - t1);     // record the time delta
            transposeMatrixSerial(A, N);                                    // restore the original matrix
            assert(matricesAreEqual(A, B));                                 // confirm the algorithm works
            output_file << setw(width) << left << setprecision(7) << fixed << time_taken.count();
        }
        output_file << endl;
    }

	output_file.close();

	cout << "Executable Runtime: " << double(clock() - start_time) / (double)CLOCKS_PER_SEC;
    cout << " seconds" << endl;
	cout << "Processing complete: created timings.txt" << endl;

}