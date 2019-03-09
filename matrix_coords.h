#ifndef MATRIX_COORDS_H_
#define MATRIX_COORDS_H_

#include "dictionary.h"
#include "matrix.h"
namespace vika_lib {
template <typename Value>
class Matrix;

template <typename Key, typename Value>
class Dictionary;

template <typename Value>
class Matrix_key
{
    friend class Matrix<Value>;
    friend class Dictionary<Matrix_key, Value>;

private:
    int _row, _column;
    const Matrix<Value> *_matrix;

    Matrix_key (const Matrix<Value>* matrix = nullptr, int row = 0, int column = 0):
    _matrix (matrix), _row (row), _column (column)
    {}
    
    int
    abs () const
    {
        if (_matrix != nullptr)
            return _row * _matrix->_width + _column;
        return 0;
    }

    friend  bool  operator==  (const Matrix_key<Value>& coords1, const Matrix_key<Value>& coords2)
    {
        if (coords1.abs() == coords2.abs()) {
            return true;
        } else {
            return false;
        }
    }

    friend  bool  operator!=  (const Matrix_key<Value> &coords1, const Matrix_key<Value> &coords2)
    {
        return !(coords1 == coords2);
    }

    friend  bool  operator>   (const Matrix_key<Value>& coords1, const Matrix_key<Value>& coords2)
    {
        if (coords1.abs() > coords2.abs()) {
            return true;
        } else {
            return false;
        }
    }

    friend  bool  operator<   (const Matrix_key<Value>& coords1, const Matrix_key<Value>& coords2)
    {
        if (coords1.abs() < coords2.abs()) {
            return true;
        } else {
            return false;
        }
    }

};

template <typename Value>
class Matrix_row_coord
{
    friend class Matrix<Value>;
private:
    int _position;
public:
    explicit Matrix_row_coord(int position):
    _position(position)
    {}
};

template <typename Value>
class Matrix_column_coord
{
    friend class Matrix<Value>;
private:
    int _position;
public:
    explicit Matrix_column_coord(int position):
    _position(position)
    {}
};

template <typename Value>
class Matrix_coord
{
    friend class Matrix<Value>;
private:
    int _row;
    int _column;
public:
    explicit Matrix_coord(int row, int column):
    _row(row), _column(column)
    {}
};
}
#endif