#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "check.h"
#include "matrix.h"

static void test_get(Matrix *matrix, size_t row, size_t column, double value)
{
    bool is_correct = Matrix_get(matrix, row, column) == value;
    const char *message = is_correct ? "Correct" : "Incorrect";
    printf("(row=%ld, col=%ld) %s.\n", row, column, message);
}

int main()
{
    Matrix *matrix = Matrix_init(2, 3);
    check_memory(matrix);

    Matrix_set(matrix, 0, 0, 1);
    Matrix_set(matrix, 0, 1, 2);
    Matrix_set(matrix, 0, 2, 3);
    Matrix_set(matrix, 1, 0, 4);
    Matrix_set(matrix, 1, 1, 5);
    Matrix_set(matrix, 1, 2, 6);

    test_get(matrix, 0, 0, 1);
    test_get(matrix, 0, 1, 2);
    test_get(matrix, 0, 2, 3);
    test_get(matrix, 1, 0, 4);
    test_get(matrix, 1, 1, 5);
    test_get(matrix, 1, 2, 6);

    Matrix_deinit(matrix);
    return EXIT_SUCCESS;

error:
    return EXIT_FAILURE;
}