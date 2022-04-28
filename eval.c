#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "parser.h"
#include "eval.h"

#ifndef EVAL
#define EVAL

#endif

// Return the car of cell
SExp car(SExp sexp){ 
    sexp->s = sexp->s->car;
    return sexp;
}

// Return the cdr of cell
SExp cdr(SExp sexp){
    sexp->s = sexp->s->cdr;
    return sexp;
}

// Return cell as it is
SExp quote(SExp sexp){
    return sexp;
}

// Symbol? If there is data in cell, it must be a symbol
// return true. If the data is null, return false.
SExp symbol(SExp sexp){
    if(sexp->s->data != NULL){
        sexp->s = makeCell("t");
        return sexp;
    }else{
        sexp->s = makeCell("#f");
        return sexp;
    }
}

// Cons: Take one conscell and make it the car of the second conscell
SExp cons(SExp one, SExp two){
    // Make new cell
    SExp sexp;
    sexp->s = makeCell(NULL);
    SExp temp;
    temp = car(one);
    SExp temptwo;
    temptwo = car(two);
    // If they are both false, return a null cell
    if(temp->s->data != NULL && !strcmp(temp->s->data, "#f")){
        if(temptwo->s->data != NULL && !strcmp(temptwo->s->data, "#f")){
            temp->s = makeCell(NULL);
            return temp;
        }
        // If only the first one is false, return the second one
        return two;
    }
    // If only the second one is false, return the first one
    if(temptwo->s->data != NULL && !strcmp(temptwo->s->data, "#f")){
        return one;
    }
    // If neither are false, set the car of new cell equal to the first cell
    // and the cdr of the new cell equal to the second cell
    sexp->s->car = one->s;
    sexp->s->cdr = two->s;
    // return the new cell
    return sexp;
}

SExp copyCell(SExp sexp){
    SExp copy;
    if(sexp->s == NULL){
        return NULL;
    }
    if(sexp->s->data != NULL){
        copy->s = makeCell(sexp->s->data);
        return copy;
    }
    copy->s = makeCell(NULL);
    if(car(sexp) != NULL){
        copy->s->car = copyCell(car(sexp))->s;
    }
    if(cdr(sexp) != NULL){
        copy->s->cdr = copyCell(cdr(sexp))->s;
    }
    return copy;
}

SExp append(SExp one, SExp two){
    SExp append;
    append->s = copyCell(one)->s;
    if(cdr(append) != NULL){
        SExp temp;
        temp->s = cdr(append)->s;
        while(cdr(temp) != NULL){
            temp->s = cdr(temp)->s;
        }
        temp->s->cdr = copyCell(two)->s;
    }else{
        append->s->cdr = copyCell(two)->s;
    }
    return append;
}

SExp null(SExp sexp){
    SExp temp;
    if(sexp->s->data != NULL){
        if(!strcmp(sexp->s->data, "#f")){
            temp->s = makeCell("#t");
        }
    }
    temp->s = makeCell("#f");
    return temp;
}

/* Eval: takes a conscell and evaluates it based on the special functions that the user may have inputted
such as car, cdr, quote, symbol?, and cons. Returns a conscell. 
*/
SExp eval(SExp sexp){
    SExp rand;
    SExp temp = NULL;
    // First make sure the cell is not null
    if(sexp != NULL){
        // Then, make sure the car of the cell is not null
        if(car(sexp) != NULL){
            // Then, make sure the data of the car of the cell is not null
            rand = car(sexp);
            if((rand->s->data) != NULL){
                char *data = rand->s->data;
                /*Then, to be consistent with scheme, we have to evaluate the code "cdr first"
                So, if the code is (car (cdr (a b c))), we have to find the cdr of (a b c) first,
                and then the car of the cdr of (a b c). */
                temp = eval(car(cdr(sexp))); // This will recurse all the way to the first data that we need to eval
                // Now, we actually run the code for each function (car, cdr, etc)
                if(!strcmp(data, "car")){
                    return car(temp);
                }else if(!strcmp(data, "cdr")){
                    return cdr(temp);
                }else if(!strcmp(data, "quote")){ // Can I have it test for ' as well? Would that make ' = quote?
                    return quote(temp);
                }else if(!strcmp(data, "symbol?")){
                    return symbol(temp);
                }else if(!strcmp(data, "cons")){
                    return cons(temp, eval(car(cdr(cdr(sexp)))));
                }
            }else{
                // Else, if the data of the car of the cell is null...
                printf("%s", sexp->s->data);
                eval(car(sexp));
                // If there's no more concells to recurse into...
                if(sexp->s->cdr == NULL){
                    // Return the cell
                    return sexp;
                }
            }
        }
        // If the cell is not null and we end up here, return the cell
        return sexp; 
    }
}
