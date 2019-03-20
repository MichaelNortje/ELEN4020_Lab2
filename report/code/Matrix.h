#ifndef MATRIX_H
#define MATRIX_H
/// \file
/// \brief Matrix class for 1D aray representation as a 2D array

#include <memory>

class Matrix
{ 
    uint32_t* array; 
    int width;

public:
    Matrix(int N) : width(N),
                    array(new uint32_t[N * N]) {}

    int at(int x, int y)
    {
        return array[_index(x, y)];
    }

    int size()
    {
        return width;
    }

    void set(int x, int y, uint32_t val)
    {
        array[_index(x, y)] = val;
    }

    void randomizeValues()
    {
        srand (static_cast<unsigned int>(time(NULL)));
        for(size_t i = 0; i < width*width; i++){
            this->array[i] = rand() % width;
        }
    }

    void swap(int x, int y)
    {
        int32_t temp = this->at(x, y);
        this->set(x, y, this->at(y, x));
        this->set(y, x, temp);
    }

protected:
    int _index(int x, int y) const
    {
        return x + width * y; 
    } 
};

#endif