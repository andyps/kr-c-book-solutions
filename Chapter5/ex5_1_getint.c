#include "stdio.h"
#include "ctype.h"

int getch(void);
void ungetch(int);

int getintOriginal(int *pn) {
  int c, sign;
  
  while (isspace(c = getch()))
    ;
  
  if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
    ungetch(c);
    return 0;
  }
  sign = (c == '-') ? -1 : 1;
  
  if (c == '+' || c == '-')
    c = getch();
  
  for (*pn = 0; isdigit(c); c = getch())
    *pn = 10 * *pn + (c - '0');
  
  *pn *= sign;
  if (c != EOF)
    ungetch(c);
  
  return c;
}

int getint(int *pn) {
  int c, sign, nextC;
  
  while (isspace(c = getch()))
    ;
  
  if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
    ungetch(c);
    return 0;
  }
  sign = (c == '-') ? -1 : 1;
  
  if (c == '+' || c == '-') {
    nextC = getch();
    if (!isdigit(nextC) && nextC != EOF) {
      ungetch(nextC);
      ungetch(c);
      return 0;
    }
    c = nextC;
  }
  
  for (*pn = 0; isdigit(c); c = getch())
    *pn = 10 * *pn + (c - '0');
  
  *pn *= sign;
  if (c != EOF)
    ungetch(c);
  
  return c;
}

#define SIZE 100

int main(void) {
  int n, array[SIZE], getint(int *);

  /* fill array just for testing */
  for (n = 0; n < SIZE; n++) {
      array[n] = -777;
  }
  
  for (n = 0; n < SIZE && getint(&array[n]) != EOF; n++)
    ;

  printf("Result:\n");
  for (n = 0; n < SIZE; n++) {
      printf("%d, ", array[n]);
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
