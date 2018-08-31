#include<stdio.h>
#include<string.h>
#include<stdlib.h>

void expr(char *str, int i);
void id(char *str, int i);
void factor(char *str, int i);
void term(char *str, int i);

int is_add(char ch)
{
    if(ch=='+' || ch=='-')
        return 1;
    else
        return 0;
}
int is_mul(char ch)
{
    if(ch=='*' || ch=='/')
        return 1;
    else
        return 0;
}
void printSpace(int l)
{
	for(int i=0;i<l;i++)
		printf(" ");
}
void removeSpaces(char* source)
{
  char* i = source;
  char* j = source;
  while(*j != 0)
  {
    *i = *j++;
    if(*i != ' ')
      i++;
  }
  *i = 0;
}

void id(char *str, int i)
{
	printSpace(i);
	printf("[id [%s]]\n", str);
}

// <factor> -> <id> | ( <expr> )
void factor(char *str, int i)
{
	// start factor
	printSpace(i);
	printf("[factor\n");
	// handle ( <expr> )
	if (*str == '(') {
		// skip '('
		str++;
		size_t len = sizeof(str);
		// skip ')'
		str[len-2] = '\0';
		expr(str, i+2);
	} else {
		// <id>
		id(str, i+2);
	}
	// end factor
	printSpace(i);
	printf("]\n");
}

// <term> -> <factor> { ( * | / ) <factor> }
void term(char *str, int i)
{
	// start term
	printSpace(i);
	printf("[term\n");
	// find '+' or '-'
	char *head = str;
	// handle ()
	if (*str=='(') {
		while (*str!=')')
			str++;
		str++;
	}
	// find * or /
	while (!is_mul(*str)) {
		if (*str == '\0')
			break;
		str++;
	}
	// no * or /
	if (*str == '\0')
		factor(head, i+2);
	// factor (*|/) factor
	else {
		// operator
		char op = *str;
		*str = '\0';
		// factor head
		factor(head, i+2);
		// print * or /
		printSpace(i+2);
		printf("[%c]\n", op);
		str++;
		// factor rest
		factor(str, i+2);
	}
	// end assign
	printSpace(i);
	printf("]\n");
}

// <expr> -> <term> { ( + | - ) <term> }
void expr(char *str, int i)
{
	// start expr
	printSpace(i);
	printf("[expr\n");
	// find '+' or '-'
	char *head = str;
	// handle ()
	if (*str=='(') {
		while (*str!=')')
			str++;
		str++;
	}
	// find + or -
	while (!is_add(*str)) {
		if (*str == '\0')
			break;
		str++;
	}
	// no + or -
	if (*str == '\0') 
		term(head, i+2);
	// term (+|-) term
	else {
		char op = *str;
		*str = '\0';
		// term head
		term(head, i+2);
		// print + or -
		printSpace(i+2);
		printf("[%c]\n", op);
		str++;
		// term rest
		term(str, i+2);
	}
	// end expr
	printSpace(i);
	printf("]\n");
} 

// <assign> -> <id> = <expr>
void assign(char *str, int i) {
	// start assign
	printSpace(i);
	printf("[assign\n");
	char *head = str;
	// find '='
	while (*str != '=')
		str++;
	// separate str
	*str = '\0';
	// id
	id(head, i+2);
	// print '=''
	printSpace(i+2);
	printf("[=]\n");
	// expr
	str++;
	expr(str, i+2);
	// end assign
	printSpace(i);
	printf("]\n");
}

int main()
{
   int i;
   char str[500]; //used to store input string
   printf("Enter String:\n");
   scanf("%[^\n]c",str);
   // remove space
   removeSpaces(str);
   // call assign()
   assign(str, 0);
   return 0;
}