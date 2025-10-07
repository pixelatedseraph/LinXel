#ifndef HELPERS_H
#define HELPERS_H
#include "genmath.h"
#include "benchmark.h"
// biops 
Matrix bench_add(Matrix, Matrix);
Matrix bench_sub(Matrix, Matrix);
Matrix bench_product(Matrix, Matrix);
// uniops
void bench_transpose();
void bench_determinant();
void bench_invert();
void bench_scalarpr();
void dotline();
#endif