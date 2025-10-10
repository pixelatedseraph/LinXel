#ifndef HELPERS_H
#define HELPERS_H
#include "genmath.h"
#include "benchmark.h"
// biops 
Matrix bench_add(Matrix, Matrix);
Matrix bench_sub(Matrix, Matrix);
Matrix bench_product(Matrix, Matrix);
Matrix bench_hadamard(Matrix, Matrix);
Matrix bench_elemwise_div(Matrix, Matrix);
Matrix bench_matrix_equal(Matrix, Matrix);
// uniops
Matrix bench_transpose(Matrix);
Matrix bench_determinant(Matrix);
Matrix bench_invert(Matrix);
Matrix bench_scalarpr(Matrix);
Matrix bench_trace(Matrix);
Matrix bench_norm(Matrix);
Matrix bench_rank(Matrix);
Matrix bench_power(Matrix);
Matrix bench_cond_num(Matrix);
void dotline();
#endif