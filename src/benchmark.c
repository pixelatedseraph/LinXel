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

