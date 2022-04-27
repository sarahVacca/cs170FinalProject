/**********************************************************************
 File: parser.h
 ----------------
 This is the interface for a parser for part of Scheme.
 It takes input from the user and determines if its a valid Scheme
 S Expression defined by the following grammar:
 <s_expression>⟶( { <s_expression> } ) | #t | #f | <symbol> | ()
 If the input is valid, it returns the parse tree for the expression
**********************************************************************/
#ifndef PARSER
#define PARSER
#include <stdlib.h>
#include "lexer.h"

/****************************************************************
 Struct: conscell
 ------------------------------------
*/
typedef struct conscell{
    char* data;
    struct conscell *car;
    struct conscell *cdr;
}*Cell;

struct SExp{
      Cell * cell; 
}*SExp;

/****************************************************************
 Array of characters
 ------------------------------------
*/
char token[20];

/****************************************************************
 Function: S_Expression()
 ------------------------------------
 Takes scheme code and returns the underlying "cons-cell" structure
 represented by the code
*/
Cell S_Expression();

Cell makeCell();

/****************************************************************
 Function: parse()
 ------------------------------------
 Runs the S_Expression function.
*/
Cell parse();

/****************************************************************
 Function: printSExp()
 ------------------------------------
 Takes the conscell representation of scheme code and prints it in
 S_Expression form
*/
void printSExp(Cell cell);

#endif