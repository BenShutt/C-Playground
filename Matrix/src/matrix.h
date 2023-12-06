#ifndef __matrix_h__
#define __matrix_h__

#include <stdlib.h>

typedef struct Matrix 
{
    double *data;
    size_t n_rows;
    size_t n_columns;
} Matrix;

Matrix* Matrix_init(size_t n_rows, size_t n_columns);
void Matrix_deinit(Matrix *matrix);

double Matrix_get(Matrix *matrix, size_t row, size_t column);
void Matrix_set(Matrix *matrix, size_t row, size_t column, double value);

#endif