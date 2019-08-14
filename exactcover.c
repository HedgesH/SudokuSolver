//EXact Cover

#include "exactcover.h"

//solution array
int solutions[MAX_ROW][MAX_COL];
int solend = 0;
int solcol = 0;

// Number of rows and columns in problem matrix  
int nRow = 0,nCol = 0; 

bool finished = false;
  
// Functions to get next index in any direction 
// for given index (circular in nature)  
int getRight(int i){return (i+1) % nCol; } 
int getLeft(int i){return (i-1 < 0) ? nCol-1 : i-1 ; } 
int getUp(int i){return (i-1 < 0) ? nRow : i-1 ; }   
int getDown(int i){return (i+1) % (nRow+1); } 

struct Cell *createCellMatrix() 
{ 

    

	

    for(int i = 0; i <= nRow; i++) 
    { 
    	
        for(int j = 0; j < nCol; j++) 
        { 
           
            if(inputMatrix[i][j]) 
            { 
                int a, b; 
  
                // If it's 1, other than 1 in 0th row 
                // then count it as Cell of column  
                // and increment Cell count in column start 
              
                if(i){
                	Matrix[0][j].CellCount += 1; 
                	

                } 

               
  
                // Add pointer to column start for this  
                // column Cell 
           
                Matrix[i][j].column = &Matrix[0][j]; 
  
                // set row and column id of this Cell 
                Matrix[i][j].rowID = i; 
                Matrix[i][j].colID = j; 
  
                // Link the Cell with neighbors 
  
                // Left pointer 
                a = i; b = j;
                b = getLeft(b); 
                while(!inputMatrix[a][b] && b != j){
                	b = getLeft(b);
                }
                Matrix[i][j].left = &Matrix[i][b]; 
  
                // Right pointer 
                a = i; b = j; 
                b = getRight(b);
                while(!inputMatrix[a][b] && b != j){
                	b = getRight(b);
                }
                Matrix[i][j].right = &Matrix[i][b]; 
  
                // Up pointer 
                a = i; b = j; 
                a = getUp(a);
                while(!inputMatrix[a][b] && a != i){
                	a = getUp(a);
                }
                Matrix[i][j].up = &Matrix[a][j]; 
  
                // Down pointer
                a = i; b = j; 
                a = getDown(a);
                while(!inputMatrix[a][b] && a != i){
                	a = getDown(a);
                } 
                Matrix[i][j].down = &Matrix[a][j]; 
                
            } 
            

            

        } 
        

       
    } 
    
  
  
    // link start right pointer to column  
    // start of first column 
    start->right = &Matrix[0][0]; 
    
  
    // link start left pointer to column  
    // start of last column  
    start->left = &Matrix[0][nCol-1];
 
  
    Matrix[0][0].left = start; 
    
    Matrix[0][nCol-1].right = start;
    
    return start; 
} 

// Cover the given node completely 
void cover(struct Cell *target) 
{ 
    struct Cell *row, *rightCell; 

  

  
    // get the pointer to the start of column 
    // to which this node belong  
  
 
    struct Cell *colCell = target->column; 

  

   
  
    // unlink column start from it's neighbors 

    colCell->left->right = colCell->right; 

     

 
  
    colCell->right->left = colCell->left; 

    
  
    // Move down the column and remove each row 
    // by traversing right 
    
 
    for(row = colCell->down; row != colCell; row = row->down) 
    { 
        for(rightCell = row->right; rightCell != row; 
            rightCell = rightCell->right) 
        { 
        	
        	
            rightCell->up->down = rightCell->down; 
            
            rightCell->down->up = rightCell->up; 
       
  
            // after unlinking row node, decrement the 
            // node count in column start 
            Matrix[0][rightCell->colID].CellCount -= 1; 
           
        } 
    } 
} 
  
