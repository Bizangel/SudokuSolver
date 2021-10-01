#include "Board.hpp"

Board::Board() {
	/*Initilalizes a Board object, filled with numbers 1-81*/
	int index = 1;
	for (int i = 1; i <= 9; i++) {
		for (int j = 1; j <= 9; j++) {
			sudoku.set(i, j, index);
			index++;
		}
	}
}

Board::Board(int n) {
	/*Initilalizes a Board object, filles all entries with value n*/
	for (int i = 1; i <= 9; i++)
		for (int j = 1; j <= 9; j++)
			sudoku.set(i, j, n);

}
Board::Board(const Board &other) {
		/*Copy Constructor, uses equal operator overload that ensures copying*/
		sudoku = other.sudoku;
}

void Board::show() const {
	/*Prints the sudoku board in a friendly way*/
	for (int j = 1; j <= 9; j++) {
		for (int i = 1; i <= 9; i++) {
			if (sudoku.get(j, i) == 0) {
				cout << "  ";
			}
			else {
				cout << sudoku.get(j, i) << " ";
			}
			if (i == 3 || i == 6) { cout << "|"; }
		}
		cout << endl;
		if (j == 3 || j == 6) {
			cout << "--------------------" << endl;
		}
	}
}

int Board::possibilities(const int i,const int j, bool *possible) {
	/* Receives an i and j entry cell and a bool array used to represent if number is possible or not
	if returned integer > 0, means that IS the only possibility in i j cell
	if returned integer == 0, means there was a contradiction found
	if returned integer < 0, means that there is -n different possiblities in the i j cell

	NOT TO BE CALLED ON ALREADY FILLED CELLS.*/

	for (int n = 0; n < 10; n++)  //Check for all possible digits
		possible[n] = true; //Suppose they're all true

	int m2 = (i-1)/3;
	int n2 = (j-1)/3;
	m2*=3;
	n2*=3;
	for (int value = 1; value < 10; value++) {
		//Check all three rules for each possiblity
		//Check row
		for (int n = 1; n <= 9; n++) {
			if (value == sudoku.get(i, n) && n != j) { //Means it is NOT a possiblity
				possible[value] = false; //Number in row
				break;
			}
		}
		if (possible[value] == false) { continue; } //It's already false, check next number
		//Check column
		for (int n = 1; n <= 9; n++) {
			if (value == sudoku.get(n, j) && n != i) { //Means it is NOT a possiblity
				possible[value] = false; //Number in column
				break;
			}
		}
		if (possible[value] == false) { continue; } //It's already false, check next number
		//Check 3x3 square
		for (int i2=1; i2 <= 3; i2++){
      for (int j2=1; j2 <= 3; j2++){
				 if (value == sudoku.get((m2+i2),(n2+j2)) && ((m2+i2) != i || (n2+j2) != j)){
					 possible[value] = false;
					 break;
				 }
			}
		}
	}
	int candidate;
	int counter=0;
	for (int n = 1; n <= 9; n++){
		if (possible[n]) {
			candidate = n;
			counter++;
		}
	}
	if (counter == 1) { return candidate; } //Means there is only a single possiblity, return it.
	else if (counter == 0) { return 0; } //Not a single possiblity, means CONTRADICTION =><= Backtrack.
	else {
		return -counter; //return the counter, but as a negative number to express possiblities.
	}
}


void Board::set(int m, int n, int x) {
	/*Sets x on entry i j */
	sudoku.set(m, n, x);
}

int Board::get(int i, int j) const {
	/*Gets entry i j value*/
	return sudoku.get(i, j);
}

bool Board::process(int& best_i, int& best_j, int& possible_ints) {
	/*Processes board, solves sudoku as much WITHOUT supposing, only basing on rules,
	when no longer able to solve, saves on best_i and best_j the i j entry with less possibilities*/


	bool poss[10];
	int poss_int;
	int best_possible = 10;

	for (int i = 1; i <= 9; i++) {
		for (int j = 1; j <= 9; j++) {
			if (get(i, j) == 0) {//Solve
				//there is a single one that is not full, so NOT solved
				poss_int = possibilities(i, j, poss);
				if (poss_int > 0) { //Number found
					set(i, j, poss_int); //Set and reset scan again
					i = 1; j = 0;
				}
				else if (poss_int < 0) {
					poss_int = -poss_int;
					if (poss_int < best_possible) { //Is a better possibility
						best_possible = poss_int;
						best_i = i;
						best_j = j;
					}
				}
				else if (poss_int == 0) {//Means there is a contradiction, return false
					return false;
				}
			}
		}
	}
	possible_ints = best_possible;
	return true;
}

