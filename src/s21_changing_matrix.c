#include "s21_matrix.h"

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int error = OK;
  if (rows <= 0 || columns <= 0 || result == NULL) {
    error = MATRIX_ER;
    ;
  } else {
    result->rows = rows;
    result->columns = columns;
    result->matrix = calloc(rows, sizeof(double *));
    if (!result->matrix) {
      error = MATRIX_ER;
    } else {
      for (int i = 0; i < rows; i++) {
        result->matrix[i] = calloc(columns, sizeof(double));
      }
    }
  }
  return error;
}
void s21_remove_matrix(matrix_t *A) {
  if (A != NULL) {
    for (int i = 0; i < A->rows; i++) {
      free(A->matrix[i]);
    }
    free(A->matrix);

    A->matrix = NULL;
    A->rows = 0;
    A->columns = 0;
  }
}
int s21_transpose(matrix_t *A, matrix_t *result) {
  int error = CALC_ER;
  if (!A || A->rows < 1 || A->columns < 1 || !A || !A->matrix) {
    error = MATRIX_ER;
  }

  else if (s21_create_matrix(A->columns, A->rows, result) == OK) {
    error = OK;
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[j][i] = A->matrix[i][j];
      }
    }
  }

  return error;
}
int s21_determinant(matrix_t *A, double *result) {
  if (!A || A->rows < 1 || A->columns < 1 || !A->matrix) return MATRIX_ER;
  if (A->rows != A->columns) return CALC_ER;

  matrix_t copy;
  *result = 1;
  s21_create_matrix(A->rows, A->columns, &copy);

  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) copy.matrix[i][j] = A->matrix[i][j];
  }
  int switch_sign = noughts_handling(&copy, result, A->columns);

  if (*result) {
    for (int k = 0; k < A->rows - 1; k++) {
      for (int i = k + 1; i < A->rows; i++) {
        double mult = copy.matrix[i][k] / copy.matrix[k][k];
        for (int j = k; j < A->columns; j++)
          copy.matrix[i][j] -= copy.matrix[k][j] * mult;
      }
    }
    for (int i = 0; i < A->rows; i++) {
      *result *= copy.matrix[i][i];
    }
    *result *= switch_sign;
  }

  s21_remove_matrix(&copy);
  return OK;
}
int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  int status = OK;
  if (!A || (A->rows < 1) || (A->columns < 1) || !result)
    status = MATRIX_ER;
  else if (A->rows != A->columns)
    status = CALC_ER;
  else {
    double det = 0.0;
    s21_determinant(A, &det);
    if (fabs(det) < 1e-6)
      status = CALC_ER;
    else if (A->rows == 1) {
      s21_create_matrix(1, 1, result);
      result->matrix[0][0] = (1 / det);
    } else {
      matrix_t B;
      s21_calc_complements(A, result);
      s21_transpose(result, &B);
      s21_remove_matrix(result);
      s21_mult_number(&B, (1.0 / det), result);
      s21_remove_matrix(&B);
    }
  }
  return status;
}
