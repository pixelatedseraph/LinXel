#ifndef HELPERS_H
#define HELPERS_H
#include "genmath.h"
#include "benchmark.h"
// biops 
Matrix bench_add(Matrix, Matrix);
Matrix bench_sub(Matrix, Matrix);
Matrix bench_product(Matrix, Matrix);
// uniops
Matrix bench_transpose(Matrix);
Matrix bench_determinant(Matrix);
Matrix bench_invert(Matrix);
Matrix bench_scalarpr(Matrix);
void dotline();
#endif