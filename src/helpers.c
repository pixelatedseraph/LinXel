#include "genmath.h"
#include "benchmark.h"
#include "helpers.h"
#include <argtable2.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include"cli.h"
void bench_add(){
    Matrix matA = genmatrix(*hrow,*hcol);
    Matrix matB = genmatrix(*hrow,*hcol);
    Matrix res = matrixadd(matA,matB);
    matrixadd(matA,matB);
    freematrix(matA);
    freematrix(matB);
    freematrix(res);
    free(hrow);
    free(hcol);
}
void bench_sub(){
    Matrix matA = genmatrix(*hrow,*hcol);
    Matrix matB = genmatrix(*hrow,*hcol);
    Matrix res = matrixadd(matA,matB);
    matrixsub(matA,matB);
    freematrix(matA);
    freematrix(matB);
    freematrix(res);
    free(hrow);
    free(hcol);
}
void bench_product(){
    Matrix matA = genmatrix(*hrow,*hcol);
    Matrix matB = genmatrix(*hrow,*hcol);
    Matrix res = matrixproduct(matA,matB);
    matrixproduct(matA,matB);
    freematrix(matA);
    freematrix(matB);
    freematrix(res);
    free(hrow);
    free(hcol);
}
void bench_transpose(){
    Matrix matA = genmatrix(*hrow,*hcol);  
    Matrix T = transpose(matA);
    freematrix(matA);
    freematrix(T);
    free(hrow);
    free(hcol);
}
void bench_determinant(){
    Matrix matA = genmatrix(*hrow,*hcol);
    double det = determinant(matA);
    freematrix(matA);
    free(hrow);
    free(hcol);
}
void bench_invert(){
    Matrix matA = genmatrix(*hrow,*hcol);
    Matrix I = invert(matA);
    freematrix(matA);
    freematrix(I);
    free(hrow);
    free(hcol);
}
void bench_scalarpr(){
    Matrix matA = genmatrix(*hrow,*hcol);
    scalarmultiply(5,matA);
    freematrix(matA);
    free(hrow);
    free(hcol);
}

void dotline(){
    printf("---------------------------------------------\n");
}