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

int ungetch(int);
void ungets(char s[]);
int getch(void);
void printbuf(void);
void clearbuf(void);

void testungets(void) {
  ungetch('a');
  ungetch('b');
  printbuf();
  printf("getch %c\n", getch());
  printbuf();
  ungets("cd");
  printf("getch %c\n", getch());
  printbuf();
  clearbuf();
}

int main(void) {
  int type;
  double op2;
  char s[MAXOP];
  
  testungets();
  
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
int ungetch(int);
void ungets(char s[]);

int getop(char s[]) {
  int i, c;
  
  while ((s[0] = c = getch()) == ' ' || c == '\t')
    ;
  s[1] = '\0';
  
  i = 0;
  
  /* check for a negative number */
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

int ungetch(int c) {
  if (bufp >= BUFSIZE) {
    printf("ungetch: too many characters\n");
    return 0;
  } else
    buf[bufp++] = c;

  return 1;
}

void ungets(char s[]) {
  int i = 0;

  while (s[i] != '\0') {
    if (!ungetch(s[i]))
      break;
    i++;
  }
}

void printbuf(void) {
  int i;
  
  printf("***Print buffer***\n");
  for (i = 0; i < bufp; i++) {
    printf("%c\n", buf[i]);
  }
  printf("***\n");
}

void clearbuf(void) {
  bufp = 0;
}
