#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <iostream>

using namespace std;

template <typename Typ>
class Matrix {
private:
	int m, n;
	Typ* p;
	int index(int r, int c) const {
		r--;
		c--;
		return r * n + c;
	}
public:

	Matrix(){
		m = 9;
		n = 9;
		p = new Typ[m * n];
		for (int i = 0; i < (m * n); i++)
			p[i] = 0; //fill all entries with zero
	}

	Matrix(int a, int b) {
		m = a;
		n = b;
		p = new Typ[a * b]; //frees m*n space


		for (int i = 0; i < (a * b); i++)
			p[i] = 0; //fill all entries with zero
	}

	Matrix(const Matrix<Typ> &other){
		/*Copy Constructor, assures sucessful copy*/
		m = other.m;
		n = other.n;
		p = new Typ[m*n];

		for (int i=0; i < (m*n); i++)
			p[i] = other.p[i];
	}

	Matrix(int a, int b, Typ c) {
		/*Sets all entries to value C*/
		m = a;
		n = b;
		p = new Typ[a * b]; //frees m*n space
		for (int i = 0; i < (a*b); i++)
			p[i] = c;
	}

	~Matrix(){
		delete[] p;
	}

	void set(int row, int col, Typ x) {
		/* Sets x value to entry row, col*/
		p[index(row, col)] = x;
	}

	Typ get(int row, int col) const {
		/* Gets value entry row, col*/
		return p[index(row, col)];
	}

	void print(void) const {
		/*Prints the matrix*/
		cout << "Matrix state is:" << endl;
		for (int i = 1; i <= m; i++) {
			for (int j = 1; j <= n; j++) {
				cout << get(i, j) << "     ";
			}
			cout << endl;
		}
	}

	int getRow(void) const {
		/*Returns Number of matrix rows*/
		return m;
	}

	int getCol(void) const {
		/* Return number of matrix columns*/
		return n;
	}

	void input(void) {
		/* Asks the user to fill in the matrix manually with user input*/
		Typ in;
		cout << "Inputting Matrix..." << endl;
		for (int i = 1; i <= m; i++) {
			for (int j = 1; j <= n; j++) {
				cin >> in;
				set(i, j, in);
				cout << "   ";
			}
			cout << endl;
		}
	}
	Matrix<Typ>& operator=(const Matrix<Typ> & copy) {
		/*Assures sucessful matrix copying*/
		delete[] p; //Deletes old allocated p space
		m = copy.m;
		n = copy.n;
		p = new Typ[m*n];

		for (int i=0; i < (m*n); i++)
			p[i] = copy.p[i];

		return *this;
	}
};



#endif
