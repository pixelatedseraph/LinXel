#ifndef BENCHMARK_H
#define BENCHMARK_H
#include<time.h>
#include <unistd.h>
#include <sys/time.h>
#include <stdio.h>
#include "genmath.h"
#include "benchmark.h"
/* ops that require two matrices*/
typedef enum biop{
    add,
    sub,
    product
}biop;
/* ops that require a singular matrix */
typedef enum uniop{
    trans,
    inv,
    det,
    spr
}uniop;
double now ();
void benchmark(void (*)(void), const char*, int);
int parse_matrix(const char*, int* ,int *);
Matrix parse_biops(Matrix, Matrix, biop);
Matrix parse_uniops(Matrix,uniop);
#endif
