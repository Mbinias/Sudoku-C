#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define max_size 16

int N;
int box_size;
int grid[max_size][max_size];

// Checks if the number is in the 3 by 3 box (by default)
int unused_in_box(int row_start, int col_start, int num) {
    for (int i = 0; i < box_size; i++)
        for (int j = 0; j < box_size; j++)
            if (grid[row_start + i][col_start + j] == num)
                return 0;
    return 1;
}

// Fills 3 by 3 box with random, unique numbers (1-9)
void fill_box(int row, int col) {
    int num;
    for (int i = 0; i < box_size; i++) {
        for (int j = 0; j < box_size; j++) {
            do {
                num = rand() % N +1;
            } while (!unused_in_box(row, col, num));
            grid[row + i ][col + j] = num;
        }
    }
}

// Checks if the number is in the row
int unused_in_row(int row, int num) {
    for (int j = 0; j < N; j++) {
        if (grid[row][j] == num)
            return 0;
    }
    return 1;
}

// Checks if the number is in the column
int unused_in_col(int col, int num) {
    for (int i = 0; i < N; i++) {
        if (grid[i][col] == num)
            return 0;
    }
    return 1;
}

// Checks if the number is safe to place in (i, j)
int check_if_safe(int row, int col, int num) {
    return unused_in_row(row, num) &&
        unused_in_col(col, num) &&
            unused_in_box(row - row % box_size, col - col % box_size, num);
}

// Fills diagonal 3 by 3 boxes
void fill_diagonal() {
    for (int i = 0; i < N; i += box_size) {
        fill_box(i, i);
    }
}

// Recursively fills the grid with correct numbers
int fill_remaining(int i, int j) {
    if (i == N)
        return 1;
    if (j == N)
        return fill_remaining(i + 1, 0);
    if (grid[i][j] != 0)
        return fill_remaining(i, j + 1);

    for (int num = 1; num <= N; num++) {
        if (check_if_safe(i, j, num)) {
            grid[i][j] = num;
            if (fill_remaining(i, j + 1))
                return 1;
            grid[i][j] = 0;
        }
    }
    return 0;
}

// removes given number of digits from a completed sudoku
void remove_k_digits(int k) {
    while (k > 0) {
        int cell_id = rand() % (N*N);
        int i = cell_id / N;
        int j = cell_id % N;
        if (grid[i][j] != 0) {
            grid[i][j] = 0;
            k--;
        }
    }
}

void generate_sudoku(int difficulty) {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            grid[i][j] = 0;

    fill_diagonal();
    fill_remaining(0, 0);
    remove_k_digits(difficulty);
}

void print_sudoku() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            printf("%2d ", grid[i][j]);
        printf("\n");
    }

}

void play_game() {
    int row, col, val;
    int mistakes = 0;
    int scanf_result;
    int number_of_zeros = 1;

    while (number_of_zeros > 0) {
        print_sudoku();
        printf("\n mistakes: %d \n", mistakes);

        printf("Enter row (0-%d), column (0-%d) and a value (1-%d): (0 0 0 to exit): ", N-1, N-1, N);
        scanf_result = scanf("%d %d %d", &row, &col, &val);

        if (scanf_result != 3) {
            printf("Invalid input. Try again.\n");
            while (getchar() != '\n');
            continue;
        }

        if (val == 0) {
            grid[row][col] = 0;
        }
        else if (grid[row][col] != 0) {
            printf("This space is already taken\n");
        }

        if (row == 0 && col == 0 && val == 0 || mistakes >= 3) {
            printf("Game ended\n");
            break;
        }

        if (row < 0 || row >= N || col < 0 || col >= N || val < 0 || val > N) {
            printf("Invalid input\n");
            continue;
        }

        if (check_if_safe(row, col, val)) {
            grid[row][col] = val;
        } else {
            printf("Wrong number\n");
            mistakes += 1;
        }

        number_of_zeros = 0;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (grid[i][j] == 0) {
                    number_of_zeros += 1;
                    break; // there is still something to fill, so no need to check further
                }
            }
            if (number_of_zeros > 0) {
                break;
            }
        }
        if (number_of_zeros == 0 && mistakes < 3) {
            printf("You succesfully completed this Sudoku! \n");
        }

    }

}

//
void menu() {
    int option;
    int difficulty;

    do {
        printf("\n MENU \n");
        printf("1. New game \n");
        printf("2. Choose Sudoku size \n");
        printf("3. Exit \n");
        printf(" Choose an option: \n");
        scanf("%d", &option);

        switch (option) {
            case 1:
                printf("\n Choose difficulty level (number of removed digits) \n");
                if (scanf("%d", &difficulty) != 1) {
                    printf("Invalid input. Enter a number\n");
                    while (getchar() != '\n');
                    continue;
                }
                generate_sudoku(difficulty);
                play_game();
                break;

            case 2:
                printf("\n Choose the board size (4, 9 or 16): ");
                if (scanf("%d", &N) != 1) {
                    printf("Invalid input. Enter a number\n");
                    while (getchar() != '\n');
                    continue;
                }
                if (N == 4 || N == 9 || N == 16) {
                    box_size = sqrt(N);
                } else {
                    printf("Invalid board size. Please choose 4, 9 or 16\n");
                    // setting a default size just in case
                    N =9;
                    box_size = sqrt(N);
                }
                break;

            case 3:
                printf("Exit \n");
                break;

            default:
                printf("\n Invalid Choice\n");
        }
    } while (option != 3);
}

int main() {
    srand(time(NULL));

    N = 9;
    box_size = sqrt(N);

    menu();

    return 0;
}

