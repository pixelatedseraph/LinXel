#include<stdio.h>
#include<stdlib.h>
#include"genmath.h"

int main(int argc , char **argv){
  srand(time(NULL));
    // Matrix testmat1 = genmatrix(3,2);
    // Matrix testmat2 = genmatrix(2,3);
    // //Matrix testmat1 = genmatrix(atoi(argv[1]),atoi(argv[2]));
    // //Matrix testmat2 = genmatrix(atoi(argv[3]),atoi(argv[4]));
    // printm(testmat1);
    // printf("--------------------------------------\n");
    // printm(testmat2);
    // printf("--------------------------------------\n");
    // Matrix prod = matrixproduct(testmat1,testmat2);
    // printm(prod);
    // freematrix(testmat1);
    // freematrix(testmat2);  
    // freematrix(prod); 
    // return 0;
    // Matrix m1 = voidmatrix(2,2);
    // printm(m1);
    // freematrix(m1);
    Matrix m1  = genmatrix(2,3);
    printm(m1);
    printf("-------------------------------------\n");
    //Matrix m2 = generaltranspose(m1);
    //printm(m2);
    Matrix m2 =  transpose(m1);
    printm(m2);
    freematrix(m1);
    //freematrix(m2);
    return 0;
}
