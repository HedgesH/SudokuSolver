My project this week was creating a sudoku solver using the dancing links implementation
of Algorithm X, created by Donald Knuth
https://en.wikipedia.org/wiki/Knuth%27s_Algorithm_X
https://en.wikipedia.org/wiki/Dancing_Links

I have two .c files, exactcover.c and SudokuSolver.c

The first one implements the dancing links algorithm

The second one creates an exact cover from a given sudoku puzzle
then feeds this into the exactcover.c algorithm

If you type ./SudokuSolver 1 
-this starts and generates a random board for a 4x4 sudoku puzzle and prints the exactcover on the screen
If you type ./SudokuSolver 2
-this starts and generates a random boar for a 9x9 sudoku puzzle, with no exactcover printed as its way too big

If you type ./SudokuSolver
-you can input your own sudoku problem, 0's are the empty value.

The biggest problem with this currently is being able to feed in sudoku matrixes, as they take a long time to type up.



--I was introduced to this topic by https://medium.com/optima-blog/solving-sudoku-fast-702912c13307