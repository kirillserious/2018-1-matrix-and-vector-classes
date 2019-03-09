/*  
 *
 *   (!) Дописать: 
 *
 *       explicit Vector (const char *)
 *       char* to_string ()
 *
 */


#ifndef VECTOR_H_
#define VECTOR_H_

#include "dictionary.h"
#include "exeption.h"
#include "matrix.h"

namespace vika_lib {

template <typename Key, typename Value>
class Dictionary;

template <typename Value>
class Matrix;

template <typename Value>
class Matrix_coord;


template <typename Value>
class Vector
{
private:
    typedef Vector<Value> This;
    typedef Dictionary<int, Value> Dict;

    Dict _dict;
    int _size;

public:

    Vector (int size = 0, int is_unit = 0)
    {
        if (size < 0) {
                throw Exeption(VEX_OUTOFARRAY);
        }
        _size = size;
        if (is_unit != 0) {
                for (int i = 0; i < size; ++i) {
                    (*this)(i) = 1;
                }
        }
    }

    Vector (const This &vector):
    _size(vector._size), _dict(vector._dict)
    {}

    This &
    operator= (const This &vector)
    {
        _size = vector._size;
        _dict = vector._dict;
        return *this;
    }

    Value
    operator[] (int position) const
    {
        if ((position >= _size) || (position < 0)) {
            throw Exeption(VEX_OUTOFARRAY);
        }
        return _dict[position];
    }

    typename Dict::Element
    operator() (int position) {
        if ((position >= _size) || (position < 0)) {
            throw Exeption(VEX_OUTOFARRAY);
        }
        return _dict(position);
    }

    const This
    operator- () const
    {
        This result = *this;
        for (int i = 0; i < _size; i++) {
            result(i) = -(*this)[i];
        }
        return result;
    }

    friend
    const This
    operator+ (const This &vector1, const This &vector2)
    {
        if (vector1._size != vector2._size) {
            throw Exeption(VEX_DIFFERENTSIZES);
        }

        This result(vector1._size);
        for (int i = 0; i < result._size; i++) {
            result(i) = vector1[i] + vector2[i];
        }

        return result;
    }

    friend
    const This
    operator- (const This &vector1, const This &vector2)
    {
        This result = vector1 + (-vector2);
        return result;
    }

    friend
    const This
    operator* (const This &vector, const Value &number)
    {
        This result(vector._size);
        for (int i = 0; i < result._size; i++) {
            result(i) = result[i] * number;
        }
        return result;
    }

    friend
    const This
    operator* (const Value &number, const This &vector)
    {
        return vector * number;
    }

    friend
    const This
    operator/ (const This &vector, const Value &number)
    {
        This result(vector._size);
        for (int i = 0; i < result._size; i++) {
            result(i) = result[i] / number;
        }
        return result;
    }

    friend
    const Value
    operator* (const This &vector1, const This &vector2)
    {
        if (vector1._size != vector2._size) {
            throw Exeption(VEX_DIFFERENTSIZES);
        }

        Value result = 0;
        for (int i = 0; i < vector1._size; i++) {
            result += vector1[i] * vector2[i];
        }

        return result;
    }

    friend
    const This
    operator* (const Matrix<Value> &matrix, const This& vector)
    {
        if (matrix.get_width() != vector.get_size()){
            throw Exeption(VEX_DIFFERENTSIZES);
        }

        This result(matrix.get_height());
        for (int i = 0; i < result._size; ++i) {

            Value sum = 0;
            for (int j = 0; j < vector._size; ++j) {
                sum += matrix[Matrix<Value>::Coord(i, j)] * vector[j];
            }
            result(i) = sum;
        }
    }

    This& 
    operator+= (const This &vector)
    {
        (*this) = (*this) + vector;
        return (*this);
    }

    This&
    operator-= (const This &vector)
    {
        (*this) = (*this) - vector;
        return (*this);
    }

    This&
    operator*= (const Value &number)
    {
        (*this) = (*this) * number;
        return (*this);
    }

    This& 
    operator/= (const Value &number)
    {
        (*this) = (*this) / number;
        return (*this);
    }

    int
    get_size() const
    {
        return _size;
    }
};
}
#endif
