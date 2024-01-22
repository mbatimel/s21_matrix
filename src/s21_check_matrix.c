#include "s21_matrix.h"

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int result = SUCCESS;
  if (!A || !B || (A->rows != B->rows) || (A->columns != B->columns)) {
    result = FAILURE;
  } else {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        if (fabs(A->matrix[i][j] - B->matrix[i][j]) > 1e-07) {
          result = FAILURE;
          break;
        }
      }
    }
  }
  return result;
}

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int error = OK;

  if (!A || A->rows < 1 || A->columns < 1 || !result) {
    error = MATRIX_ER;
  } else if (A->rows != A->columns) {
    error = CALC_ER;
  } else {
    s21_create_matrix(A->rows, A->columns, result);
    if (A->rows == 1) {
      result->matrix[0][0] = A->matrix[0][0];

    } else {
      matrix_t minor;
      s21_create_matrix(A->rows - 1, A->columns - 1, &minor);
      for (int i = 0; i < A->rows; i++) {
        for (int ii = 0; ii < A->columns; ii++) {
          fill_minor(A->rows - 1, A, i, ii, &minor);

          double det;
          int mult = ((i + ii) % 2) ? -1 : 1;
          s21_determinant(&minor, &det);

          result->matrix[i][ii] = det * mult;
        }
      }
      s21_remove_matrix(&minor);
    }
  }
  return error;
}
