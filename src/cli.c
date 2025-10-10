#include<stdio.h>
#include "cli.h"
#include"benchmark.h"
#include"helpers.h"
#include"genmath.h"
#include<argtable2.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include "globals.h"
int repeat; int repc;
int main(int argc , char** argv){
    // Seed the random number generator for matrix generation
    srand(time(NULL));
    
    struct arg_str *gen = arg_strn(
        "g",
        "generate",
        "<m * n>",
        0 ,5 ,
        "generate upto 5 matrices of any size by comma-separated list (eg 2x2,3x3,4x4) ");

    struct arg_str *select =  arg_strn(
        "s",
        "select",
        "<idx>",
        0, 5 ,
        "select from the list of matrices by comma-separated indicies (eg 1,2,3) "); 

    struct arg_str *ops = arg_strn(
        "o",
        "operate",
        "<op>",
        0, 1 , 
        "choose operation: biops(add,sub,product,hadamard,elemwise_div,matrix_equal) uniops(trans,det,inv,spr,trace,norm,rank,power,cond) " );

    struct arg_lit *help = arg_lit0(
        "h",
        "help",
        "Lists out all flags available ");

    struct arg_int *rep = arg_int0(
        "r",
        "repeat",
        "<rep>",
        "repeats the operation (1-100000) ");

    struct arg_lit *print = arg_lit0(
        "p",
        "print",
        "prints all the generated matrices");
    
    struct arg_lit *hwid = arg_lit0(
        "i",
        "hwid",
        "provides the info about cpu and gpu ");
    
    struct arg_lit *parllel = arg_lit0(
        "pa",
        "parallel",
        "enable parallelism computation "); 

    struct arg_end *end = arg_end(20);
    void *argtable[] = {gen,select,ops,help,print,rep,end,NULL};
    int nerrors = arg_parse(argc, argv, argtable);
    /* if parsing fails */
    if (nerrors > 0){
        arg_print_errors(stdout,end,argv[0]);
        printf("Try --help for more info \n");
        arg_freetable(argtable,sizeof(argtable)/sizeof(argtable[0]));
        return 1;
    }
    /* if help flag is invoked */
    if (help->count > 0){
        printf("Uses :\n");
        arg_print_syntax(stdout,argtable , "\n");
        printf("\nOptions:\n");
        arg_print_glossary(stdout,argtable,"  %-25s %s\n");
        arg_freetable(argtable,sizeof(argtable)/sizeof(argtable[0]));
    }
    /* if repeat flag is 0*/
     repc = rep->count;
   
    /* handle rest of flags */

    Matrix matrices[20];
    Matrix selected[20]; 
    int total_matrices = 0;
    int total_selected = 0;
    
    /* generate matrices */
    if (gen->count > 0){
       for (int g = 0 ; g < gen->count ; ++g){
           char** matrix_specs;
           int spec_count;
           
           if (parse_matrix_list(gen->sval[g], &matrix_specs, &spec_count)) {
               for (int i = 0; i < spec_count && total_matrices < 20; i++) {
                   int rows, cols;
                   if(parse_matrix(matrix_specs[i], &rows, &cols)) {
                       matrices[total_matrices] = genmatrix(rows, cols);
                       total_matrices++;
                   } else { 
                       printf("invalid format in '%s' use any of the specified formats \n r*c\n rxc \n rXc", matrix_specs[i]);
                       // cleanup
                       for (int j = 0; j < spec_count; j++) free(matrix_specs[j]);
                       free(matrix_specs);
                       return 1;
                   }
               }
               for (int i = 0; i < spec_count; i++) free(matrix_specs[i]);
               free(matrix_specs);
           } else {
               // Handle single matrix specification
               int rows, cols;
               if(parse_matrix(gen->sval[g], &rows, &cols)) {
                   matrices[total_matrices] = genmatrix(rows, cols);
                   total_matrices++;
               } else { 
                   printf("invalid format use any of the specified formats \n r*c\n rxc \n rXc");
                   return 1;
               }
           }
       }
    }
    
    /* impl select flag */
    if (select->count > 0){
        if(total_matrices == 0){
        printf("You must generate matrices first!\n");
        return 1;
       }
       
       for (int s = 0; s < select->count; s++) {
           int* indices;
           int index_count;
           
           if (parse_index_list(select->sval[s], &indices, &index_count)) {
               for (int i = 0; i < index_count && total_selected < 20; i++) {
                   int idx = indices[i] - 1; // make indices 0 based 
                   if (idx >= 0 && idx < total_matrices){
                       selected[total_selected] = matrices[idx];
                       total_selected++;
                   } else {
                       printf("invalid index: %d\n", indices[i]);
                       free(indices);
                       return 1;
                   }
               }
               free(indices);
           } else {
               int idx = atoi(select->sval[s]) - 1;
               if (idx >= 0 && idx < total_matrices){
                   selected[total_selected] = matrices[idx];
                   total_selected++;
               } else {
                   printf("invalid index\n");
                   return 1;
               }
           }
       }
    }

    /* handle repeat flag BEFORE operations */
    if (rep->count > 0){
        repeat = rep->ival[0];
    }

    /* handle operations now*/
    /* parse bi ops */
    if (ops->count > 0 && total_selected == 2){
        if (strcmp("add",ops->sval[0])==0 || strcmp("sub",ops->sval[0])==0 || strcmp("product",ops->sval[0])==0 ||
            strcmp("hadamard",ops->sval[0])==0 || strcmp("elemwise_div",ops->sval[0])==0 || strcmp("matrix_equal",ops->sval[0])==0){
            Matrix res = parse_biops(selected[0],selected[1],str_to_biop(ops->sval[0]));
            printf("First Matrix  \n");
            printm(selected[0]);
            dotline();
            printf("Second Matrix \n");
            printm(selected[1]);
            dotline();
            printf("The resultant matrix by %s: \n",ops->sval[0]);
            printm(res);
        }
    else {
        printf("invalid operation for two matrices \n");
        return 1;
    }
    }
    /* parse uni ops*/
    if (ops->count > 0 && total_selected == 1 ){
        if (strcmp("trans",ops->sval[0])==0 || strcmp("inv",ops->sval[0])==0 || strcmp("det",ops->sval[0])==0 || 
            strcmp("spr",ops->sval[0])==0 || strcmp("trace",ops->sval[0])==0 || strcmp("norm",ops->sval[0])==0 ||
            strcmp("rank",ops->sval[0])==0 || strcmp("power",ops->sval[0])==0 || strcmp("cond",ops->sval[0])==0){
            Matrix res = parse_uniops(selected[0],str_to_uniop(ops->sval[0]));
            printf("The Matrix \n");
            printm(selected[0]);
            dotline();
            printf("The Matrix after %s operation \n",ops->sval[0]);
            printm(res);

        }
        else {
            printf("Undefined operation \n");
            return 1;
        }
    }

    /* print matrices if invoked -p */
    if (print->count > 0){
        printf("Generated Matrices (%d total):\n", total_matrices);
        for (int i = 0; i < total_matrices; i++){
            printf("Matrix %d:\n", i+1);
            printm(matrices[i]);
            dotline();
        }
    }
    /* handle hwid flag */
    if(hwid-> count > 0){
        
    }
    return 0;
}