#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAXOP 100
#define NUMBER '0'

int getop(char s[]);
void push(double);
double pop(void);

double last(void);
void duplicate(void);
void swap(void);
void clearstack(void);
void printstack(void);

int main(void) {
  int type;
  double op2;
  char s[MAXOP];
  
  while ((type = getop(s)) != EOF) {
    // printstack();
    
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
        // get the last element in the stack
        printf("\t%.8g\n", last());
        break;

      case 'd':
        duplicate();
        break;
      case 's':
        swap();
        break;
      case 'c':
        clearstack();
        break;
      case 'p':
        printstack();
        break;
        
      case '^':
        op2 = pop();
        push(pow(pop(), op2));
        break;
      case '~':
        push(sin(pop()));
        break;
      case 'e':
        push(exp(pop()));
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
/*
pop without deleting
*/
double last(void) {
  if (sp > 0)
    return val[sp - 1];
  else {
    printf("stack empty\n");
    return 0.0;
  }
}
/*
Duplicate the last element
*/
void duplicate(void) {
  if (sp > 0)
    push(val[sp - 1]);
  else
    printf("error: stack empty\n");
}
/*
Swap two last elements
*/
void swap(void) {
  double last, lastbutone;
  
  if (sp > 1) {
    last = pop();
    lastbutone = pop();
    push(last);
    push(lastbutone);
  } else
    printf("error: less than two elements are in stack\n");
}

void clearstack(void) {
  sp = 0;
}

void printstack(void) {
  int i;
  
  printf("***Print stack***\n");
  for (i = 0; i < sp; i++) {
    printf("%.8g%c", val[i], (i < sp - 1) ? ',' : '\n');
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

#define BUFSIZE 100

char buf[BUFSIZE];
int bufp = 0;

int getch(void) {
  return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) {
  if (bufp >= BUFSIZE)
    printf("ungetch: too many characters\n");
  else
    buf[bufp++] = c;
}
