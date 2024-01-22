#include "s21_matrix.h"
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int error = OK;
  if (s21_check_MATRIX_ER(A, B, result) == MATRIX_ER) {
    error = MATRIX_ER;
  } else if (s21_check_CALC_ER(A, B) == CALC_ER) {
    error = CALC_ER;
  } else {
    s21_create_matrix(A->rows, A->columns, result);
    for (int m = 0; m < A->rows; m++) {
      for (int n = 0; n < A->columns; n++) {
        result->matrix[m][n] = A->matrix[m][n] + B->matrix[m][n];
      }
    }
  }
  return error;
}
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int error = OK;
  if (s21_check_MATRIX_ER(A, B, result) == MATRIX_ER) {
    error = MATRIX_ER;
  } else if (s21_check_CALC_ER(A, B) == CALC_ER) {
    error = CALC_ER;
  } else {
    int create_matrix = s21_create_matrix(A->rows, A->columns, result);
    if (create_matrix == OK) {
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
        }
      }
    }
  }

  return error;
}
int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  if (!A || A->rows < 1 || A->columns < 1 || !A || !A->matrix) return MATRIX_ER;

  int ret_code = CALC_ER;
  if (s21_create_matrix(A->rows, A->columns, result) == OK) {
    ret_code = OK;
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[i][j] = A->matrix[i][j] * number;
      }
    }
  }
  return ret_code;
}

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  if (!A || !B || A->rows < 1 || A->columns < 1 || B->rows < 1 ||
      B->columns < 1 || !A->matrix || !B->matrix)
    return MATRIX_ER;

  if (A->columns != B->rows) return CALC_ER;

  int ret_code = CALC_ER;
  result->rows = A->rows;
  result->columns = B->columns;
  if (s21_create_matrix(result->rows, result->columns, result) == OK) {
    ret_code = OK;

    for (int i = 0; i < result->rows; i++) {
      for (int j = 0; j < result->columns; j++) {
        result->matrix[i][j] = 0;
        for (int k = 0; k < A->columns; k++)
          result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
      }
    }
  }
  return ret_code;
}
