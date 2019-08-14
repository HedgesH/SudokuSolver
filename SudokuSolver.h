//SudokoSolver.h


#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "exactcover.h"
#include <time.h>




int size;
int sudokuMatrix[9][9];

//a simple structure for holding coordinates
struct coords{
	int x;
	int y;
};


//prints a size x size sudoku puzzle
void printSudokuMatrix();

//creates the sudoku board
void createSudokuMatrix(int** array);

//prints the exact cover form of the sudoku puzzle
void printInputMatrix();

//creates a matrix
int** matrixMaker(int rowsize,int colsize);

//turns the exact cover row into coordinates, f | N -> N*N
struct coords *coordinates(int row);

//given the row, it will then work out the coordinates, followed by the sudoku region
int region(int row);

//the position constraint on a sudoku puzzle
void Constraint1(int row);

//the row constraint on a sudoku puzzle
void Constraint2(int row);

//the column constraint on a sudoku puzzle
void Constraint3(int row);


//the region constraint on a sudoku puzzle
void Constraint4(int row);

//given the coordinates and the position, it returns the exact cover row f| N*N*N -> N
int sudokuStateToNumber(int row, int col, int val);

//for an inputted sudoku puzzle, this covers rows and cols in the exact cover matrix associated with the numbers in each box
int coverRows(int r );

//creates the exact cover of an empty board

void basesudokucover();

//searches sudoku board for inputted values and performs coverRows
void reduceSudokuCover();

//given a row, this gives you its row coordinate
int firstcoord(int i);

//given a row, this gives you its column coordinate
int secondcoord(int i);

//given a row, this gives you its value
int inputValues(int i);


//these two functions validate the solution, technically it should never be wrong
bool validityrowcolchecker();

bool validtyregchecker();

//fills the sudoku randomly
void randomMatrixFill();


//this prints out the solutions
int solutionsIntoSudokuMatrix();

//blank sudoku board for testing

void inputBlankSudoku();


//input values onto 9x9 sudoku board
void inputSudoku();

int test4x4Sudoku();

int test9x9Sudoku();

