#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

// An (x, y) coordinate
typedef struct Coordinate
{
    // X coordinate
    int x;

    // Y coordinate
    int y;
} Coordinate;

// Map a 1D index to a 2D coordinate
Coordinate mapIndexToCoordinate(int index) 
{
    Coordinate coordinate;
    coordinate.x = 0;
    coordinate.y = 0;
    return coordinate;
}

// Test that the 1D index maps correctly to the 2D coordinate
void test(int index, int x, int y) 
{
    Coordinate coordinate = mapIndexToCoordinate(index);
    int isCorrect = coordinate.x == x && coordinate.y == y;
    char* result = isCorrect ? "Pass" : "Fail";
    printf("%s: %d -> (%d, %d)\n", result, index, x, y);
}

int main()
{
    test(1, 1, 1);
    return EXIT_SUCCESS;
}
