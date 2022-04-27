#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "parser.h"
#include "parser.c"

// Return the car of cell
Cell car(Cell cell){
    return cell->car;
}

// Return the cdr of cell
Cell cdr(Cell cell){
    return cell->cdr;
}

// Return cell as it is
Cell quote(Cell cell){
    return cell;
}

// Symbol? If there is data in cell, it must be a symbol
// return true. If the data is null, return false.
Cell symbol(Cell cell){
    if(cell->data != NULL){
        return makeCell("#t");
    }else{
        return makeCell("#f");
    }
}

// Cons: Take one conscell and make it the car of the second conscell
Cell cons(Cell one, Cell two){
    // Make new cell
    Cell cell = makeCell(NULL);
    // If they are both false, return a null cell
    if(car(one)->data != NULL && !strcmp(car(one)->data, "#f")){
        if(car(two)->data != NULL && !strcmp(car(two)->data, "#f")){
            return makeCell(NULL);
        }
        // If only the first one is false, return the second one
        return two;
    }
    // If only the second one is false, return the first one
    if(car(two)->data != NULL && !strcmp(car(two)->data, "#f")){
        return one;
    }
    // If neither are false, set the car of new cell equal to the first cell
    // and the cdr of the new cell equal to the second cell
    cell->car = one;
    cell->cdr = two;
    // return the new cell
    return cell;
}

/* Eval: takes a conscell and evaluates it based on the special functions that the user may have inputted
such as car, cdr, quote, symbol?, and cons. Returns a conscell. 
*/
Cell eval(Cell cell){
    Cell temp = NULL;
    // First make sure the cell is not null
    if(cell != NULL){
        // Then, make sure the car of the cell is not null
        if(car(cell) != NULL){
            // Then, make sure the data of the car of the cell is not null
            if(car(cell)->data != NULL){
                char *data = car(cell)->data;
                /*Then, to be consistent with scheme, we have to evaluate the code "cdr first"
                So, if the code is (car (cdr (a b c))), we have to find the cdr of (a b c) first,
                and then the car of the cdr of (a b c). */
                temp = eval(car(cdr(cell))); // This will recurse all the way to the first data that we need to eval
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
                    return cons(temp, eval(car(cdr(cdr(cell)))));
                }
            }else{
                // Else, if the data of the car of the cell is null...
                printf("%s", cell->data);
                eval(car(cell));
                // If there's no more concells to recurse into...
                if(cell->cdr == NULL){
                    // Return the cell
                    return cell;
                }
            }
        }
        // If the cell is not null and we end up here, return the cell
        return cell; 
    }
}
