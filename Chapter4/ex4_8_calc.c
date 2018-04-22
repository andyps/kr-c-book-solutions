/*
A reverse-polish notation calculator
*/
#include <stdio.h>
#include <stdlib.h>

#define MAXOP 100
#define NUMBER '0'

int getop(char s[]);
void push(double);
double pop(void);
void printstack(void);

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
int getch(void);
void ungetch(int);

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
      if (c != EOF)
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
  if (c != EOF)
    ungetch(c);
  
  return NUMBER;
}

/*
Buffer size is one in this exercise
*/
char buf = EOF;

int getch(void) {
  char result;
  if (buf != EOF) {
    result = buf;
    buf = EOF;
    return result;
  }
  return getchar();
}

void ungetch(int c) {
  buf = c;
}
