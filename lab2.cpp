#include <iostream>
#include <vector>
#include <memory>
#include <ctime>
#include "omp.h"


using namespace std;

shared_ptr<vector<shared_ptr<vector<int>>>> generate2d(int N){
    srand(time(NULL));
    shared_ptr<vector<shared_ptr<vector<int>>>> A = make_shared<vector<shared_ptr<vector<int>>>>();
    for (int i = 0; i < N; i++){
        vector<int> row;
        for (int j = 0; j < N; j++){
            row.push_back(rand() % N);
        }
        auto row_ptr = make_shared<vector<int>> (row);
        A->push_back(row_ptr);
    }
    return A;
}

void print2d(shared_ptr<vector<shared_ptr<vector<int>>>> A, int N){
    for (auto i = 0; i < N; i++){
        for (auto j = 0; j < N; j++){
            cout << A->at(i)->at(j) << "\t";
        }
        cout << "\n";
    }
}

void BasicAlgorithm(shared_ptr<vector<shared_ptr<vector<int>>>> A, int N){
    #pragma omp parallel for
    for (auto i = 0; i < N; i++){
        #pragma omp parallel for
        for (auto j = 0; j < i; j++){
            int temp = A->at(i)->at(j);
            A->at(i)->at(j) = A->at(j)->at(i);
            A->at(j)->at(i) = temp;
        }
    }
}

int main(){
    int N = 4;
    
    shared_ptr<vector<shared_ptr<vector<int>>>> A = generate2d(N);

    print2d(A, N);
    BasicAlgorithm(A, N);
    cout << endl;
    print2d(A, N);

    return 0;
}