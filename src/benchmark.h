#ifndef BENCHMARK_H
#define BENCHMARK_H
#include<time.h>
#include <unistd.h>
#include <sys/time.h>
#include <stdio.h>
#include "genmath.h"
#include "benchmark.h"
double now ();
void benchmark(void (*)(void), const char*, int);
#endif
