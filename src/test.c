#include<stdio.h>
#include<stdlib.h>
#include"genmath.h"
#include"benchmark.h"
#include "helpers.h"
int main(int argc , char **argv){
    srand(time(NULL));
    benchmark(test_product,"test for product of 3 * 3 matrix ",10000000);
    return 0;
}
