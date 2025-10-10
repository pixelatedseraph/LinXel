#ifndef GENMATH_H
#define GENMATH_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <math.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct Matrix {
    double** mat;
    int rows;
    int cols;
} Matrix;

Matrix voidmatrix(int, int);
Matrix genmatrix(int, int);
void printm(Matrix);
Matrix matrixproduct(Matrix, Matrix);
Matrix matrixadd(Matrix, Matrix);
Matrix matrixsub(Matrix, Matrix);
void freematrix(Matrix);
Matrix scalarmultiply(int, Matrix);
void inplacescalarmultiply(int, Matrix);
Matrix inplacetranspose(Matrix);
Matrix transpose(Matrix);
Matrix identitymatrix(int);
double determinant(Matrix);
Matrix invert(Matrix);
double trace(Matrix);
double frobeniusnorm(Matrix);
int rank(Matrix);
Matrix matrixpower(Matrix, int);
double conditionnumber(Matrix);
Matrix zerosmatrix(int, int);
Matrix onesmatrix(int, int);
Matrix hadamardproduct(Matrix, Matrix);
Matrix elementwisedivision(Matrix, Matrix);
int matrixequal(Matrix, Matrix, double);

#ifdef __cplusplus
}
#endif

#endif // GENMATH_H
