#include <iostream>
#include <vector>
#include <memory>
#include "omp.h"

using namespace std;

// shared_ptr<vector<shared_ptr<vector<int>>>> generate2d(int N){
    
// }

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
    shared_ptr< std::vector< shared_ptr< std::vector<int> > > > A = make_shared<vector<shared_ptr<vector<int>>>>();
    vector<int> row1 = {1,2,3,4};
    vector<int> row2 = {5,6,7,8};
    vector<int> row3 = {9,10,11,12};
    vector<int> row4 = {13,14,15,16};

    auto row1_ptr = make_shared<vector<int>> (row1);
    auto row2_ptr = make_shared<vector<int>> (row2);
    auto row3_ptr = make_shared<vector<int>> (row3);
    auto row4_ptr = make_shared<vector<int>> (row4);

    A->push_back(row1_ptr);
    A->push_back(row2_ptr);
    A->push_back(row3_ptr);
    A->push_back(row4_ptr);

    print2d(A, 4);
    BasicAlgorithm(A, 4);
    cout << endl;
    print2d(A, 4);

    

    return 0;
}