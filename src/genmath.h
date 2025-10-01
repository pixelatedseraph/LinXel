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

Matrix genmatrix(int ,int);
void printm(Matrix);
Matrix matrixproduct(Matrix ,Matrix);
void freematrix(Matrix);

#endif