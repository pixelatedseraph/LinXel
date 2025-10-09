#ifndef BENCHMARK_H
#define BENCHMARK_H
#include<time.h>
#include <unistd.h>
#include <sys/time.h>
#include <stdio.h>
#include "genmath.h"
#include<string.h>
/* ops that require two matrices*/
typedef enum biop{
    add,
    sub,
    product
}biop;
/* user provides str , convert it to enum*/
    biop str_to_biop(const char*);

/* ops that require a singular matrix */
typedef enum uniop{
    trans,
    inv,
    det,
    spr
}uniop;
/* user provides string as input ,handle the conversion (convert string to enum) */
uniop str_to_uniop(const char *s);
/* struct for uniops which require additional argument */

double now ();
Matrix benchmark(Matrix(*)(Matrix,Matrix),Matrix ,Matrix ,const char*, int);
Matrix singlebenchmark(Matrix(*)(Matrix),Matrix ,const char*, int);
double special1singlebenchmark(double(*)(Matrix) ,Matrix ,const char* ,int);
int parse_matrix(const char*, int* ,int *);
int parse_matrix_list(const char*, char***, int*);
int parse_index_list(const char*, int**, int*);
Matrix parse_biops(Matrix, Matrix, biop);
Matrix parse_uniops(Matrix,uniop);
#endif
