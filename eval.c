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
