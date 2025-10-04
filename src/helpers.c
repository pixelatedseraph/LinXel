#include "genmath.h"
#include "benchmark.h"
#include "helpers.h"

void test_add(){
    Matrix matA = voidmatrix(3,3);
    Matrix matB = voidmatrix(3,3);
    matrixadd(matA,matB);
    freematrix(matA);
    freematrix(matB);
}
void test_sub(){
    Matrix matA = voidmatrix(3,3);
    Matrix matB = voidmatrix(3,3);
    matrixsub(matA,matB);
    freematrix(matA);
    freematrix(matB);
}
void test_product(){
    Matrix matA = voidmatrix(3,3);
    Matrix matB = voidmatrix(3,3);
    matrixproduct(matA,matB);
    freematrix(matA);
    freematrix(matB);
}
void test_transpose(){
    Matrix matA = voidmatrix(3,3);  
    Matrix T = transpose(matA);
    freematrix(matA);
    freematrix(T);
}
void test_determinant(){
    Matrix matA = voidmatrix(3,3);
    double det = determinant(matA);
    freematrix(matA);
}
void test_invert(){
    Matrix matA = voidmatrix(3,3);
    Matrix I = invert(matA);
    freematrix(matA);
    freematrix(I);
}
void test_scalarpr(){
    Matrix matA = voidmatrix(3,3);
    scalarmultiply(5,matA);
    freematrix(matA);
}

