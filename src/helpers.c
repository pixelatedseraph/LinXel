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
    return singlebenchmark(scalarmultiply, matA ,"multiplcation by scalar" ,repc == 0 ? 1 : repeat);
}
 void dotline(){
     printf("---------------------------------------------\n");
 }