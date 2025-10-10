#include "genmath.h"
#include "benchmark.h"
#include "helpers.h"
#include <argtable2.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include"cli.h"
#include "globals.h"
/* biops benchmarks */

Matrix bench_add(Matrix matA , Matrix matB){
    return benchmark(matrixadd,matA,matB,"matrix add",repc == 0 ? 1 : repeat);
}
Matrix bench_sub(Matrix matA , Matrix matB){
    return benchmark(matrixsub,matA,matB,"matrix sub",repc == 0 ? 1 : repeat);
}
Matrix bench_product(Matrix matA , Matrix matB){
    return benchmark(matrixproduct,matA,matB,"matrix product",repc == 0 ? 1 : repeat);
}

Matrix bench_hadamard(Matrix matA, Matrix matB) {
    return benchmark(hadamardproduct, matA, matB, "hadamard product", repc == 0 ? 1 : repeat);
}

Matrix bench_elemwise_div(Matrix matA, Matrix matB) {
    return benchmark(elementwisedivision, matA, matB, "element-wise division", repc == 0 ? 1 : repeat);
}

Matrix bench_matrix_equal(Matrix matA, Matrix matB) {
    return special2benchmark(matrixequal, matA, matB, "matrix equality", repc == 0 ? 1 : repeat);
}

/* uniops benchmarking */

Matrix bench_transpose(Matrix matA){
    return singlebenchmark(transpose,matA, "matrix transpose",repc == 0 ? 1 : repeat);
}
Matrix bench_invert(Matrix matA){
    return singlebenchmark(invert, matA , "matrix invert", repc == 0 ? 1 : repeat);
}
Matrix bench_determinant(Matrix matA){
  double det =  special1singlebenchmark(determinant,matA , "determinant of matrix",repc == 0 ? 1 : repeat);
        Matrix res = voidmatrix(1,1);
        if (res.mat != NULL){
        res.mat[0][0] = det;
        return res;
        }
        else {return (Matrix) {NULL,0,0};}
}
Matrix bench_scalarpr(Matrix matA){
    Matrix result = scalarmultiply(5, matA);
    printf("scalar multiplication by 5 operation completed\n");
    dotline();
    return result;
}

Matrix bench_trace(Matrix matA) {
    double tr = special1singlebenchmark(trace, matA, "matrix trace", repc == 0 ? 1 : repeat);
    Matrix res = voidmatrix(1, 1);
    if (res.mat != NULL) {
        res.mat[0][0] = tr;
    }
    return res;
}

Matrix bench_norm(Matrix matA) {
    double norm_val = special1singlebenchmark(frobeniusnorm, matA, "frobenius norm", repc == 0 ? 1 : repeat);
    Matrix res = voidmatrix(1, 1);
    if (res.mat != NULL) {
        res.mat[0][0] = norm_val;
    }
    return res;
}

Matrix bench_rank(Matrix matA) {
    // Create a special function that returns double for rank
    double rank_val = (double)rank(matA);
    Matrix res = voidmatrix(1, 1);
    if (res.mat != NULL) {
        res.mat[0][0] = rank_val;
    }
    printf("matrix rank ran for : 1 times & the rank is : %.0f\n", rank_val);
    dotline();
    return res;
}

Matrix bench_power(Matrix matA) {
    // Default power of 2 for demonstration
    Matrix result = matrixpower(matA, 2);
    printf("matrix power (^2) operation completed\n");
    dotline();
    return result;
}

Matrix bench_cond_num(Matrix matA) {
    double cond = special1singlebenchmark(conditionnumber, matA, "condition number", repc == 0 ? 1 : repeat);
    Matrix res = voidmatrix(1, 1);
    if (res.mat != NULL) {
        res.mat[0][0] = cond;
    }
    return res;
}
 void dotline(){
     printf("---------------------------------------------\n");
 }