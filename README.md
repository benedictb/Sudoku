# Sudoku

Sudoku is a sudoku puzzle solver written in C++ that allows the user to solve plaintext sudoku files or solves them automatically. This program was written for an assignment in CSE20212 (Fundamentals of Computing II) at the University of Notre Dame.

#### Input
Valid input files come in the following form: 9 lines of 9 numbers separated by a space, an example below.
```txt
4 0 8 7 0 0 1 0 2
0 0 0 3 4 0 0 5 0
0 1 0 0 5 0 0 0 0
0 0 0 8 0 0 6 0 0
0 8 4 0 0 0 2 7 0
0 0 2 0 0 5 0 0 0
0 0 0 0 8 0 0 4 0
0 9 0 0 2 4 0 0 0
3 0 6 0 0 7 8 0 1
```

This repository comes with 3 sample puzzles of various difficulties, conveniently named "easy", "medium" and "hard" in the `puzzles` directory.

#### Startup
To build, enter `make` in the repository root. This will result in a binary file named `main`.

After running `main`, the user will be prompted to input a filename. For convenience, the contents of the `puzzles` directory is displayed. After selecting a puzzle file, you will be prompted to either play (manually solve the puzzle) or solve (have the program solve it automatically).

#### Playing
When play is selected, the program enters a turn-like state. Each turn, the user selects a (valid) row and column, and if the coordinates do not represent a part of the original puzzle, you may enter a number to put into that cell. The program will not let you change the origianl puzzle or enter a non-valid number (for example, a 3 in a row that already had a 3).

You may re-enter numbers in cells if they do not belong to the original puzzle.

If you fill the entire board with numbers, by definition you have solved the puzzle, but there is an additional congratulatory message.

When in play mode, enter "-1" as the desired number to exit the program, or simply press CTRL + C.


#### Solving
Sudoku uses a singleton algorithm to try all possible ways to deduce a correct number placement, and places the definite numbers it finds in a board. Sudoku can solve any puzzle that doesn't have any ambiguous moves, that is, it must have a deterministic solution.

When solve is selected, the board will be solved and updated in "runs" through the board. The display will refresh after each run to give the user an idea of how the program is solving the puzzle. After the puzzle has been solver, the number of runs will be displayed alongside the solved puzzle.

