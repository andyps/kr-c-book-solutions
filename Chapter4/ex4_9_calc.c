/*
A reverse-polish notation calculator.


To be machine independent and to accept EOF which is equal to -1
this 
"char buf[BUFSIZE];"
should be rewritten as signed char explicitly
"signed char buf[BUFSIZE];".

On the other hand if getch and ungetch should not work with EOF
they should be defined as below, so it is not neccessary
to check for EOF in other functions
*/
#include <stdio.h>
#include <stdlib.h>

#define MAXOP 100
#define NUMBER '0'

int getop(char s[]);
void push(double);
double pop(void);
void printstack(void);

int getch(void);
void ungetch(int);
void printbuf(void);
void clearbuf(void);

int main(void) {
  int type;
  double op2;
  char s[MAXOP];
  
  while ((type = getop(s)) != EOF) {
    switch (type) {
      case NUMBER:
        push(atof(s));
        break;
      case '+':
        push(pop() + pop());
        break;
      case '*':
        push(pop() * pop());
        break;
      case '-':
        op2 = pop();
        push(pop() - op2);
        break;
      case '%':
        op2 = pop();
        if (op2 != 0.0)
          push((int)pop() % (int)op2);
        else
          printf("error: zero divisor\n");
        break;
      case '/':
        op2 = pop();
        if (op2 != 0.0)
          push(pop() / op2);
        else
          printf("error: zero divisor\n");
        break;
      case '\n':
        printf("\t%.8g\n", pop());
        break;
      case 'p':
        printstack();
        break;
      default:
        printf("error: unknown command %s\n", s);
        break;
    }
  }

  return 0;
}

#define MAXVAL 100

int sp = 0;
double val[MAXVAL];

void push(double f) {
  if (sp < MAXVAL)
    val[sp++] = f;
  else
    printf("error: stack full, can't push %g\n", f);
}

double pop(void) {
  if (sp > 0)
    return val[--sp];
  else {
    printf("error: stack empty\n");
    return 0.0;
  }
}

void printstack(void) {
  int i;
  
  printf("***Print stack***\n");
  for (i = 0; i < sp; i++) {
    printf("\t%.8g\n", val[i]);
  }
  printf("***\n");
}

#include <ctype.h>

int getop(char s[]) {
  int i, c;
  
  while ((s[0] = c = getch()) == ' ' || c == '\t')
    ;
  s[1] = '\0';
  
  i = 0;

  // check for a negative number
  if (c == '-') {
    c = getch();
    if (!isdigit(c) && c != '.') {
      ungetch(c);
      return '-';
    } else {
      i = 1;
      s[1] = c;
      s[2] = '\0';
    }
  } else if (!isdigit(c) && c != '.') {
      return c;
  }
  
  if (isdigit(c))
    while (isdigit(s[++i] = c = getch()))
      ;
      
  if (c == '.')
    while (isdigit(s[++i] = c = getch()))
      ;
      
  s[i] = '\0';
  ungetch(c);
  
  return NUMBER;
}

#define BUFSIZE 100

signed char buf[BUFSIZE];
int bufp = 0;

int getch(void) {
  return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) {
  if (bufp >= BUFSIZE)
    printf("ungetch: too many characters\n");
  else if (c != EOF)
    buf[bufp++] = c;
}

void printbuf(void) {
  int i;
  
  printf("***Print buffer***\n");
  for (i = 0; i < bufp; i++) {
    printf("%d\n", buf[i]);
  }
  printf("***\n");
}

void clearbuf(void) {
  bufp = 0;
}
