//exactcover.h

//EXact Cover

#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>

// using DLX (Dancing Links) technique 
  
#define MAX_ROW 1000 
#define MAX_COL 1000 
   
struct Cell 
{ 
    struct Cell *left; 
    struct Cell *right; 
    struct Cell *up; 
    struct Cell *down; 
    struct Cell *column; 

    int rowID; 
    int colID; 
    int CellCount; 
}; 

struct Cell *start;

// Matrix to contain Cells of linked mesh 
struct Cell Matrix[MAX_ROW][MAX_COL]; 
  
// Problem Matrix 
bool inputMatrix[MAX_ROW][MAX_COL];
bool inputMatrix2[MAX_ROW][MAX_COL]; 

//solution array
int solutions[MAX_ROW][MAX_COL];
int solend;
int solcol;

// Number of rows and columns in problem matrix  
int nRow,nCol; 


int RowID[729];
  
// Functions to get next index in any direction 
// for given index (circular in nature)  
int getRight(int i);
int getLeft(int i);
int getUp(int i);  
int getDown(int i);

struct Cell *createCellMatrix();

// Cover the given node completely 
void cover(struct Cell *target); 

// Uncover the given node completely 
void uncover(struct Cell *target) ;
  
// Traverse column starts right and  
// return the column having minimum  
// node count 
struct Cell *getMinColumn() ;
  
void printSolutions() ;

void solutionsadd(struct Cell *row);

void solutionsremove();
  
// Search for exact covers 
void search(int k);

void createInputMatrix(int row, int col);

