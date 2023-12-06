#include <stdbool.h>

#include "matrix.h"
#include "check.h"

Matrix* Matrix_init(size_t n_rows, size_t n_columns)
{
    assert(n_rows > 0, "Invalid n_rows argument");
    assert(n_columns > 0, "Invalid n_columns argument");

    Matrix *matrix = (Matrix *)malloc(sizeof(Matrix));
    check_memory(matrix);

    matrix->data = (double *)calloc(n_rows * n_columns, sizeof(double));
    check_memory(matrix->data);

    return matrix;

error:
    Matrix_deinit(matrix);
    return NULL;
}

void Matrix_deinit(Matrix *matrix)
{
    if(matrix)
    {
        if(matrix->data)
        {
            free(matrix->data);
        }

        free(matrix);
    }
}

static size_t Matrix_index(Matrix *matrix, size_t row, size_t column)
{
    assert(matrix != NULL, "Invalid matrix argument");
    assert(row >= 0 && row < matrix->n_rows, "Invalid row argument");
    assert(column >= 0 && column < matrix->n_columns, "Invalid column argument");
    return row * matrix->n_columns + column;
}

double Matrix_get(Matrix *matrix, size_t row, size_t column)
{
    size_t index = Matrix_index(matrix, row, column);
    return matrix->data[index];
}

void Matrix_set(Matrix *matrix, size_t row, size_t column, double value)
{
    size_t index = Matrix_index(matrix, row, column);
    matrix->data[index] = value;
}