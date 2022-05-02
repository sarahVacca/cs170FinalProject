# cs170FinalProject
Semester Project for CS170 - Analysis of Programming Languages

Part 1: 
https://mathcs.clarku.edu/~kebasye/cs170_2022/CS170HW/CS170Proj1.html
Write a recursive descent parser for the subset of Scheme defined by the following EBNF grammar:
<s_expression> ⟶ ( { <s_expression> } ) | #t | #f | <symbol> | ().
  
Part 2:
https://mathcs.clarku.edu/~kebasye/cs170_2022/CS170HW/CS170Proj2.html
Modify your S_Expression() function so that it returns the underlying "cons-cell" structure of the list that it parses.To complement this, 
write a function printSExp(SExp s) that, given a pointer to such a cons-cell structure, will print out the list in parenthesized form. Thus, given 
a pointer to the above structure, printSExp() will print out (a b c)
  
Part 3:
https://mathcs.clarku.edu/~kebasye/cs170_2022/CS170HW/CS170Proj3.html
If you have not already done so, be sure that your program evaluates all levels of function calls. It's a matter of having your function "eval" call itself at the correct times. In addition, for the rest of the project, be sure to continue to always evaluate arguments before evaluating a function. For example, (car (cdr '(a b c))) should return b, rather than cdr. (Of course, (car '(cdr (a b c))) WILL return cdr because the quote should continue to suppress evaluation.
This assignment sets up the necessary preliminaries for function definition. We will concentrate here on simply defining symbols to have values, which is much the same as defining constant functions. This is analogous to assigning values to variables in imperative languages.
  
Part 4:
https://mathcs.clarku.edu/~kebasye/cs170_2022/CS170HW/CS170Proj4.html
Enhance your interpreter so that it is capable of reading user function definitions and evaluating them correctly. Function definitions in Scheme are of the form,

   (define (< function-name > < formal-parameters >)
           < s-expression >)
Note that, by contrast with definitions of symbols, the function name and the formal parameters are presented as a list. For example:
      (define (member E L)
        (cond ((null? L) #f)
              ((equal? E (car L)) L)
              (else (member E (cdr L)))))
             
Part 5: OPTIONAL
https://mathcs.clarku.edu/~kebasye/cs170_2022/CS170HW/CS170Proj5.html
Make your interpreter even nicer than it is now. Add the following capabilites:
