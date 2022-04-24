# cs170FinalProject
Semester Project for CS170 - Analysis of Programming Languages

Part 1: 
Write a recursive descent parser for the subset of Scheme defined by the following EBNF grammar:
<s_expression> ⟶ ( { <s_expression> } ) | #t | #f | <symbol> | ().
  
Part 2:
Modify your S_Expression() function so that it returns the underlying "cons-cell" structure of the list that it parses.To complement this, 
write a function printSExp(SExp s) that, given a pointer to such a cons-cell structure, will print out the list in parenthesized form. Thus, given 
a pointer to the above structure, printSExp() will print out (a b c)
