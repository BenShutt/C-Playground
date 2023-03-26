#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>

// A (row, column) coordinate
typedef struct Coordinate
{
    // Row number (Y)
    int row;

    // Column number (X)
    int column;
} Coordinate;

// Get the nth triangle number
int triangleNumber(int n)
{
    return 0.5 * n * (n + 1);
}

// Map 1D index to row
int rowForIndex(int index)
{
    double numerator = -1 + sqrt(8 * index + 1);
    return (int)ceil(numerator / 2);
}

// Map 1D index at row to column
int columnForIndexAndRow(int index, int row)
{
    return row + index - triangleNumber(row);
}

// Map 1D index to 2D coordinate
Coordinate mapIndexToCoordinate(int index) 
{
    Coordinate coordinate;
    coordinate.row = rowForIndex(index);
    coordinate.column = columnForIndexAndRow(index, coordinate.row);
    return coordinate;
}

// Test that the 1D index maps correctly to the 2D coordinate
void test(int index, int row, int column) 
{
    Coordinate coordinate = mapIndexToCoordinate(index);
    bool isCorrect = coordinate.row == row && coordinate.column == column;
    if (isCorrect)
    {
        printf("Pass: %d -> (%d, %d).\n", index, row, column);
    }
    else 
    {
        fprintf(stderr, "Fail: %d -> (%d, %d). Expected (%d, %d).\n", 
            index, coordinate.row, coordinate.column, row, column);
    }
}

// ============================== Main ==============================

int main()
{
    test(1, 1, 1);
    
    test(2, 2, 1);
    test(3, 2, 2);
    
    test(4, 3, 1);
    test(5, 3, 2);
    test(6, 3, 3);

    test(7, 4, 1);
    test(8, 4, 2);
    test(9, 4, 3);
    test(10, 4, 4);

    test(11, 5, 1);
    test(12, 5, 2);
    test(13, 5, 3);
    test(14, 5, 4);
    test(15, 5, 5);

    test(16, 6, 1);
    test(17, 6, 2);
    test(18, 6, 3);
    test(19, 6, 4);
    test(20, 6, 5);
    test(21, 6, 6);

    test(22, 7, 1);
    test(23, 7, 2);
    test(24, 7, 3);
    test(25, 7, 4);
    test(26, 7, 5);
    test(27, 7, 6);
    test(28, 7, 7);

    test(29, 8, 1);
    test(30, 8, 2);
    test(31, 8, 3);
    test(32, 8, 4);
    test(33, 8, 5);
    test(34, 8, 6);
    test(35, 8, 7);
    test(36, 8, 8);

    return EXIT_SUCCESS;
}
