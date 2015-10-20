//
// Created by julian on 05.10.15.
//

#ifndef MATRIX_MATRIX_H
#define MATRIX_MATRIX_H

#include "exceptions.h"


//Namespace of my Library
namespace jib {


	//class definitition of the Matrix class
    template<typename T>
    class Matrix {
    public:

    	//Constructor for different dimesnios
        Matrix(const size_t, const size_t);

        //constructor for quadratic MATRIX
        Matrix(const size_t row_colls);

        //Copy constructor
        Matrix(const Matrix& mat);

        //Move constructor
        Matrix(Matrix&& mat);

        //destructor deleting all allocated pointers unless ptr = nullptr(i.e. it has been moved)
        ~Matrix();

        //Copy operator
        Matrix& operator=(const Matrix& mat);

        //move Operator
        Matrix& operator=(Matrix&& mat);

        //subscript operator
        T *operator[](const size_t index) const;

        operator bool() const;

        size_t get_collums() const;
        size_t get_rows() const;

        //prints the values of the Matrix in Matix form using \n ..., by using operator string
        void print() const;

    private:

    	//Matrix has immutable dimensions. Number of rows, collums
        const size_t rows;
        const size_t colls;

        //Pointer to matrix. Dynamically alocated, allocated in constrcutor and deallocated
        T **ptr;


    };

    /**
     * @brief      Matrix Constructor for a quadratic MxM matrix.
     *
     * @param[in]  row_colls  dimensions(rows and collums) of my desired Matrix 
     *
     * @tparam     T          Template argument T defining the tpyes of the Matrix's coefficients
     */
    template<typename T>
    Matrix<T>::Matrix(const size_t row_colls) :
            Matrix(row_colls , row_colls) {
        ptr = new T *[rows];
        for (int i = 0; i < rows; ++i) {
            ptr[i] = new T[rows];
        }
    }

    /**
     * @brief      MAtrix constructor for a MxN Matrix where m=n or m!=n
     *
     * @param[in]  _rows   Number of Rows
     * @param[in]  _colls  Number of collums
     *
     * @tparam     T       Template argument T defining the tpyes of the Matrix's coefficients
     */
    template<typename T>
    Matrix<T>::Matrix(const size_t _rows, const size_t _colls) :
            rows{_rows},
            colls{_colls} {
        ptr = new T *[rows];
        for (int i = 0; i < colls; ++i) {
            ptr[i] = new T[colls];
        }
    }


    /**
     * @brief      Copy Constructor
     *
     * @param[in]  mat   Matrix to be copied | collums/rows(mat) = collums/rows(this)
     *
     * @tparam     T     Template argument T defining the tpyes of the Matrix's coefficients
     */
    template <typename T>
    Matrix<T>::Matrix(const jib::Matrix<T>& mat):
            Matrix{mat.rows , mat.get_collums()}
    {
        for(int i = 0;  i < this->rows ; ++i) {
            for(int j = 0; j < this->colls ; ++j) {
                ptr[i][j] = mat[i][j];
            }
        }
    }

    /**
     * @brief      Move constructor, leavs the second matrx in undefined state
     *
     * @param[in]  mat   Matrix from which should be moved
     *
     * @tparam     T          Template argument T defining the tpyes of the Matrix's coefficients
     */
    template<typename T>
    Matrix<T>::Matrix(jib::Matrix<T>&& mat):
            rows{mat.get_rows()},
            colls{mat.get_collums()}
    {
        this->ptr = mat.ptr;
        mat.ptr = nullptr;
    }

    /**
     * @brief      Cppy operator, performs a deep copy
     *
     * @param[in]  mat   Matrix from which should be copied
     *
     * @tparam     T          Template argument T defining the tpyes of the Matrix's coefficients
     */
    template <typename T>
    Matrix<T>& Matrix<T>::operator=(const jib::Matrix<T> &mat) {
        if(this->rows != mat.get_rows() || this->colls != mat.get_collums()) {
            throw jib::invalid_dimension_exception("Either collums or rows are not equal");
        }

        for(int i = 0;  i < this->rows ; ++i) {
            for(int j = 0; j < this->colls ; ++j) {
                ptr[i][j] = mat[i][j];
            }
        }
    }

     /**
     * @brief      Move operator leavs the second matrx in undefined state
     *
     * @param[in]  mat   Matrix from which should be moved
     *
     * @tparam     T          Template argument T defining the tpyes of the Matrix's coefficients
     */
    template <typename T>
    Matrix<T>& Matrix<T>::operator=(jib::Matrix<T> &&mat) {
        if(this->rows != mat.get_rows() || this->colls != mat.get_collums()) {
            throw jib::invalid_dimension_exception("Either collums or rows are not equal");
        }
        this->ptr = mat.ptr;
        mat.ptr = nullptr;
    }

