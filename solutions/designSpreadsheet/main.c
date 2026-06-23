#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    int** grid;
    int rows;
} Spreadsheet;

Spreadsheet* spreadsheetCreate(int rows) {
    Spreadsheet* obj = (Spreadsheet*)malloc(sizeof(Spreadsheet));
    obj->rows = rows;
    obj->grid = (int**)malloc(26 * sizeof(int*));
    
    for (int i = 0; i < 26; i++) {
        obj->grid[i] = (int*)calloc(rows, sizeof(int));
    }
    
    return obj;
}

void parseCellReference(char* cell, int* col, int* row) {
    *col = cell[0] - 'A';
    *row = atoi(cell + 1) - 1;
}

void spreadsheetSetCell(Spreadsheet* obj, char* cell, int value) {
    int col, row;
    parseCellReference(cell, &col, &row);
    obj->grid[col][row] = value;
}

void spreadsheetResetCell(Spreadsheet* obj, char* cell) {
    int col, row;
    parseCellReference(cell, &col, &row);
    obj->grid[col][row] = 0;
}

int isNumber(char* str) {
    for (int i = 0; str[i]; i++) {
        if (!isdigit(str[i])) return 0;
    }
    return 1;
}

int getValue(Spreadsheet* obj, char* token) {
    if (isNumber(token)) {
        return atoi(token);
    } else {
        int col, row;
        parseCellReference(token, &col, &row);
        return obj->grid[col][row];
    }
}

int spreadsheetGetValue(Spreadsheet* obj, char* formula) {
 
    char* expr = formula + 1;
    
    char* plus_pos = strchr(expr, '+');
    
    int len1 = plus_pos - expr;
    char operand1[20], operand2[20];
    
    strncpy(operand1, expr, len1);
    operand1[len1] = '\0';
    strcpy(operand2, plus_pos + 1);
    
    return getValue(obj, operand1) + getValue(obj, operand2);
}

void spreadsheetFree(Spreadsheet* obj) {
    for (int i = 0; i < 26; i++) {
        free(obj->grid[i]);
    }
    free(obj->grid);
    free(obj);
}