#define _POSIX_C_SOURCE 199309L
#define _GNU_SOURCE
#include <unistd.h>
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
int parse_matrix(const char* s, int* rows ,int* cols ){
    int res = sscanf(s,"%dx%d",rows,cols);
    if (res != 2)
        res = sscanf(s,"%dX%d",rows,cols);
    if (res !=2)
        res = sscanf(s,"%d*%d",rows,cols);
    if (res !=2 || *rows < 0 || *cols < 0)  
        return 0;
    return 1;
}

/* Parse comma-separated matrix specifications */
int parse_matrix_list(const char* s, char*** matrix_specs, int* count){
    if (!s || !matrix_specs || !count) return 0;
    
    char* input = strdup(s);
    if (!input) return 0;
    
    *count = 1;
    for (char* p = input; *p; p++) {
        if (*p == ',') (*count)++;
    }
    
    *matrix_specs = malloc(*count * sizeof(char*));
    if (!*matrix_specs) {
        free(input);
        return 0;
    }
    
    char* token = strtok(input, ",");
    int i = 0;
    while (token && i < *count) {
        // Trim whitespace
        while (*token == ' ' || *token == '\t') token++;
        char* end = token + strlen(token) - 1;
        while (end > token && (*end == ' ' || *end == '\t')) end--;
        *(end + 1) = '\0';
        
        (*matrix_specs)[i] = strdup(token);
        if (!(*matrix_specs)[i]) {
            // Cleanup on failure
            for (int j = 0; j < i; j++) free((*matrix_specs)[j]);
            free(*matrix_specs);
            free(input);
            return 0;
        }
        token = strtok(NULL, ",");
        i++;
    }
    
    free(input);
    return 1;
}

/* Parse comma-separated indices for selection */
int parse_index_list(const char* s, int** indices, int* count){
    if (!s || !indices || !count) return 0;
    
    char* input = strdup(s);
    if (!input) return 0;
    
    *count = 1;
    for (char* p = input; *p; p++) {
        if (*p == ',') (*count)++;
    }
    
    *indices = malloc(*count * sizeof(int));
    if (!*indices) {
        free(input);
        return 0;
    }
    
    char* token = strtok(input, ",");
    int i = 0;
    while (token && i < *count) {
        // Trim whitespace
        while (*token == ' ' || *token == '\t') token++;
        
        int idx = atoi(token);
        if (idx <= 0) {
            free(*indices);
            free(input);
            return 0;
        }
        (*indices)[i] = idx;
        token = strtok(NULL, ",");
        i++;
    }
    
    free(input);
    return 1;
}
Matrix parse_biops(Matrix matA, Matrix matB, biop op){
    switch (op)
    {
    case add:
        return matrixadd(matA,matB);
    case sub:
        return matrixsub(matA,matB);
    case product:
        return matrixproduct(matA,matB);
    default:
        return (Matrix){NULL,0,0};
    }
}

Matrix parse_uniops(Matrix matA ,uniop op){
    switch (op)
    {
    case trans:
        return transpose(matA);
    case inv:
        return invert(matA);
    case det:
        double detm = determinant(matA);
        Matrix res = voidmatrix(1,1);
        if (res.mat != NULL){
        res.mat[0][0] = detm;
        return res;
        }
        else {return (Matrix) {NULL,0,0};}
    case spr:
        return scalarmultiply(5,matA);
    default:
        return (Matrix) {NULL,0,0};
    }
}
biop str_to_biop(const char* s){
    if (strcmp(s,"add")==0) return add;
    if (strcmp(s,"sub")==0) return sub;
    if (strcmp(s,"product")==0) return product;
    fprintf(stderr, "Unknown operation: %s\n", s);
    exit(1);
}
uniop str_to_uniop(const char *s){
    if (strcmp(s,"trans")==0) return trans;
    if (strcmp(s,"inv")==0) return inv;
    if (strcmp(s,"det")==0) return det;
    if (strcmp(s,"spr")==0) return spr;
    fprintf(stderr, "undefined operation: %s\n", s);
    exit(1);
}