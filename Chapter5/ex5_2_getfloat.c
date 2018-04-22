#include "stdio.h"
#include "ctype.h"

int getch(void);
void ungetch(int);

int getfloat(double *pn) {
  double power;
  int c, sign;
  
  power = 1.0;

  while (isspace(c = getch()))
    ;
  
  if (!isdigit(c) && c != EOF && c != '+' && c != '-' && c != '.') {
    ungetch(c);
    return 0;
  }
  sign = (c == '-') ? -1 : 1;
  
  if (c == '+' || c == '-')
    c = getch();
    
  for (*pn = 0.0; isdigit(c); c = getch())
    *pn = 10.0 * *pn + (c - '0');
  
  if (c == '.') {
    c = getch();
    
    for (; isdigit(c); c = getch()) {
      *pn = 10.0 * *pn + (c - '0');
      power *= 10;
    }
  }

  *pn *= sign / power;

  if (c != EOF)
    ungetch(c);
  
  return c;
}

#define SIZE 100

int main(void) {
  int n, getfloat(double *);
  double array[SIZE];

  for (n = 0; n < SIZE; n++) {
      array[n] = -777.;
  }
  
  for (n = 0; n < SIZE && getfloat(&array[n]) != EOF; n++)
    ;

  printf("Result:\n");
  for (n = 0; n < SIZE; n++) {
      printf("%.6g, ", array[n]);
  }
  
  return 0;
}

/* getch and ungetch functions can be put into a separate file */
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
