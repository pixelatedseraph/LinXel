#include<stdio.h>
#include<stdlib.h>
#include"genmath.h"

int main(){
    double** testmat = genmatrix();
    printm(testmat);
    freematrix(testmat);
}
