#include "Board.hpp"
#include <iostream>

using namespace std;

int main(void)
{
	/*Objective is to solve a 9x9 sudoku
		Empty squares will be represented with 0 */

	Board sudoku(0); //Creates empty sudoku

	/*Reads sudoku from File*/
	filebuf file;
  if (file.open("sudoku.dat",ios::in)){
    istream is(&file);
    sudoku = readSudoku(is);
    file.close();
  }

	Board* Solved_Sudoku=nullptr;
	if (sudoku.rulescheck()){ //Check if sudoku is viable for solving
		solve(sudoku,Solved_Sudoku); //Solve sudoku
	}

	/*Export solution to solved.dat, if found*/
	filebuf out;
	file.open("solved.dat",ios::out);
	ostream os(&file);

	if (Solved_Sudoku == nullptr){
		os << 'F' ; //No solution
	}
	else{
		exportSudoku(*Solved_Sudoku,os);
	}
	return 0;
}
