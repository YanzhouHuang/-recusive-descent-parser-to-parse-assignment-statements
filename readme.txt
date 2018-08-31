In this project, you will implement a recusive-descent parser to parse assignment statements. Recall that a recusive-descent parser is a top-down parser consisting of a collection of subprograms, many of which are recursive.
The grammar used for this project is the following:
   <assign> -> <id> = <expr>
   <expr>   -> <term> { ( + | - ) <term> }
   <term>   -> <factor> { ( * | / ) <factor> }
   <factor> -> <id> | ( <expr> )
The identifier lexeme is defined in your first project on scanner.
For example, for the input expression, A = B1 + B2, the above gammar will give you the following parse tree.

Go to command prompt
input gcc project2.c
input .\a.exe
Enter String:
A=B+C

it will display the output
