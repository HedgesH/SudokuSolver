//inputsudokumatrix
#include "SudokuSolver.h"



int size = 4;
int sudokuMatrix[9][9];

//a simple structure for holding coordinates

//prints a size x size sudoku puzzle
void printSudokuMatrix(){

	for(int i=0; i<size; i++) 
    { 
        for(int j=0; j<size; j++) 
        { 
        	if (sudokuMatrix[i][j] == 0) printf("X ");
        	else printf("%d ", sudokuMatrix[i][j]); 
        	if((j+1)%(int)sqrt(size) == 0) printf(" ");


            
        } 
        if((i+1)%(int)sqrt(size) == 0) printf("\n");
        printf("\n");
    } 

    printf("\n");

}


//creates the sudoku board
void createSudokuMatrix(int** array){
 

	for(int i=0; i<size; i++) 
    { 
        for(int j=0; j<size; j++) 
        { 
     		sudokuMatrix[i][j] = *(*(array + j) + i); 
        } 
    } 
  	
}

//prints the exact cover form of the sudoku puzzle
void printInputMatrix(){

	for(int i=0; i<=nRow; i++) 
    { 
        for(int j=0; j<nCol; j++) 
        { 

            printf("%d ", inputMatrix[i][j]); 
        } 
        printf("\n");
    } 

}

//creates a matrix
int** matrixMaker(int rowsize,int colsize){
	int **matrixArray;
	matrixArray = malloc(colsize * sizeof (int*));
	for (int k = 0; k < colsize; k++) {
    	*(matrixArray+k) = malloc(rowsize * sizeof (int));
    	for (int i = 0; i < rowsize; ++i)
    	{
    		*(matrixArray[k] + i)  = 0;
    	}
	}	

    return matrixArray;
}

//turns the exact cover row into coordinates, f | N -> N*N
struct coords *coordinates(int row){
	struct coords *c = malloc(sizeof(struct coords));
	int z = (row / size );
	int x,y;

	if( z % (size*size) == 0 && (z != 0)) x = z/(size*size);
	else x = (row/(size*size)) + 1;

	if( z % (size) == 0 && (z != 0)) y = ((z) % (size)) + 1;
	else y = (z % (size)) + 1;

	c->x = x;
	c->y = y;

	return c;
}

//given the row, it will then work out the coordinates, followed by the sudoku region
int region(int row){
	struct coords *c = coordinates(row);
	int x,y;
	x = c->x;
	y = c->y;

	free(c);

	int z,w;
	z= ((x-1)/(int)sqrt(size)) + 1;
	w = ((y-1)/(int)sqrt(size)) + 1;
	return (((z-1) * sqrt(size)) + w );
}

//the position constraint on a sudoku puzzle
void Constraint1(int row){
	int sum = row;


	


	//SudokuExactCover[row][sum/(size)] = 1;
	inputMatrix[row + 1 ][sum/(size)] = 1;


}

//the row constraint on a sudoku puzzle
void Constraint2(int row){
	int sum = row;

	
	inputMatrix[row + 1 ][(size*size) +  ((sum) % size) + (size*(sum/(size*size))) ] = 1;

	
}

//the column constraint on a sudoku puzzle
void Constraint3(int row){
	int sum = row;

	
	inputMatrix[row + 1][2*(size*size) + ((sum) % (size*size))] = 1;
}


//the region constraint on a sudoku puzzle
void Constraint4(int row){
	int sum = row;
	int a = region(row);
	int b = 3*(size*size) + ((sum) % (size)) + size*(a-1) ;
	
	inputMatrix[row +1][b] = 1;
	
}

//given the coordinates and the position, it returns the exact cover row f| N*N*N -> N
int sudokuStateToNumber(int row, int col, int val){
	//cs row and col
	int x = col + 1;
	int y = row + 1;

	return (size*size*(y-1)) + (size*x) + val - size-1;

}

//for an inputted sudoku puzzle, this covers rows and cols in the exact cover matrix associated with the numbers in each box
int coverRows(int r ){
	int right = (r) / size;





	struct Cell *rowCell = &Matrix[r+1][right];

	struct Cell *tempCell = rowCell;

	solutionsadd(&Matrix[r+1][right]);

	cover(rowCell);


	for (rowCell = rowCell->right ; rowCell != tempCell; rowCell = rowCell->right)
	{
		cover(rowCell);

	}




	


	


	return -1;
	
}

//creates the exact cover of an empty board

void basesudokucover(){

	nCol = size*size*4;

	

	nRow = size*size*size;


	for (int i = 0; i < nCol ; ++i)
	{
		inputMatrix[0][i] = 1;

	}


	


	for (int i = 0; i <= nRow; ++i)
	{

		

		for (int j = 0; j < nCol; ++j)
		{
			inputMatrix[i+1][j] = 0;


		}

		


		
		
		Constraint1(i);
		Constraint2(i);
		Constraint3(i);
		Constraint4(i);
		

	
	}

	
}

//searches sudoku board for inputted values and performs coverRows
void reduceSudokuCover(){

	
	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < size; ++j)
		{
			int num = sudokuMatrix[i][j];

			if(num !=0){

				int row = sudokuStateToNumber(i,j,num);

				

				coverRows(row);



			}
			
			



		}
	}

}

//given a row, this gives you its row coordinate
int firstcoord(int i){ return i / (size*size);}

//given a row, this gives you its column coordinate
int secondcoord(int i){ return (i / size) % size;}

