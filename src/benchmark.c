#define _POSIX_C_SOURCE 199309L
#include <unistd.h>
#include <sys/time.h>
#include <stdio.h>
#include "genmath.h"
#include "benchmark.h"
#include <time.h>
/* returns current time , call twice and diff them to get benchmark */
double now (){
    struct timespec t;
    clock_gettime(CLOCK_MONOTONIC, &t);
    return t.tv_sec + t.tv_nsec  * 1e-9;
}
void benchmark(void (*fptr) (void) , const char* info , int runs){
    double total = 0.0 , avg = 0.0;
    for (int i = 0; i < runs ; ++i ){
        double st = now();
        fptr();
        double en = now();
        total += en - st;
    }
    avg = total / runs;
    printf("%s ran for : %d times & the average time taken : %.10f \n the total time taken is : %.3f\n",info,runs,avg,total);
}
int parse_matrix(const char* s, int* rows ,int* cols ){
    int res = sscanf(s,"%dx%d",rows,cols);
    if (res != 2)
        res = sscanf(s,"%dX%d",rows,cols);
    if (res !=2)
        res = sscanf(s,"%d*%d",rows,cols);
    if (res !=2 || *rows < 0 || *cols < 0)  
        return 0;
    return 1;
}
Matrix parse_biops(Matrix matA, Matrix matB, biop op){
    switch (op)
    {
    case add:
        return matrixadd(matA,matB);
    case sub:
        return matrixsub(matA,matB);
    case product:
        return matrixproduct(matA,matB);
    default:
        return (Matrix){NULL,0,0};
    }
}
Matrix parse_uniops(Matrix matA ,uniop op){
    switch (op)
    {
    case trans:
        return transpose(matA);
    case inv:
        return invert(matA);
    case det:
        double detm = determinant(matA);
        Matrix res = voidmatrix(1,1);
        if (res.mat != NULL){
        res.mat[0][0] = detm;
        return res;
        }
        else {return (Matrix) {NULL,0,0};}
    case spr:
        return scalarmultiply(5,matA);
    default:
        return (Matrix) {NULL,0,0};
    }
}
biop str_to_biop(const char* s){
    if (strcmp(s,"add")==0) return add;
    if (strcmp(s,"sub")==0) return sub;
    if (strcmp(s,"product")==0) return product;
    fprintf(stderr, "Unknown operation: %s\n", s);
    exit(1);
}
uniop str_to_uniop(const char *s){
    if (strcmp(s,"trans")==0) return trans;
    if (strcmp(s,"inv")==0) return inv;
    if (strcmp(s,"det")==0) return det;
    if (strcmp(s,"spr")==0) return spr;
    fprintf(stderr, "undefined operation: %s\n", s);
    exit(1);
}