bool Board::solved(void) {
	/*Returns true if board all cells are filled*/
	for (int i = 1; i <= 9; i++) {
		for (int j = 1; j <= 9; j++) {
			if (get(i, j) == 0) { return false; }
		}
	}
	return true;
}

void Board::extract_board(const Board &other) {
	/*Copies other board values to self*/
	for (int i = 1; i <= 9; i++)
		for (int j = 1; j <= 9; j++)
			set(i, j, other.get(i, j));
}

void Board::input(void){
	/*Allows user to input manually the 9x9 Board values*/
	sudoku.input();
}

void exportSudoku(const Board &sudoku,ostream &os){
		/*Writes board to an ostream object*/
    for (int  i = 1; i < 10; i++)
        for(int j = 1; j < 10;j++)
            os << sudoku.get(i,j);

}

Board readSudoku(istream &is){
		/*Reads 9x9(81) characters from istream object and copies respective values to self Board*/
    Board returnBoard; //9x9 by default
    int indexer = 0;
    while (indexer < 81){
        returnBoard.set(indexer/9+1,indexer%9+1, int( is.get() - '0' ) );
        //cout << indexer/9 << "-" << indexer%9 << "  " << int( is.get() - '0' ) << endl;
        indexer++;
    }
    return returnBoard;
}


bool Board::rulescheck(void){
	/*Checks that all Sudoku Property rules are fullfilled, returns false if any of the rules are not satisfied*/
	bool checked[10];
	int val;
	/*Check rows*/
	for (int row = 1 ; row < 10; row++){
		for (int i = 0; i < 10; i++){
			checked[i] = true;
		}
		for (int i = 1; i < 10; i++){
			val = get(row,i);
			if (val != 0){
				if (val != 0 && checked[val] == true){checked[val] = false;}
				else {return false;} //didn't make it
			}
		}
	}
	/*Check Columns */
	for (int col=1; col < 10; col++){

		for(int i = 0; i < 10; i++){
			checked[i] = true;
		}

		for (int i = 1; i < 10; i++){
			val = get(i,col);
			if (val != 0){
				if (checked[val] == true){checked[val] = false;}
				else {return false;} //didn't make it
			}
		}
	}
	/*Check 3x3 squares*/
	for (int rowgrid = 0; rowgrid < 3; rowgrid++){
		for (int colgrid = 0; colgrid < 3; colgrid++){
			for(int i = 0; i < 10; i++){
				checked[i] = true;
			}
			for (int i = 0; i < 3; i++){
				for (int j = 0; j < 3; j++){
					val = get(rowgrid*3+i+1,colgrid*3+j+1);
					if (val != 0){
						if (checked[val] == true){checked[val] = false;}
						else {return false;} //didn't make it
					}
				}
			}
		}
	}
	return true; //if completed every check
}

bool solve(Board sudoku, Board* &p) {
	/*Solves a sudoku Board, new solved board is created on pointer p*/
	if (sudoku.solved()) { //Check if all entries are filled
		if (sudoku.rulescheck()){//Check IF truly Solved
			p = new Board;
			*p = sudoku;
			return true;
		}
		else{return false;} //not truly solved
	}
	else {
		int best_i,best_j,n_possibilities;
		bool no_contradiction = sudoku.process(best_i, best_j, n_possibilities);
		if (no_contradiction) {
			bool possibilities[10];
			sudoku.possibilities(best_i, best_j, possibilities); //get best i and j possibilities
			for (int i = 1; i <= 9; i++) {
				if (possibilities[i] == true) { //try it
					Board maybe(sudoku); //create copy of sudoku named maybe
					maybe.set(best_i, best_j, i); //Take the assumption, on maybe
					if (solve(maybe,p) == true) { //If not contradicted
						return true;
					}
					else { //failed to find solution
						possibilities[i] = false;
						i = 0; //try again
					}
				}
			}
			return false;
		}
		else { //contradiction, return false
			return false;
		}
	}
}
