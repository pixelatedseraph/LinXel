#include<stdio.h>
#include "cli.h"
#include"benchmark.h"
#include"helpers.h"
#include"genmath.h"
#include<argtable2.h>
#include<string.h>
int main(int argc , char** argv){
    struct arg_str *gen = arg_strn(
        "g",
        "generate",
        "<m * n>",
        1 ,5 ,
        "generate upto 5 matrices of any size (eg 2x2 , 5x3 ..etc) ");

    struct arg_int *select =  arg_intn(
        "s",
        "select",
        "<idx>",
        1, 5 ,
        "select from the list of matrices by index (1-5) "); 

    struct arg_str *ops = arg_str1(
        "o",
        "operate",
        "<op>",
        "choose the operation ( mul , transpose , invert , det etc) " );

    struct arg_lit *help = arg_lit0(
        "h",
        "help",
        "Lists out all flags available ");

    struct arg_int *rep = arg_intn(
        "r",
        "repeat",
        "<rep>",
        0, 10000 ,
        "repeats the operation (0-10000) ");

    struct arg_lit *print = arg_lit0(
        "p",
        "print",
        "prints all the generated matrices");

    struct arg_end *end = arg_end(20);
    void *argtable[] = {gen,select,ops,help,rep,end,NULL};
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
    /* handle rest of flags */

    /* generate matrices */
    Matrix matrices [gen->count];
    if (gen->count > 0){
        Matrix matrices [gen->count]; 
       for (int i = 0 ; i < gen->count ; ++i){
        int rows,cols;
            if(parse_matrix(gen->sval[i],&rows,&cols))
                matrices[i] = voidmatrix(rows,cols);
            else printf("invalid format use any of the specified formats \n r*c\n rxc \n rXc");
       }
    }
    Matrix selected [select-> count];
    /* impl select flag */
    if (select->count > 0){
        if(gen->count == 0){
        printf("You must generate matrices first!\n");
        return 1;
       }
       for (int i = 0 ; i < select->count ; ++i){
        int idx = select->ival[i]-1 ; //make indices 0 based 
        if (idx >= 0 & idx < gen->count){
            selected [i] = matrices[idx];
        }
        else{
            printf("invalid index\n");
            }
       }
    }

    /* handle operations now*/
    /* parse bi ops */
    if (ops->count > 0 && select->count ==2){
        if (strcmp("add",ops->sval[0])==0 || strcmp("sub",ops->sval[0])==0 || strcmp("mul",ops->sval[0])==0){
            Matrix res = parse_biops(selected[0],selected[1],ops->sval);
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
    if (ops->count > 0 && select->count ==1 ){
        if (strcmp("trans",ops->sval[0])==0 || strcmp("inv",ops->sval[0])==0 || strcmp("det",ops->sval[0])==0 || strcmp("spr",ops->sval[0])==0){
            Matrix res = parse_uniops(selected[0],ops->sval[0]);
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
}