#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "lexer.h"
#include "parser.h"
#ifndef PARSER
#define PARSER

#endif

Cell S_Expression(int depth);
char token[20];

// printSExp takes a conscell "cell" and prints it in parenthesized form
void printSExp(Cell cell){
    int depth = 1;
    if(cell != NULL){
        if(cell->data != NULL){
            printf("%s", cell->data);
        }else{
            if(depth != 0){
                printf("(");
            }
            depth = 1;
            printCell(cell->car);
            if(cell->cdr == NULL){
                printf(")");
            }else{
                printf(" ");
                depth = 0;
                printCell(cell->cdr);
            }
        }
    }
}

// makeCell takes a char* named data and creates a new conscell structure and puts
// data into the conscells char* also named data
Cell makeCell(char *data){
    // Initialize a new conscell with the char data given from user as the data of the cell
    Cell cell = (Cell) malloc(sizeof(struct conscell));
    // If data is empty, make the cells data null
    if(data == NULL){
        cell->data = NULL;
    }else{ // else, put data into cell->data
        cell->data = malloc(sizeof(char)*strlen(data) + 1);
        strcpy(cell->data, data);
    }
    // Initialize the car and the cdr of this conscell as null
    cell->car = NULL;
    cell->cdr = NULL;
    // return the conscell structure
    return cell;
}

/* S_Expression takes an integer that represents the "depth" or how many S_Expressions deep we are
We start of at 0 and each time the depth increases, that means have recursed into a new
S_Expression. For the conscell representation, we want to initialize a new conscell with each 
new S_Expression created */
Cell S_Expression(int depth){
    Cell cell, temp;
    /* Main part of function, handles what to do if the token is an open parenthesis
    Also handles recursive calls as an open parenthesis means the start of a new
    S_Expression as defined by the grammar in part one */
    if (!strcmp(token, "(")) { // if token = (
        // make a new conscell (make it null because we don't know what is in it yet, all we know is we have a new conscell)
        cell = makeCell(NULL);
        // get the token
        strcpy(token, getToken());
        // The car of the cons cell will be the next token
        cell->car = S_Expression(depth + 1);
        // Set a temporary conscell "temp" equal to our current conscell "cell"
        temp = cell;
        // While we are in a new S_Expression...
        while (strcmp(token, ")")){ // if token does not equal )
            // Set our current conscell "temp" cdr equal to a new empty conscell
            temp->cdr = makeCell(NULL);
            // Then, set temp equal to its own cdr
            temp = temp->cdr;
            // Then make the car of temp (temp is the cdr of temp which is also cell) equal to the next token
            temp->car = S_Expression(depth + 1); // Recursion
        }
        temp->cdr = NULL;
        if(depth != 0){
            strcpy(token, getToken());
        }
    }
    // If token is ()
    else if (!strcmp(token, "()")) { 
        cell = makeCell("()");
        if(depth != 0){
            strcpy(token, getToken());
        }
    }
    // If token is #t
    else if (!strcmp(token, "#t")) { 
        cell = makeCell("#t");
        if(depth != 0){
            strcpy(token, getToken());
        }
    }
    // If token is #f
    else if (!strcmp(token, "#f")) { 
        cell = makeCell("#f");
        if(depth != 0){
            strcpy(token, getToken());
        }
    }
    // Else, meaning that token is any other character not defined above
    else{
        cell = makeCell(token);
        if(depth != 0){
            strcpy(token, getToken());
        }
    }
    return cell;
}

int main(){
// call S_Expression
    startTokens(20);
    while (1){
        printf("Scheme> ");
        strcpy(token, getToken());
        S_Expression(0);
    }
}




