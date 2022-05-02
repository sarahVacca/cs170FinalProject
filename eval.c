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
    SExp sexp = malloc(sizeof(struct SExp)); 
    sexp->s = makeCell(NULL);
    SExp temp = malloc(sizeof(struct SExp));
    temp = car(one);
    SExp temptwo = malloc(sizeof(struct SExp));
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

// Copies one sexp into another
SExp copyCell(SExp sexp){
    SExp copy = malloc(sizeof(struct SExp));
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

// Scheme "append" functionality
SExp append(SExp one, SExp two){
    SExp append = malloc(sizeof(struct SExp));
    append->s = copyCell(one)->s;
    if(cdr(append) != NULL){
        SExp temp = malloc(sizeof(struct SExp));
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

// Checks if an sexp is null
SExp null(SExp sexp){
    SExp temp = malloc(sizeof(struct SExp));
    if(sexp->s->data != NULL){
        if(!strcmp(sexp->s->data, "#f")){
            temp->s = makeCell("#t");
        }
    }
    temp->s = makeCell("#f");
    return temp;
}

// Checks to see if the data, car, and cdr of two sexps are
// structurally equal
SExp equalsHelper(SExp one, SExp two){
    SExp sexp = malloc(sizeof(struct SExp));
    if((one->s->car == NULL && two->s->car != NULL) ||
        (one->s->car != NULL && two->s->car == NULL) ||
        (one->s->cdr == NULL && two->s->cdr != NULL) ||
        (one->s->cdr != NULL && two->s->cdr == NULL) ||
        (one->s->data == NULL && two->s->data != NULL) ||
        (one->s->data != NULL && two->s->data == NULL)){
            sexp->s = makeCell("f");
    }else{
        sexp->s = makeCell("t");
    }
    return sexp;
}

// Checks if two SExps are equal in every way
SExp equals(SExp one, SExp two){
    SExp temp = malloc(sizeof(struct SExp));
    SExp helper = equalsHelper(one, two);
    // If helper returns false, automatically false
    if(!strcmp(helper->s->data, "#f")){
        temp->s = makeCell("f");
        return temp;
    }
    // Then make sure the data of one and two is equal
    if(one->s->data != NULL && two->s->data != NULL){
        if(strcmp(one->s->data, two->s->data)){
            temp->s = makeCell("#f");
            return temp;
        }
    }
    // Then, make sure the cars of one and two are equal
    if(one->s->car != NULL && two->s->car != NULL){
        helper = equalsHelper(car(one), car(two));
        if(!strcmp(helper->s->data, "#f")){
            temp->s = makeCell("f");
            return temp;
        }
    }
    // Then check if the cdrs of one and two are equal
    if(one->s->cdr != NULL && two->s->cdr != NULL){
        helper = equalsHelper(cdr(one), cdr(two));
        if(!strcmp(helper->s->data, "#f")){
            temp->s = makeCell("f");
            return temp;
        }
    }
    // If we get here, the two SExps are equal
    temp->s = makeCell("#t");
    return temp;
}

/* Scheme assoc functionality: 
returns the pair that the symbol is a part of. SExp symbol is 
the symbol and list is the S_Expression containing the list that 
symbol and its pair are a part of */
SExp assoc(SExp symbol, SExp list){
    SExp temp = malloc(sizeof(struct SExp));
    // Go through every pair and find which one equals "symbol"
    while(list != NULL){
        if(car(list) != NULL){
            SExp pair = malloc(sizeof(struct SExp));
            pair = car(list);
            if(car(pair) != NULL){
                SExp item = malloc(sizeof(struct SExp));
                item = car(pair);
                if(item->s->data != NULL){
                    if(!strcmp(symbol->s->data, item->s->data)){
                        // Symbol found, return the pair including symbol
                        return pair;
                    }
                }
            }
        }
        // Traverse through the list until symbol is found
        list = cdr(list);
    }
    // Symbol not found, return #f
    temp->s = makeCell("f");
    return temp;
}

/* Cond: Multiple Alternative conditional
Like an if statement, first part is the condition and
the second part is what you do if the condition is true
*/
SExp cond(SExp sexp){
    // First make sure the list isn't null
    if(sexp != NULL){
        // Then, make sure there is a conditional part
        SExp first = malloc(sizeof(struct SExp));
        first = car(sexp);
        if(first != NULL){
            // Check if the car (the condition) is true
            if(!strcmp(eval(car(first))->s->data, "#t")){
                // Make sure there is a second part
                if(cdr(first) != NULL){
                    // Run the second part
                    SExp secondOfFirst = malloc(sizeof(struct SExp));
                    secondOfFirst = cdr(first);
                    return eval(car(secondOfFirst));
                }
            }
        }
        // Cond statements can have multiple parts to run after the conditional part
        // Check if there's more of those
        if(cdr(sexp) != NULL){
            // Run cond again but with the cdr of sexp
            return cond(cdr(sexp)); // Recursive call
        }
    }
    // If we get here, and we haven't returned anything yet, return false
    SExp new = malloc(sizeof(struct SExp));
    new->s = makeCell("#f");
    return new;
}

/* Define handles define statements using the scheme functionality:
When the user types a define statement, define will take the first item
in the list and associate the second value in the list with the first
item. It will also store the pair in the global enviornment so that 
it can be referenced when needed.*/
SExp define(SExp symbol, SExp value){
    // Make an empty list
    SExp empty;
    empty = malloc(sizeof(struct SExp));
    empty->s = makeCell("()");
    // Cons the value with the empty list and store that in temp
    SExp temp = cons(value, empty);
    // Cons temp with the symbol and store that in pair
    SExp pair = cons(symbol, temp);
    // Add the pair to the global enviornment
    globalEnviornment = malloc(sizeof(struct SExp));
    globalEnviornment = cons(pair, globalEnviornment);
    // Return the symbol
    return symbol;
}

/* Eval: takes a conscell and evaluates it based on the special functions that the user may have inputted
such as car, cdr, quote, symbol?, and cons. Returns a conscell. 
*/
SExp eval(SExp sexp){
    if(globalEnviornment == NULL){
        globalEnviornment = malloc(sizeof(struct SExp));
        globalEnviornment = makeCell("()");
    }
    SExp rand = malloc(sizeof(struct SExp));
    SExp temp = malloc(sizeof(struct SExp));
    temp = NULL;
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
                }else if(!strcmp(data, "append")){
                    return append(temp, eval(car(cdr(cdr(sexp)))));
                }else if(!strcmp(data, "null?")){
                    return null(temp);
                }else if(!strcmp(data, "equal?")){
                    return equals(temp, eval(car(cdr(cdr(sexp)))));
                }else if(!strcmp(data, "assoc")){
                    return assoc(temp, eval(car(cdr(cdr(sexp)))));
                }else if(!strcmp(data, "cond")){
                    return cond(eval(cdr(sexp)));
                }else if(!strcmp(data, "define")){
                    return define(car(cdr(sexp)), eval(car(cdr(cdr(sexp)))));
                }
            }else if(strcmp(sexp->s->data, "")){
                // If we input something that is a symbol in the global Enviornment...
                SExp tool = malloc(sizeof(struct SExp));
                Cell cell = malloc(sizeof(struct conscell));
                tool->s = cell;
                tool->s->car = NULL;
                tool->s->cdr = NULL;
                strcpy(cell->data, sexp->s->data);
                SExp pair = malloc(sizeof(struct SExp));
                pair = assoc(tool, globalEnviornment);
                // Make sure the value associated with the symbol in the pair isn't null
                if(pair->s->car != NULL){
                    // Return the value associated with the symbol
                    return car(cdr(pair));
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
