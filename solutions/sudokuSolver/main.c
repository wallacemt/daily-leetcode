#include <stdio.h>
#include <stdbool.h>

bool isValid(char** board, int row, int col, char num) {
    // Check row
    for (int i = 0; i < 9; i++) {
        if (board[row][i] == num) {
            return false;
        }
    }
    
    // Check column
    for (int i = 0; i < 9; i++) {
        if (board[i][col] == num) {
            return false;
        }
    }
    
    // Check 3x3 box
    int boxRow = (row / 3) * 3;
    int boxCol = (col / 3) * 3;
    for (int i = boxRow; i < boxRow + 3; i++) {
        for (int j = boxCol; j < boxCol + 3; j++) {
            if (board[i][j] == num) {
                return false;
            }
        }
    }
    
    return true;
}

bool backtrack(char** board) {
    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++) {
            if (board[row][col] == '.') {
                for (char num = '1'; num <= '9'; num++) {
                    if (isValid(board, row, col, num)) {
                        board[row][col] = num;
                        
                        if (backtrack(board)) {
                            return true;
                        }
                        
                        // Backtrack
                        board[row][col] = '.';
                    }
                }
                return false;
            }
        }
    }
    return true; // All cells filled
}

void solveSudoku(char** board, int boardSize, int* boardColSize) {
    backtrack(board);
}
