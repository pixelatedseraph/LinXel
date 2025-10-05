#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<time.h>
#include<math.h>
#include "genmath.h"
Matrix voidmatrix(int rows , int cols){
    Matrix mtes;
    mtes.rows = rows;
    mtes.cols = cols;
    mtes.mat = malloc(sizeof(double*) * mtes.rows);
    if(mtes.mat == NULL) {printf("no Matrix allocated! \n"); return (Matrix){NULL,0,0};}
    for(int i = 0 ; i < mtes.rows ; ++i ){
        mtes.mat[i] = malloc(sizeof(double) * mtes.cols);
        if (mtes.mat[i] == NULL) {
            printf("no Matrix allocated! \n"); 
            for(int k = 0 ; k < i ; ++k){
                free(mtes.mat[k]);
            }
            free(mtes.mat);
            return (Matrix){NULL,0,0};

        }
    }
    for (int i = 0 ; i <  mtes.rows ; ++i){
        for (int j = 0 ; j < mtes.cols ; ++j){
            mtes.mat[i][j] = 0.0;
        }
    }
    return mtes;
}
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
            *(*(m.mat + i)+j) = rand() % 11;
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
Matrix matrixadd(Matrix matA , Matrix matB){
    if ((matA.rows != matB.rows) || (matA.cols != matB.cols) ) {printf("Matrix Addition isnt Possible!\n"); return (Matrix){NULL,0,0} ;}
    Matrix res = voidmatrix(matA.rows,matB.cols);
    for (int i = 0 ; i < matA.rows  ;++i ){
        for (int j = 0 ; j < matB.cols  ;++j ){
            res.mat[i][j] = matA.mat[i][j] + matB.mat[i][j];
        }   
    }
    return res;
}
Matrix matrixsub(Matrix matA , Matrix matB){
    if ((matA.rows != matB.rows) || (matA.cols != matB.cols) ) {printf("Matrix Addition isnt Possible!\n"); return (Matrix){NULL,0,0} ;}
    Matrix res = voidmatrix(matA.rows,matB.cols);
    for (int i = 0 ; i < matA.rows  ;++i ){
        for (int j = 0 ; j < matB.cols  ;++j ){
            res.mat[i][j] = matA.mat[i][j] - matB.mat[i][j];
        }   
    }
    return res;
}

Matrix scalarmultiply(int k,Matrix matA){
    Matrix res = voidmatrix(matA.rows , matA.cols);
    for (int i = 0 ; i < matA.rows ; ++i){
        for (int j = 0 ; j < matA.cols ; ++j){
            res.mat[i][j] = k * matA.mat[i][j]; 
        }
    }
    return res;
}
void inplacescalarmultiply(int k, Matrix matA){
    for (int i = 0; i < matA.rows; ++i) {
        for (int j = 0; j < matA.cols; ++j) {
            matA.mat[i][j] *= k;
        }
    }
}
void inplacetranspose(Matrix matA){
    int n = matA.rows ;
    for (int i = 0 ; i < n ; ++i){
        for (int j = i+1 ; j < n ; ++j ){
            double temp = matA.mat[i][j];
            matA.mat[i][j] =  matA.mat[j][i];
            matA.mat[j][i] = temp;
        }
    }
}
Matrix generaltranspose(Matrix matA){
    int rows = matA.cols;
    int cols = matA.rows;
    Matrix T = voidmatrix(rows, cols);
    for (int i = 0 ; i < T.rows ; ++i){
        for (int j = 0 ; j < T.cols ; ++j){
            T.mat[i][j] = matA.mat[j][i]; 
        }
    }
    return T;
} 
Matrix transpose(Matrix matA){
    if (matA.rows == matA.cols){
        inplacetranspose(matA);
        return matA;
    }
    else {
        return generaltranspose(matA);
    }
}
Matrix identitymatrix(int size){
    Matrix res = voidmatrix(size,size);
    for(int i = 0 ; i < size ; ++i ){
        for (int j = 0 ; j < size ; ++j ){
                res.mat[i][j] = (i == j) ? 1 : 0;
        }
    }
    return res;
}
double determinant(Matrix matA) {
    if (matA.rows != matA.cols) {
        printf("Not a square matrix\n");
        return 0.0;
    }
    int n = matA.rows;
    Matrix temp = voidmatrix(n, n);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            temp.mat[i][j] = matA.mat[i][j];

    double det = 1.0;
    for (int i = 0; i < n; ++i) {
        int pivot = i;
        for (int j = i + 1; j < n; ++j) {
            if (fabs(temp.mat[j][i]) > fabs(temp.mat[pivot][i]))
                pivot = j;
        }
        if (fabs(temp.mat[pivot][i]) < 1e-9) {
            freematrix(temp);
            return 0.0;
        }
        if (pivot != i) {
            double* tmp = temp.mat[i];
            temp.mat[i] = temp.mat[pivot];
            temp.mat[pivot] = tmp;
            det *= -1;
        }
        det *= temp.mat[i][i];
        for (int j = i + 1; j < n; ++j) {
            double factor = temp.mat[j][i] / temp.mat[i][i];
            for (int k = i; k < n; ++k)
                temp.mat[j][k] -= factor * temp.mat[i][k];
        }
    }
    freematrix(temp);
    return det;
}
Matrix invert(Matrix matA){
    if (matA.rows != matA.cols) {
        printf("Not a square matrix\n");
        return (Matrix){NULL,0,0};
    }
    int n = matA.rows;
    Matrix aug = voidmatrix(n, 2 * n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            aug.mat[i][j] = matA.mat[i][j];
        }
        for (int j = n; j < 2 * n; ++j) {
            aug.mat[i][j] = (i == (j - n)) ? 1.0 : 0.0;
        }
    }
    for (int i = 0; i < n; ++i) {
        int pivot = i;
        for (int j = i + 1; j < n; ++j) {
            if (fabs(aug.mat[j][i]) > fabs(aug.mat[pivot][i]))
                pivot = j;
        }
        if (fabs(aug.mat[pivot][i]) < 1e-9) {
            freematrix(aug);
            printf("Matrix is singular and cannot be inverted.\n");
            return (Matrix){NULL,0,0};
        }
        if (pivot != i) {
            double* tmp = aug.mat[i];
            aug.mat[i] = aug.mat[pivot];
            aug.mat[pivot] = tmp;
        }
        double pivotVal = aug.mat[i][i];
        for (int j = 0; j < 2 * n; ++j)
            aug.mat[i][j] /= pivotVal;
        for (int j = 0; j < n; ++j) {
            if (j != i) {
                double factor = aug.mat[j][i];
                for (int k = 0; k < 2 * n; ++k)
                    aug.mat[j][k] -= factor * aug.mat[i][k];
            }
        }
    }
    Matrix inv = voidmatrix(n, n);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            inv.mat[i][j] = aug.mat[i][j + n];
    freematrix(aug);
    return inv;
}