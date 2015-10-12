//
// Created by julian on 05.10.15.
//

#ifndef MATRIX_MATRIX_H
#define MATRIX_MATRIX_H

#include "exceptions.h"

namespace myLib {

    template<typename T>
    class Matrix {
    public:
        Matrix(const size_t, const size_t);
        Matrix(const size_t row_colls);
        Matrix(const Matrix& mat);
        Matrix(Matrix&& mat);

        ~Matrix();

        Matrix& operator=(const Matrix& mat);
        Matrix& operator=(Matrix&& mat);

        T *operator[](const size_t index) const;


        size_t get_collums() const;
        size_t get_rows() const;


        void print() const;

    private:
        const size_t rows;
        const size_t colls;
        T **ptr;


    };

    template<typename T>
    Matrix<T>::Matrix(const size_t row_colls) :
            Matrix(row_colls , row_colls) {
        ptr = new T *[rows];
        for (int i = 0; i < rows; ++i) {
            ptr[i] = new T[rows];
        }
    }


    template<typename T>
    Matrix<T>::Matrix(const size_t _rows, const size_t _colls) :
            rows{_rows},
            colls{_colls} {
        ptr = new T *[rows];
        for (int i = 0; i < colls; ++i) {
            ptr[i] = new T[colls];
        }
    }

    template <typename T>
    Matrix<T>::Matrix(const myLib::Matrix<T>& mat):
            Matrix{mat.rows , mat.get_collums()}
    {
        for(int i = 0;  i < this->rows ; ++i) {
            for(int j = 0; j < this->colls ; ++j) {
                ptr[i][j] = mat[i][j];
            }
        }
    }

    template<typename T>
    Matrix<T>::Matrix(myLib::Matrix<T>&& mat):
            rows{mat.get_rows()},
            colls{mat.get_collums()}
    {
        this->ptr = mat.ptr;
        this->ptr = nullptr;
    }

    template <typename T>
    Matrix<T>& Matrix<T>::operator=(const myLib::Matrix<T> &mat) {
        if(this->rows != mat.get_rows() || this->colls != mat.get_collums()) {
            throw myLib::invalid_dimension_exception("Either collums or rows are not equal");
        }

        for(int i = 0;  i < this->rows ; ++i) {
            for(int j = 0; j < this->colls ; ++j) {
                ptr[i][j] = mat[i][j];
            }
        }
    }


    template <typename T>
    Matrix<T>& Matrix<T>::operator=(myLib::Matrix<T> &&mat) {
        if(this->rows != mat.get_rows() || this->colls != mat.get_collums()) {
            throw myLib::invalid_dimension_exception("Either collums or rows are not equal");
        }
        this->ptr = mat.ptr;
        this->ptr = nullptr;
    }


    template<typename T>
    Matrix<T>::~Matrix() {

        if(this->ptr == nullptr) {
            return;
        }

        for (int i = 0; i < rows; ++i) {
            delete[] ptr[i];
        }
        delete[] ptr;
    }


    template<typename T>
    T *Matrix<T>::operator[](const size_t index) const {
        if (index >= rows) throw std::out_of_range("the index is larger or equal than your number of rows");
        return this->ptr[index];
    }

    template <typename T>
    size_t Matrix<T>::get_collums() const {
        return this->colls;
    }

    template <typename T>
    size_t Matrix<T>::get_rows() const {
        return this->rows;
    }

    template<typename T>
    void Matrix<T>::print() const {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < colls; ++j) {
                std::cout << ptr[i][j];
            }
            std::cout << std::endl;
        }
    }


    template<typename T>
    Matrix<T> operator*(const Matrix<T>& a , const Matrix<T>& b) {
        if(a.get_collums() != b.get_rows()) {
            throw myLib::invalid_dimension_exception("Colls of A != Rows of B");
        }
        Matrix<T> tmp(a.get_rows() , b.get_collums());



    }
}
#endif //MATRIX_MATRIX_H
