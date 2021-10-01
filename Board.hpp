#pragma once

#include "Matrix.hpp"
#include <fstream>

using namespace std;

class Board
{
private:
	Matrix<int> sudoku;
public:

	Board();
	Board(int n);
	Board(const Board &other);

	void show() const;

	int possibilities(int i, int j,bool *possible);

	void set(int m, int n, int x);

	int get(int i, int j) const;

	bool process(int& m, int& n, int& possible_ints);
	bool solved(void);

	void extract_board(const Board &other);

	void input(void);

	bool rulescheck(void); //checks if all sudoku rules are fullfilled

};

void exportSudoku(const Board &sudoku,ostream &os);
Board readSudoku(istream &is);
bool solve(Board sudoku, Board* &p);
