/*  
 *
 *   (!) Дописать: 
 *
 *       explicit Matrix (const char *)
 *       char* to_string ()
 *
 */



#ifndef MATRIX_H_
#define MATRIX_H_ 

#include "dictionary.h"
#include "matrix_coords.h"
#include "vector.h"
#include "exeption.h"
#include "matrix_iterator.h"

namespace vika_lib {

template <typename Key, typename Value>
class Dictionary;

template <typename Value>
class Matrix_row_iterator;

template <typename Value>
class Matrix_colomn_iterator;

template <typename Value>
class Matrix_key;

template <typename Value>
class Matrix_coord;

template <typename Value>
class Matrix_row_coords;

template <typename Value>
class Matrix_colomn_coords;

template <typename Value>
class Vector;

enum Matrix_create_mode
{
    ZERO   = 0,
    UNIT   = 1,
    ALLONE = 2
};

enum Matrix_orientation_mode
{
    VERTICAL   = 0,
    HORIZONTAL = 1
};

template <typename Value>
class Matrix
{
    friend class Matrix_key<Value>;
    friend class Matrix_row_iterator<Value>;
private:
    typedef Matrix<Value> This;
    typedef Matrix_key<Value> Key;
    typedef Dictionary<Key, Value> Dict;


    int _width, _height;
    Dict _dict;

    const Key
    make_key(int row, int column) const
    {
        if ((row < 0) || (row >= _height) || (column < 0) || (column >= _width)) {
            throw Exeption (MEX_OUTOFARRAY);
        }
        Key result(this, row, column);
        return result;
    }

    typename Dict::Element 
    operator() (const Key &key)
    {
        if (key._matrix != this) {
            throw MEX_COORDSFROMOTHERMATRIX;
        }
        return _dict(key);
    }

    const Value
    operator[] (const Key &key) const
    {
        if (key._matrix != this) {
            throw MEX_COORDSFROMOTHERMATRIX;
        }
        return _dict[key];
    }

public:
    typedef Matrix_coord<Value>         Coord;
    typedef Matrix_row_coord<Value>     Row_coord;
    typedef Matrix_colomn_coords<Value> Col_coord;



    Matrix (int height = 0, int width = 0, Matrix_create_mode mode = ZERO)
    {
        if ((height < 0) || (width < 0)) {
            throw Exeption(MEX_OUTOFARRAY);
        }
        _height = height;
        _width  = width;

        if (mode == UNIT) {
            int min = (height < width) ? height : width;
            for (int i = 0; i < min; ++i) {
                (*this)(i, i) = 1;
            }
        } else if (mode == ALLONE) {
            for (int i = 0; i < height; ++i) {
                for (int j = 0; j < width; ++j) {
                    (*this)(i,j) = 1;
                }
            }
        }
    }

    Matrix (const This &matrix)
    {
        _height = matrix._height;
        _width  = matrix._width;
        _dict   = matrix._dict;
    }

    explicit
    Matrix (const Vector<Value> vector, Matrix_orientation_mode mode = VERTICAL)
    {
        if (mode == VERTICAL) {
            _height = vector.get_size();
            _width  = 1;
            for (int i = 0; i < _height; ++i) {
                (*this)(i, 0) = vector[i];
            }
        } else {
            _height = 1;
            _width  = vector.get_size();
            for (int i = 0; i < _width; ++i) {
                (*this)(0, i) = vector[i];
            }
        }
    }

    This & 
    operator= (const This &matrix)
    {
        _height = matrix._height;
        _width  = matrix._width;
        _dict   = matrix._dict;
        return (*this);
    }

    typename Dict::Element
    operator() (int row, int column)
    {
        return (*this)(make_key(row, column));
    }

    typename Dict::Element
    operator() (Coord coord)
    {
        return (*this)(coord._row, coord._column);
    }

    friend
    const This
    operator+ (const This &matrix1, const This &matrix2)
    {
        if ((matrix1._height != matrix2._height) || (matrix1._width != matrix2._width)) {
            throw MEX_DIFFERENTSIZES;
        }

        This result (matrix1._height, matrix1._width);
        for (int i = 0; i < result._height; ++i) {
            for (int j = 0; j < result._width; ++j) {
                result(i, j) = matrix1[matrix1.make_key(i, j)] + matrix2[matrix2.make_key(i, j)];
            }
        }
        return result;
    }

    const This
    operator- () const
    {
        This result (this->_height, this->_width);
        for (int i = 0; i < result._height; ++i) {
            for (int j = 0; j < result._width; ++j) {
                result(i, j) = -(*this)[this->make_key(i, j)];
            }
        }
        return result;
    }

    friend
    const This
    operator- (const This &matrix1, const This &matrix2)
    {
        return matrix1 + (-matrix2);
    }

    friend
    const This
    operator * (const This &matrix1, const This &matrix2)
    {
        if (matrix1._width != matrix2._height) {
            throw MEX_DIFFERENTSIZES;
        }

        This result (matrix1._height, matrix2._width);
        for (int i = 0; i < result._height; ++i) {
            for (int j = 0; j < result._width; ++j) {
                Value sum = 0;
                for (int k = 0; k < matrix1._width; ++k) {
                    sum += matrix1[matrix1.make_key(i, k)] * matrix2[matrix2.make_key(k, j)];
                }
                result(i, j) = sum;
            }
        }

        return result;
    }

    int
    get_width () const
    {
        return _width;
    }

    int
    get_height () const
    {
        return _height;
    }

    This& 
    operator+= (const This &matrix)
    {

        (*this) = (*this) + matrix;

        return (*this);
    }

    This&
    operator-= (const This &matrix)
    {
        (*this) = (*this) - matrix;
        return (*this);
    }

    This&
    operator*= (const This &matrix)
    {
        (*this) = (*this) * matrix;
        return (*this);
    }

    const This
    operator! () const
    {
        This result(this->_width, this->_height);
        for (int i = 0; i < result._height; ++i) {
            for (int j = 0; j < result._width; ++j) {
                result(i, j) = (*this)[this->make_key(j, i)];
            }
        }

        return result;
    }

    const This 
    operator^ (int pow) const
    {
        if (pow <= 0) {
            throw MEX_POWISZEROORLESS;
        }
        This result = (*this);
        for (int i = 0; i < pow-1; ++i) {
            result *= (*this);
        }
        return result;
    }

    This&
    operator^=(int pow)
    {
        (*this) = (*this) ^ pow;
    }

    const Value
    operator[] (const Coord &coord) const
    {
        return (*this)[make_key(coord._row, coord._column)];
    }

    const Vector<Value>
    operator[] (const Row_coord &coords) const
    {
        Vector<Value> result(_width);
        for (int i = 0; i < _width; ++i) {
            result(i) = (*this)[make_key(coords._position, i)];
        }
        return result;
    }

    const Vector<Value>
    operator[] (const Matrix_column_coord<Value> &coords) const
    {
        Vector<Value> result(_height);
        for (int i = 0; i < _height; ++i) {
            result(i) = (*this)[make_key(i, coords._position)];
        }
        return result;
    }

    typedef Matrix_row_iterator<Value> Row_iterator;
    typedef Matrix_colomn_iterator<Value> Col_iterator;

    Row_iterator
    rbegin()
    {
        return Row_iterator(*this, 0);
    }

    Row_iterator
    rend()
    {
        return Row_iterator(*this, _height);
    }

    Col_iterator
    cbegin()
    {
        return Col_iterator(*this, 0);
    }

    Col_iterator
    cend()
    {
        return Col_iterator(*this, _width);
    }   

};
}
#endif