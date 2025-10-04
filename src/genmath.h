#ifndef GENMATH_H
#define GENMATH_H

#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<time.h>
#include<math.h>

typedef struct Matrix
{
    double** mat;
    int rows;
    int cols;
}Matrix;

Matrix voidmatrix(int ,int);
Matrix genmatrix(int ,int);
void printm(Matrix);
Matrix matrixproduct(Matrix ,Matrix);
Matrix matrixadd(Matrix, Matrix);
Matrix matrixsub(Matrix, Matrix);
void freematrix(Matrix);
void scalarmultiply(int ,Matrix);
void inplacetranspose(Matrix);
Matrix transpose(Matrix);
Matrix identitymatrix(int);
double determinant(Matrix);
Matrix invert(Matrix);
#endif
