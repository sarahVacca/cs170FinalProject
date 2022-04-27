#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "lexer.h"
#include "parser.h"
#include "eval.h"

int main(){
    char token[20];
    startTokens(20);

    while(1){
        printf("Scheme> ");
        printSExp(eval(parse));
        printf("\n\n");
    }
}