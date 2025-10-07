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


 void dotline(){
     printf("---------------------------------------------\n");
 }