    /**
     * @brief      Matrix destructor, does nothing in case the matrix has been moved	
     *
     * @tparam     T     Template argument T defining the tpyes of the Matrix's coefficients
     */
    template<typename T>
    Matrix<T>::~Matrix() {

    	//in case has been moved prior to destruction
        if(this->ptr == nullptr) {
            return;
        }

        for (int i = 0; i < rows; ++i) {
            delete[] ptr[i];
        }
        delete[] ptr;
    }

    /*
     * @brief       Subscript operator. returns an array of T-elements(rows), which again can be subscripted
     * 				In orhter word: It returns the pointer to the Nth row(array).
     *
     * @throws std::out_of_range exception in case the index is larger than the rows
     *
     *
     * @param[in]  n		Which row should be selected and returned.
     *
     * @tparam     T          Template argument T defining the tpyes of the Matrix's coefficients
     */
    template<typename T>
    T *Matrix<T>::operator[](const size_t index) const {
        if (index >= rows) throw std::out_of_range("the index is larger or equal than your number of rows");
        return this->ptr[index];
    }


    /**
     *  @brief    IF the matrix has been moved from in other words is invalid, it returns 0
     *  
     *  @tparam   T typename to deduce MAtrix type
     *  
     *  @return   returns true if matrix is valid false otherwise.
     */
    template<typename T>
    Matrix<T>::operator bool() const {
    	return (ptr==nullptr ? true : false);
    }
    /**
     * @brief      Getter for number of collums
     *
     * @tparam     T     Template argument T defining the tpyes of the Matrix's coefficients
     *
     * @return     Number of collums
     */
    template <typename T>
    size_t Matrix<T>::get_collums() const {
        return this->colls;
    }

    /**
     * @brief      Getter for number of rows
     *
     * @tparam     T     Template argument T defining the tpyes of the Matrix's coefficients
     *
     * @return     Number of Rows
     */
    template <typename T>
    size_t Matrix<T>::get_rows() const {
        return this->rows;
    }

    /**
     * @brief      Printing the each row of the matrix and appending \n after each row. Using the string overload for the coefficients
     *
     * @tparam     T     Template argument T defining the tpyes of the Matrix's coefficients
     */
    template<typename T>
    void Matrix<T>::print() const {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < colls; ++j) {
                std::cout << ptr[i][j];
            }
            std::cout << std::endl;
        }
    }





    /**
     * @brief      Matrix Mulitplication. (AB)ij = Sum Aik*Bkj. Is not commutative.
     *
     * @throws invalid_dimension_exception in case Collums(A) != Rows(B)
     *
     *
     * @param[in]  a     First Matrix
     * @param[in]  b     Second Matrix
     *
     * @tparam     T     Template argument T defining the tpyes of the Matrix's coefficients	
     *
     * @return     Returns the matrix (A*B)
     */
    template<typename T>
    Matrix<T> operator*(const Matrix<T>& matrix_A , const Matrix<T>& matrix_B) {
        if(matrix_A.get_collums() != matrix_B.get_rows()) {
            throw jib::invalid_dimension_exception("Colls of A != Rows of B");
        }


        //for the k variable needed in the 3rd loop
        auto sum_loop_iterator = matrix_A.get_collums();

        //Matrix to be returned
        Matrix<T> tmp(matrix_A.get_rows() , matrix_B.get_collums());
        
        for(int i = 0; i < tmp.get_rows() ; ++i) {
        	for(int j = 0; j < tmp.get_collums() ; ++j) {
        		for(int k = 0; k < sum_loop_iterator ; ++k) {
        			tmp[i][j]  =  matrix_A[i][k] * matrix_B[k][j];
        		}
        	}
        }
        return tmp;

    }

    /**
     * @brief      Comparison operator Checks if all coefficients on the same posistion are the same. And if dimensions are the same
     *
     * @param[in]  matrix_A  1st Matrix
     * @param[in]  matrix_B  2nd Matrix
     *
     * @tparam     T         To deduce the Matrice`s Coefficient type
     *
     * @return     returns true if for all Coeffients Aij = Bij
     */

    template<typename T>
    bool operator==(const Matrix<T>& matrix_A , const Matrix<T>& matrix_B) noexcept
    {
    	if(matrix_A.get_rows() != matrix_B.get_rows() || matrix_A.get_collums() != matrix_B.get_collums()) {
    		return false;
    	}

    	for (int i = 0; i < matrix_A.get_rows(); ++i ) {
    		for (int j = 0; j < matrix_A.get_collums(); ++i) {
    			if(matrix_A[i][j] != matrix_B[i][j]) {
    				return false;
    			}
    		}
    	}

    	return true;
    }
}


#endif //MATRIX_MATRIX_H