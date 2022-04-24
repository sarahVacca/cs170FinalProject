#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "lexer.h"
#ifndef PARSER
#define PARSER

#endif

void sexpression(int depth);
void S_Expression();
char token[20];
int main(){
// call sexpression
    startTokens(20);
    while (1){
        printf("Scheme> ");
        strcpy(token, getToken());
        sexpression(0);
    }
}
void sexpression(int depth){
    for (int i = 0; i < depth; i++){
        printf(" ");
    }
    // can all be dealt with a for loop
    // have this call itself

    if (!strcmp(token, "(")) { // if token = (
        printf("S_Expression\n");
        for (int i = 0; i < depth; i++){
            printf(" ");
        }
        printf("(\n");
        strcpy(token, getToken());
        while (strcmp(token, ")")){ // if token does not equal )
            sexpression(depth + 1);
        }
        for (int i = 0; i < depth; i++){
            printf(" ");
        }
        printf(")\n");
        if(depth != 0){
            strcpy(token, getToken());
        }
    }
    else if (!strcmp(token, "()")) { // if token = ()
        printf("S_Expression\n");
        for (int i = 0; i < depth; i++){
            printf(" ");
        }
        printf("%s\n", token);
        if(depth != 0){
            strcpy(token, getToken());
        }
    }
    else if (!strcmp(token, "#t")) { // if token = #t
        printf("S_Expression\n");
        for (int i = 0; i < depth; i++){
            printf(" ");
        }
        printf("%s\n", token);
        if(depth != 0){
            strcpy(token, getToken());
        }
    }
    else if (!strcmp(token, "#f")) { // if token = #f
        printf("S_Expression\n");
        for (int i = 0; i < depth; i++){
            printf(" ");
        }
        printf("%s\n", token);
        if(depth != 0){
            strcpy(token, getToken());
        }
    }
    else{
        printf("S_Expression\n");
        for (int i = 0; i < depth; i++){
            printf(" ");
        }
        printf("%s\n", token);
        if(depth != 0){
            strcpy(token, getToken());
        }
    }
}




