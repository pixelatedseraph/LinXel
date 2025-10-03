#ifndef GENMATH_H
#define GENMATH_H

#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<time.h>

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
Matrix matrixadd(Matrix, Matrix);
void freematrix(Matrix);
void scalarmultiply(int ,Matrix);
void inplacetranspose(Matrix);
Matrix generaltranspose(Matrix);
Matrix transpose(Matrix);
#endif
