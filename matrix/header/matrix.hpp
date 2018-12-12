#pragma once
#ifndef MATRIX
#define MATRIX

#include <vector>
#include <iostream>
#include <string.h>

namespace Matrix {
	template < typename T >
	class matrix {
	public:
		matrix(int row,int col);
		matrix(int order );
		matrix( const matrix<T>& m );//复制构造函数
		matrix& operator=(const matrix& m);//复制赋值运算符
		matrix( matrix<T>&& m);//移动构造函数
		matrix& operator=(matrix&& m);//移动赋值运算符
		virtual ~matrix();//析构函数

		int rowSize();
		int colSize();
		T& operator()(int row,int col);
		matrix<T>& operator()( const char*);
	private:
		T row;//行
		T col;//列
		enum class status {
			Ok,
			Error
		};
		struct {
			std::vector<T>* elementP;
			status statusP = status::Error;
		} element;
	};


	template < typename T >
	matrix<T>::matrix(int row, int col):row(row),col(col) {
		if ((row>0)&&(col>0)) {
			this->element.elementP = new std::vector<T>(row*col, 0);
			this->element.statusP = status::Ok;
		}
		else {
			this->element.elementP = nullptr;
			this->element.statusP = status::Error;
		}
	}
	template < typename T >
	matrix<T>::matrix(int order):matrix(order,order) {

	}
	template < typename T >
	matrix<T>::matrix( const matrix<T>& m ):row(m.row),col(m.col) {
		this->element.elementP = new std::vector<T>( *(m.element.elementP) );
		this->element.statusP = status::Ok;
	}
	template < typename T >
	matrix<T>& matrix<T>::operator=(const matrix<T>& m){
		this->row = m.row;
		this->col = m.col;
		this->element.elementP = new std::vector<T>( *(m.element.elementP) );
		this->element.statusP = status::Ok;
		return *this;
	}
	template < typename T >
	matrix<T>::matrix( matrix<T>&& m) : row(m.row), col(m.col) {
		this->element.elementP = m.element.elementP;
		this->element.statusP = status::Ok;
		m.element.elementP = nullptr;
		m.element.statusP = status::Error;
	}
	template < typename T >
	matrix<T>& matrix<T>::operator=(matrix<T>&& m) {
		this->row = m.row;
		this->col = m.col;
		this->element.elementP = m.element.elementP;
		this->element.statusP = status::Ok;
		m.element.elementP = nullptr;
		m.element.statusP  = status::Error;
		return *this;
	}
	template < typename T >
	matrix<T>::~matrix() {
		if (this->element.statusP == status::Ok) {
			delete this->element.elementP;
			this->element.statusP = status::Error;
		}
	}
	template < typename T >
	int matrix<T>::rowSize() {
		return this->row;
	}
	template < typename T >
	int matrix<T>::colSize() {
		return this->col;
	}
	template < typename T >
	T& matrix<T>::operator()(int row, int col) {
		if ((row<=0)||(col<=0)) {
			exit(0);
		}
		return (*(this->element.elementP))[(row - 1)*(this->col) + col - 1];
	}
	template < typename T >
	matrix<T>& matrix<T>::operator()( const char* c) {
		if ( !strcmp(c,"I") ) {
			for (int i = 1; i <= row; i++) {
				for (int j = 1; j <= col; j++) {
					if (i == j) {
						(*this)(i, j) = 1;
					}
					else {
						(*this)(i, j) = 0;
					}
				}
			}
		}
		else if (!strcmp(c, "T")) {
			auto tempElementP = new std::vector<T>(row*col, 0);
			for (int i = 1; i <= row; i++) {
				for (int j = 1; j <= col; j++) {
					(*tempElementP)[ (j-1)*col + i - 1 ] = (*(element.elementP))[ (i-1)*row + j - 1 ];
				}
			}
			delete element.elementP;
			element.elementP = tempElementP;
			int temp = col;
			col = row;
			row = temp;
		}
		return *this;
	}
}


template < typename T >
Matrix::matrix<T> operator+(Matrix::matrix<T>& m1, Matrix::matrix<T>& m2) {
	int row = m1.rowSize();
	int col = m1.colSize();
	auto m = Matrix::matrix<T>(row,col);
	for (int i = 1; i <= row;i++) {
		for (int j = 1; j <= col; j++) {
			m(i, j) = m1(i, j) + m2(i, j);
		}
	}
	return m;
}
template < typename T >
Matrix::matrix<T> operator*(Matrix::matrix<T>& m1, Matrix::matrix<T>& m2) {
	int row = m1.rowSize();
	int col = m1.colSize();
	auto m = Matrix::matrix<T>(row, col);
	for (int i = 1; i <= row; i++) {
		for (int j = 1; j <= col; j++) {
			T sum = 0;
			for (int k = 1; k <= m1.colSize(); k++) {
				sum += m1(i, k)*m2(k, j);
			}
			m(i, j) = sum;
		}
	}
	return m;
}
template < typename T,typename K >
Matrix::matrix<T> operator*(Matrix::matrix<T>& m1, K& m2) {
	int row = m1.rowSize();
	int col = m1.colSize();
	auto m = Matrix::matrix<T>(row, col);
	for (int i = 1; i <= row; i++) {
		for (int j = 1; j <= col; j++) {
			m(i, j) = m1(i,j)*m2;
		}
	}
	return m;
}
template < typename T, typename K >
Matrix::matrix<T> operator*(K& m2, Matrix::matrix<T>& m1) {
	return m1 * m2;
}
template < typename T >
std::ostream& operator<<(std::ostream& os, Matrix::matrix<T>& m) {
	int row = m.rowSize();
	int col = m.colSize();
	for (int i = 1; i <= row; i++) {
		for (int j = 1; j <= col; j++) {
			os << m(i, j);
			os << ' ';
		}
		os << std::endl;
	}
	return os;
}
template < typename T >
std::ostream& operator<<(std::ostream& os, Matrix::matrix<T>&& m) {
	int row = m.rowSize();
	int col = m.colSize();
	for (int i = 1; i <= row; i++) {
		for (int j = 1; j <= col; j++) {
			os << m(i, j);
			os << ' ';
		}
		os << std::endl;
	}
	return os;
}
#endif //MATRIX