#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<time.h>
#include "genmath.h"
double** genmatrix(){
    srand(time(0));
    double **matrix = malloc (sizeof(double *) * 1000);
    if (matrix==NULL){printf("no matrix allocated! \n"); return 0;}
    for (int i = 0 ; i < 1000 ; ++i){
        matrix[i] = malloc(sizeof(double) * 1000);
        if(matrix[i]==NULL){printf("no matrix allocated! \n"); return 0;}
    }
    for (int i = 0 ;  i < 3; ++i){
        for (int j = 0 ; j < 3 ; ++j){
            *(*(matrix + i)+j) = rand();
            }
        }
        return matrix;
    }
void printm(double** mat){
    for (int i = 0 ; i < 3 ; ++i){
        for (int j = 0 ; j < 3 ;++j){
            printf("%.2f ",mat[i][j]);
        }
        printf("\n");
    }
}

void freematrix(double** mat){
    for (int i = 0 ; i < 3 ; ++i ){
      free(mat[i]);
    }
    free(mat);
}