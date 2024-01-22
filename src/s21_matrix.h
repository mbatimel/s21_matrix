#ifndef S21_MATRIX_H
#define S21_MATRIX_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define OK 0
#define MATRIX_ER 1
#define CALC_ER 2
#define SUCCESS 1
#define FAILURE 0

#define EPSILON 10e-7

typedef struct matrix_struct {
  double **matrix;
  int rows;
  int columns;
} matrix_t;

/*-------------- MAIN FUNCTIONS --------------------------------*/

int s21_create_matrix(int rows, int columns, matrix_t *result);
void s21_remove_matrix(matrix_t *A);
int s21_eq_matrix(matrix_t *A,
                  matrix_t *B);  // #define SUCCESS 1 #define FAILURE 0
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_mult_number(matrix_t *A, double number, matrix_t *result);
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_transpose(matrix_t *A, matrix_t *result);
int s21_calc_complements(matrix_t *A, matrix_t *result);
int s21_determinant(matrix_t *A, double *result);
int s21_inverse_matrix(matrix_t *A, matrix_t *result);

/*--------------OTHER FUNCTIONS --------------------------------*/

int s21_check_rouwcount_columnscount(matrix_t *A);
void s21_smaller_matrix(int row, int columns, matrix_t *A, matrix_t *minor);
int noughts_handling(matrix_t *copy, double *result, int dimention);
void replacement(matrix_t *copy, int dimention, int v, int row);
int s21_check_MATRIX_ER(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_check_CALC_ER(matrix_t *A, matrix_t *B);
void fill_minor(int dimention, matrix_t *A, int i, int ii, matrix_t *minor);
#endif