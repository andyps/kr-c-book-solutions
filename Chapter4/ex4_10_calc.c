/*
A reverse-polish notation calculator.

Version with 'getline' (which is named 'readline' here) function.
*/
#include <stdio.h>
#include <stdlib.h>

#define MAXOP 100
#define NUMBER '0'
#define BUFSIZE 100

int getop(char s[]);
void push(double);
double pop(void);
void printstack(void);

char buf[BUFSIZE];
int bufp;
int readline(char s[], int lim);

int main(void) {
  int type;
  double op2;
  char s[MAXOP];
  
  
  while (readline(buf, BUFSIZE) > 0) {
    bufp = 0;
    while ((type = getop(s)) != '\0') {
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
          printf("error: unknown command %s-%d\n", s, type);
          break;
      }
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
  
  while ((s[0] = c = buf[bufp++]) == ' ' || c == '\t')
    ;
  s[1] = '\0';
  
  i = 0;
  
  /* check for a negative number */
  if (c == '-') {
    c = buf[bufp++];
    if (!isdigit(c) && c != '.') {
      bufp--;
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
    while (isdigit(s[++i] = c = buf[bufp++]))
      ;
      
  if (c == '.')
    while (isdigit(s[++i] = c = buf[bufp++]))
      ;
      
  s[i] = '\0';
  bufp--;
  
  return NUMBER;
}

int readline(char s[], int lim) {
  int c, i;
  
  i = 0;
  while (--lim > 0  && (c = getchar()) != EOF && c != '\n')
    s[i++] = c;
    
  if (c == '\n')
    s[i++] = c;

  s[i] = '\0';
  return i;
}
