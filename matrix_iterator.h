#ifndef MATRIX_ITERATOR_H_
#define MATRIX_ITERATOR_H_

#include "matrix.h"
#include "matrix_coords.h"
#include "dictionary.h"
#include "vector.h"
namespace vika_lib {
template <typename Value>
class Matrix;

template <typename Value>
class Vector;

template <typename Value>
class Matrix_row_iterator
{
    friend class Matrix<Value>;
private:
    typedef Matrix_row_iterator<Value> This;

    Vector<Value> _vector;

    Matrix<Value> & _matrix;
    int _position;

    bool
    is_position_correct () const
    {
        if ((_position >= 0)&&(_position < _matrix._height)) {
            return true;
        } else {
            return false;
        }
    }

    Matrix_row_iterator (Matrix<Value> &matrix, int position):
    _matrix (matrix), _position (position), _vector(matrix._width)
    {
        if (is_position_correct()) {
            _vector = matrix[typename Matrix<Value>::Row_coord(position)];
        }
    }
public:

    Vector<Value> &
    operator * ()
    {
        return _vector;
    }

    friend
    bool
    operator == (const This &iter1, const This &iter2)
    {
        if ((&(iter1._matrix) == &(iter2._matrix)) && (iter1._position == iter2._position)) {
            return true;
        } else {
            return false;
        }
    }
    
    friend
    bool
    operator != (const This &iter1, const This &iter2)
    {
        return ! (iter1 == iter2);
    }

    This &
    operator += (int offset) {
        _position += offset;
        return (*this);
    }

    This &
    operator -= (int offset) {
        _position -= offset;
        return (*this);
    }

    This &
    operator ++ () {
        return (*this) += 1;
    }

    This &
    operator -- () {
        return (*this) -= 1;
    }

    void
    sync_to()
    {
        for (int i = 0; i < _vector.get_size(); i++) {
            _matrix(_position, i) = _vector(i);
        }
    }

    void
    sync_from()
    {
        _vector = _matrix[typename Matrix<Value>::Row_coord(_position)];
    }

};

template <typename Value>
class Matrix_column_iterator
{
    friend class Matrix<Value>;
private:
    typedef Matrix_row_iterator<Value> This;

    Vector<Value> _vector;

    Matrix<Value> & _matrix;
    int _position;

    bool
    is_position_correct () const
    {
        if ((_position >= 0)&&(_position < _matrix._width)) {
            return true;
        } else {
            return false;
        }
    }

    Matrix_column_iterator (Matrix<Value> &matrix, int position):
    _matrix (matrix), _position (position), _vector(matrix._width)
    {
        if (is_position_correct()) {
            _vector = matrix[typename Matrix<Value>::Column_coord(position)];
        }
    }
public:

    Vector<Value> &
    operator * ()
    {
        return _vector;
    }

    friend
    bool
    operator == (const This &iter1, const This &iter2)
    {
        if ((&(iter1._matrix) == &(iter2._matrix)) && (iter1._position == iter2._position)) {
            return true;
        } else {
            return false;
        }
    }
    
    friend
    bool
    operator != (const This &iter1, const This &iter2)
    {
        return ! (iter1 == iter2);
    }

    This &
    operator += (int offset) {
        _position += offset;
        return (*this);
    }

    This &
    operator -= (int offset) {
        _position -= offset;
        return (*this);
    }

    This &
    operator ++ () {
        return (*this) += 1;
    }

    This &
    operator -- () {
        return (*this) -= 1;
    }

    void
    sync_to()
    {
        for (int i = 0; i < _vector.get_size(); i++) {
            _matrix(_position, i) = _vector(i);
        }
    }

    void
    sync_from()
    {
        _vector = _matrix[typename Matrix<Value>::Col_coord(_position)];
    }

};
}
#endif