// Uncover the given node completely 
void uncover(struct Cell *target) 
{ 
    struct Cell *rowCell, *leftCell; 
  
    // get the pointer to the start of column 
    // to which this node belong  
    struct Cell *colCell = target->column; 
  
    // Move down the column and link back 
    // each row by traversing left 
    for(rowCell = colCell->up; rowCell != colCell; rowCell = rowCell->up) 
    { 
        for(leftCell = rowCell->left; leftCell != rowCell; 
            leftCell = leftCell->left) 
        { 
            leftCell->up->down = leftCell; 
            leftCell->down->up = leftCell; 
  
            // after linking row node, increment the 
            // node count in column start 
            Matrix[0][leftCell->colID].CellCount += 1; 
        } 
    } 
  
    // link the column start from it's neighbors 
    colCell->left->right = colCell; 
    colCell->right->left = colCell; 
} 
  
// Traverse column starts right and  
// return the column having minimum  
// node count 
struct Cell *getMinColumn() 
{ 
    struct Cell *h = start; 

    struct Cell *min_col = h->right; 

    h = h->right->right;

    
    
    if(h->CellCount < min_col->CellCount) 
        { 
            min_col = h; 
        } 
    h = h->right; 
    while(h != start){
    	

    	if(h->CellCount < min_col->CellCount) 
        { 
            min_col = h; 
        } 
        h = h->right; 
    } 
   
  
    return min_col; 
} 
  
void printSolutions() 
{ 
	//printf("solution %d on rows: ", solcol+1);
    for (int i = 0; i <solend; ++i)
    {
    	//printf("%d ", solutions[solcol][i]);
    	solutions[solcol + 1][i] = solutions[solcol][i]; 
    }
    //printf("\n");

    solutions[solcol][solend] = -1;

    solcol++;
} 

void solutionsadd(struct Cell *row){
	int r = row->rowID;
	solutions[solcol][solend] = r-1 ;
	solend++;


}

void solutionsremove(){
	solutions[solcol][solend] = 0;
	if (solend != 0) solend--;

}

void PrintLinkedList(){

	for (int i = 0; i <= nRow; ++i)
	{
		for (int j = 0; j < nCol; ++j)
		{
			
			if(inputMatrix[i][j]){
				struct Cell *h =&Matrix[i][j];


				if ((h->right->left == h && h->left->right == h) && h->up->down == h && h->down->up == h)
				{
				printf("%d ", inputMatrix[i][j] );
				}
				else printf( "N ");
			}
			else printf("0 ");

			
			

		}
		printf("\n");
	}

}
  
// Search for exact covers 
void search(int k) 
{ 
    struct Cell *rowCell; 
    struct Cell *rightCell; 
    struct Cell *leftCell; 
    struct Cell *column; 

    if (finished == true)
    {
    	return;

    }

  
    // if no column left, then we must 
    // have found the solution 
    if(start->right == start) 
    { 
        printSolutions();
        if(solcol >= 1) finished = true;
        return; 
    } 

  
  
    // choose column deterministically 

    column = getMinColumn(); 
  
    cover(column);
  	
 
    for(rowCell = column->down; rowCell != column;  
        rowCell = rowCell->down ) 
    { 
    	
        solutionsadd(rowCell);
  
        for(rightCell = rowCell->right; rightCell != rowCell; rightCell = rightCell->right){
            cover(rightCell); 
        }
            
  
        // move to level k+1 (recursively) 

        search(k+1); 

          
        // if solution in not possible, backtrack (uncover) 
        // and remove the selected row (set) from solution 

        solutionsremove();
  
        column = rowCell->column; 
        for(leftCell = rowCell->left; leftCell != rowCell;leftCell = leftCell->left){
        	uncover(leftCell);
        }
             
    } 

    

  
    uncover(column); 
} 

void createInputMatrix(int row, int col){
	nRow = row; 
    nCol = col; 

	for(int i=0; i<=nRow; i++) 
    { 
        for(int j=0; j<nCol; j++) 
        { 
            // if it's row 0, it consist of column 
            // starts. Initialize it with 1 
            if(i == 0) inputMatrix[i][j] = true; 
            else inputMatrix[i][j] = false; 
        } 
    } 

}
//s





  




  