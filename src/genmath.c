#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<time.h>
#include "genmath.h"
Matrix genmatrix(int rows , int cols){
    Matrix m;
    m.rows = rows;
    m.cols = cols;
    m.mat = malloc (sizeof(double*) * m.rows);
    if (m.mat==NULL){printf("no Matrix allocated! \n"); return (Matrix){NULL,0,0};}
    for (int i = 0 ; i < m.rows ; ++i){
        m.mat[i] = malloc(sizeof(double) * m.cols);
        if(m.mat[i]==NULL){printf("no Matrix allocated! \n"); return (Matrix){NULL,0,0};}
    }
    for (int i = 0 ;  i < m.rows; ++i){
        for (int j = 0 ; j < m.cols ; ++j){
            *(*(m.mat + i)+j) = rand();
            }
        }
        return m;
    }
void printm(Matrix m1){
    for (int i = 0 ; i < m1.rows ; ++i){
        for (int j = 0 ; j < m1.cols ;++j){
            printf("%.2f ",m1.mat[i][j]);
        }
        printf("\n");
    }
}

void freematrix(Matrix m1){
    for (int i = 0 ; i < m1.rows ; ++i ){
      free(m1.mat[i]);
    }
    free(m1.mat);
}
Matrix matrixproduct(Matrix matA, Matrix matB){
    if (matA.cols != matB.rows){printf("This Operation is invalid!\n"); return (Matrix){NULL,0,0}; }
    Matrix res;
    res.rows = matA.rows;
    res.cols = matB.cols; 
    res.mat = malloc(sizeof(double*) * res.rows); 
    if (res.mat == NULL) {printf("no Matrix allocated! \n"); return (Matrix){NULL,0,0};}
    for (int p = 0 ; p < res.rows ; ++p ){
        res.mat[p] = malloc(sizeof(double) * res.cols );
    }
    for(int i = 0 ; i < res.rows ; ++i){
        for(int j = 0 ; j < res.cols ; ++j){
            res.mat[i][j] = 0.0;
            for (int k = 0 ; k < matA.cols ; ++k){
                res.mat[i][j] += matA.mat[i][k] * matB.mat[k][j];
            }
        }
    }
    return res;
}
