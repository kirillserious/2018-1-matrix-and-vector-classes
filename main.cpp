#include <iostream>
#include "vector.h"
#include "matrix.h"
#include "exeption.h"

using namespace std;
using namespace vika_lib;

void print(const Vector<int> &vector)
{
    int size = vector.get_size();
    for (int i = 0; i < size; i++)
    {
        cout << vector[i] <<endl;
    }
}

void print(const Matrix<int> &matrix)
{
    for (int i = 0; i < matrix.get_height(); i++){
        for (int j = 0; j < matrix.get_width(); j++) {
            cout << matrix[Matrix<int>::Coord(i, j)] << ' ';
        }
        cout << endl;
    }
}

int main()
{  
    Vector<int> v(4, 1);
    Matrix<int> m(3,3, UNIT);
    m = Matrix<int>(v, HORIZONTAL);
    m(0, 3) = 5;
    print(m);


    return 0;
}