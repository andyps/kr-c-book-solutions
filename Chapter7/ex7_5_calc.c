/*
= outputs result
Expects spaces around operands and operators
*/

#include <stdio.h>
#include <stdlib.h>

#define MAXOP 100
#define NUMBER '0'

int getop(double *);
void push(double);
double pop(void);

int main(void) {
  int type;
  double op2, f;

  while ((type = getop(&f)) != EOF) {
    switch (type) {
      case NUMBER:
        push(f);
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
      case '/':
        op2 = pop();
        if (op2 != 0.0)
          push(pop() / op2);
        else
          printf("error: zero divisor\n");
        break;
      case '=':
        printf("\t%.8g\n", pop());
        break;
      default:
        printf("error: unknown command %d\n", type);
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

#include <ctype.h>
int getch(void);
void ungetch(int);

int getop(double *f) {
  int c, r;

  r = scanf(" +%c", (char *)&c);
  if (r == EOF)
    return r;
  if (r == 1)
    return '+';
  
  r = scanf(" -%c", (char *)&c);
  if (r == EOF)
    return r;
  if (r == 1)
    return '-';

  r = scanf("%lf", f);
  if (r == 1)
    return NUMBER;
  if (r == EOF)
    return r;

  c = getchar();
  return c;
}
