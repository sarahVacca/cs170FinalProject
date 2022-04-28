#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "lexer.h"
#include "parser.h"
#include "eval.h"

int main(){
    startTokens(20);

    while(1){
        printf("Scheme> ");
        struct SExp *sexp = S_Expression();
        struct SExp *evalauated = eval(sexp);
        printSExp(evalauated->s);
        printf("\n");
    }
}
