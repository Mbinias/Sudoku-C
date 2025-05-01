# Sudoku Project in C

A simple Sudoku game program with the ability to select the board size (4x4, 9x9, 16x16) and difficulty level (number of digits removed).

## Description

When launched, the program displays a menu with options:

1. New game: Starts a new game with the selected difficulty level.

2. Select Sudoku size: Allows you to change the board size to 4x4, 9x9 or 16x16.

3. Exit: Closes the program.

During the game, the current Sudoku board and the number of mistakes made are displayed on the screen. 
The user can enter numbers by providing a row, column and value (separated by spaces).Entering "0 0 0" ends the game. 
The game also ends after making 3 mistakes or after correctly solving Sudoku.

## Known Problems and Limitations

* No possibility to save and load the game yet.
* The generation algorithm does not guarantee that each generated board has a unique solution.
* After changing the board size in the menu, a new game (option 1) is not generated automatically. You have to select "New game" again.
* No advanced mechanisms for checking the correctness of entered numbers during the game (apart from the basic `check_if_safe`).
