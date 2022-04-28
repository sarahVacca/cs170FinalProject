#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "lexer.h"
#include "parser.h"
#include "eval.h"

int main(){
    char token[20];
    startTokens(20);

// This does not run :( 
    // Causes a segmentation fault
    while(1){
        printf("Scheme> ");
        printSExp(eval(parse)); // The result of parse and the parameter of eval cause incompatible type error
        printf("\n\n");
    }
}
