#include "s21_matrix.h"

int noughts_handling(matrix_t *copy, double *result, int dimention) {
  int switch_sign = 1;
  for (int v = 0; v < dimention; v++) {
    if (fabs(copy->matrix[v][v]) < EPSILON) {
      int row = 0;
      while (row < dimention) {
        if (fabs(copy->matrix[v][row]) > EPSILON &&
            fabs(copy->matrix[row][v]) > EPSILON) {
          switch_sign *= -1;
          replacement(copy, dimention, v, row);
          break;
        }

        else
          row++;
      }

      if (row == dimention) *result = 0;
    }
  }
  return switch_sign;
}
void replacement(matrix_t *copy, int dimention, int v, int row) {
  double tmp;

  for (int i = 0; i < dimention; i++) {
    tmp = copy->matrix[v][i];
    copy->matrix[v][i] = copy->matrix[row][i];
    copy->matrix[row][i] = tmp;
  }
}
int s21_check_MATRIX_ER(matrix_t *A, matrix_t *B, matrix_t *result) {
  int error = OK;
  if (!A || !B || A->matrix == NULL || B->matrix == NULL || result == NULL ||
      A->rows < 1 || A->columns < 1 || B->rows < 1 || B->columns < 1) {
    error = MATRIX_ER;
  }
  return error;
}
int s21_check_CALC_ER(matrix_t *A, matrix_t *B) {
  int error = OK;
  if (A->rows != B->rows || A->columns != B->columns) {
    error = CALC_ER;
  }
  return error;
}
void fill_minor(int dimention, matrix_t *A, int i, int ii, matrix_t *minor) {
  for (int iii = 0; iii < dimention; iii++) {
    for (int iv = 0; iv < dimention; iv++) {
      if (iii < i && iv < ii) minor->matrix[iii][iv] = A->matrix[iii][iv];
      if (iii < i && iv >= ii) minor->matrix[iii][iv] = A->matrix[iii][iv + 1];
      if (iii >= i && iv < ii) minor->matrix[iii][iv] = A->matrix[iii + 1][iv];
      if (iii >= i && iv >= ii)
        minor->matrix[iii][iv] = A->matrix[iii + 1][iv + 1];
    }
  }
}