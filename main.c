#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "lexer.h"
#include "parser.h"
#include "eval.h"

// Runs the parser
int main(){
    char token[20];
    startTokens(20);
    globalEnviornment = malloc(sizeof(struct SExp));
    globalEnviornment->s = makeCell(NULL); 

    while(1){
        printf("Scheme> ");
        struct SExp *sexp = malloc(sizeof(struct SExp));
        sexp = S_Expression();
        struct SExp *evaluated = malloc(sizeof(struct SExp));
        evaluated = eval(sexp);
        printSExp(evaluated->s);
        printf("\n");
    }
}