//given a row, this gives you its value
int inputValues(int i) { return (i % size) + 1;}


//these two functions validate the solution, technically it should never be wrong
bool validityrowcolchecker(int s){
	int array1[s];
	int array2[s];



	for (int i = 0; i < s; ++i)
	{
		for (int  j= 0; j < s; ++j)
		{	

			for (int k = 0; k < j; ++k)
			{
				if(array1[k] != 0 && array2[k]){
					if (array1[k] == sudokuMatrix[i][j] || array2[k] == sudokuMatrix[j][i])
					{
						

						return false;
					}

				}
				
			}

			array1[j] = sudokuMatrix[i][j];
			array2[j] = sudokuMatrix[j][i];

		}
		
	}

	return true;
}

bool validtyregchecker(){

	int regs = size;
	int counter = 0;
	int mod = (int)sqrt(size);

	while(counter != regs){

		int y = (counter / (int)sqrt(size)) ;
		int counter2 = 0;
		int array[size];

		for (int i = y*mod; i < (mod*y) + mod; ++i)
		{
	
			for (int j = mod*(counter%mod) ; j < (counter%mod)*mod + mod; ++j)
			{
				array[counter2] = sudokuMatrix[i][j];
			
				counter2++;
				
			}
		}

		for (int i = 0; i < size; ++i)
		{
			for (int j = 0; j < size; ++j)
			{
				if (array[i] == array[j] && i!=j)
				{
					return false;
				}
			}
		}

		counter++;
		





	}

	return  true;

}

//fills the sudoku randomly
void randomMatrixFill(){
	

	for (int i = 0; i < size; ++i)
	{
		int x = rand() % size;

		int y = rand() % size;


		sudokuMatrix[y][x] = i;

		if (validityrowcolchecker(size) == false)
		{
			sudokuMatrix[y][x] = 0;
			i--;
		}
		
	}


}


//this prints out the solutions
int solutionsIntoSudokuMatrix(){

	if(solcol == 0){
		printf("There are no solutions\n");
		printf("---------\n");
		return 1;
	}

	for (int i = 0; i<solcol; ++i)
	{

		for (int j = 0; solutions[i][j] != -1; ++j)
		{
		int x = firstcoord(solutions[i][j]);
		int y = secondcoord(solutions[i][j]);
		int z = inputValues(solutions[i][j]);

		sudokuMatrix[x][y] = z;
		}

		printSudokuMatrix();
		printf("---------\n");
		if(validityrowcolchecker(size) == true && validtyregchecker() == true){
    		printf("valid solution\n");
    		printf("---------\n");
    		return 1;
    	}
   	 	// else{
   	 	// 	printf("invalid solution\n");
   	 	// 	printf("---------\n");
   	 	// 	return false;

   	 	// } 
   	 	

		
	}

	printf("There are no solutions\n");
	printf("---------\n");
	return 1;

	
}

//blank sudoku board for testing

void inputBlankSudoku(){
	int **array = matrixMaker(size,size);
	

	for (int i=0; i<size; i++) {
		for (int j = 0; j < size; ++j)
		{
		
    		(*(*(array + j) + i)) = 0;

    		
    		
		}
    	
  	}

 

  	createSudokuMatrix(array);
  		
}


//input values onto 9x9 sudoku board
void inputSudoku(){
	size = 9;
	int **array = matrixMaker(size,size);

	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < size; ++j)
		{
			(*(*(array + j) + i)) = 0;
		}
	}
	createSudokuMatrix(array);
	

	for (int i=0; i<size; i++) {
		for (int j = 0; j < size; ++j)
		{
			printf("Enter number for row: %d col: %d or 0 for empty",i+1,j+1);
			int temp = 0;
    		scanf("%d", &temp);
    		if ( temp< 0 || temp > 9)
    		{
    			j--;
    			printf("INVALID INPUT\n" );
    			continue;
    		}
    		(*(*(array + j) + i)) = temp;
    		createSudokuMatrix(array);
    		printSudokuMatrix();
    		
    		
		}
    	
  	}

  	createSudokuMatrix(array);
  	basesudokucover();
    printSudokuMatrix();
	start = malloc(sizeof(struct Cell));
    start = createCellMatrix();
    reduceSudokuCover();
    search(0);
    solutionsIntoSudokuMatrix();
   


  	
}


int test4x4Sudoku(){
	size = 4;


	inputBlankSudoku();
		
    randomMatrixFill();

  	basesudokucover();
    printSudokuMatrix();
	start = malloc(sizeof(struct Cell));
    start = createCellMatrix();
    reduceSudokuCover();
    search(0);
    printInputMatrix();
    printf("\n");
    return solutionsIntoSudokuMatrix();

	



}

int test9x9Sudoku(){

	size = 9;


	inputBlankSudoku();
	
	randomMatrixFill();

  	basesudokucover();
    printSudokuMatrix();
	start = malloc(sizeof(struct Cell));
    start = createCellMatrix();
    reduceSudokuCover();
    search(0);
    printInputMatrix();


    return solutionsIntoSudokuMatrix();

	



}



int main(int argc, char const *argv[]) 
{   
	srand(time(NULL));
	printf("\n");
	if (argc > 1)
	{
		if(**(argv + 1) == '1'){
			assert(test4x4Sudoku() == 1);
		}
		
		if(**(argv + 1) == '2'){
			assert(test9x9Sudoku() == 1);
		}
		
	}
	else  inputSudoku();



  
   
   
  


   return 0; 
} 


