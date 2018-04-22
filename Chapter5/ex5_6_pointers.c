#include "stdio.h"
#include "string.h"
#include "ctype.h"

void reverseOriginal(char s[]) {
  int c, i, j;
  
  for (i = 0, j = strlen(s) - 1; i < j; i++, j--) {
    c = s[i];
    s[i] = s[j];
    s[j] = c;
  }
}

void reverseNew(char *s) {
  int c, i, j;

  for (i = 0, j = strlen(s) - 1; i < j; i++, j--) {
    c = *(s + i);
    *(s + i) = *(s + j);
    *(s + j) = c;
  }
}

int strindexOriginal(char s[], char t[]) {
  int i, j, k;
  
  for (i = 0; s[i] != '\0'; i++) {
    for (j = i, k = 0; t[k] != '\0' && s[j] == t[k]; j++, k++)
      ;
    
    if (k > 0 && t[k] == '\0')
      return i;
  }
  
  return -1;
}

int strindexNew(char *s, char *t) {
  int i, j, k;
  
  i = 0;
  while (*s) {
    k = 0;
    j = 0;
    while (*(t + k) && *(s + j) == *(t + k)) {
      j++;
      k++;
    }
    
    if (k > 0 && *(t + k) == '\0') 
      return i;
    
    s++;
    i++;
  }

  return -1;
}

int getlineOriginal(char s[], int lim) {
  int c, i;
  
  i = 0;
  while (--lim > 0 && (c = getchar()) != EOF && c != '\n')
    s[i++] = c;
    
  if (c == '\n')
    s[i++] = c;
    
  s[i] = '\0';
  return i;
}

int getlineNew(char *s, int lim) {
  int c, i;
  
  i = 0;
  while (--lim > 0 && (c = getchar()) != EOF && c != '\n')
    *(s + i++) = c;
    
  if (c == '\n')
    *(s + i++) = c;

  *(s + i) = '\0';

  return i;
}

int atoiOriginal(char s[]) {
  int i, n, sign;
  
  for (i = 0; isspace(s[i]); i++)
    ;
    
  sign = (s[i] == '-') ? -1 : 1;
  if (s[i] == '+' || s[i] == '-')
    i++;
    
  for (n = 0; isdigit(s[i]); i++)
    n = 10 * n + (s[i] - '0');
    
  return sign * n;
}

int atoiNew(char *s) {
  int n, sign;
  
  while (isspace(*s)) {
    s++;
  }
  
  sign = (*s == '-') ? -1 : 1;
  if (*s == '+' || *s == '-')
    s++;
  
  n = 0;
  while (isdigit(*s)) {
    n = 10 * n + (*s - '0');
    s++;
  }

  return sign * n;
}

void itoaOriginal(int n, char s[]) {
  int i, sign;

  if ((sign = n) < 0) {
    n = -n;
  }

  i = 0;
  do {
    s[i++] = n % 10 + '0';
  } while ((n /= 10) > 0);
  
  if (sign < 0) {
    s[i++] = '-';
  }

  s[i] = '\0';

  reverseOriginal(s);
}

void itoaNew(int n, char *s) {
  int sign;
  char *s0 = s;

  if ((sign = n) < 0) {
    n = -n;
  }

  do {
    *s++ = n % 10 + '0';
  } while ((n /= 10) > 0);

  if (sign < 0) {
    *s++ = '-';
  }

  *s = '\0';

  reverseNew(s0);
}

#define NUMBER '0'
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

int getopOriginal(char s[]) {
  int i, c;
  
  while ((s[0] = c = getch()) == ' ' || c == '\t')
    ;
  s[1] = '\0';

  if (!isdigit(c) && c != '.') {
      return c;
  }
  
  i = 0;
  
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

int getopNew(char *s) {
  int c;
  
  while ((*s = c = getch()) == ' ' || c == '\t')
    ;
  *(s + 1) = '\0';

  if (!isdigit(c) && c != '.') {
      return c;
  }

  if (isdigit(c))
    while (isdigit(*++s = c = getch()))
      ;
      
  if (c == '.')
    while (isdigit(*++s = c = getch()))
      ;
      
  *s = '\0';
  if (c != EOF)
    ungetch(c);
  
  return NUMBER;
}

int main(void) {
  int n;
  char s1[] = "abc";
  char s2[100];
  char s3[100];
  char s4[100];
  
  /* test reverse */
  reverseNew(s1);
  printf("reverse: %s\n", s1);
  
  /* test strindex */
  printf("strindex: %d\n", strindexNew("1234567", "345"));
  
  /* test atoi */
  printf("atoi: %d\n", atoiNew(" -123456"));
  
  /* test itoa */
  itoaNew(-123, s2);
  printf("itoa: %s\n", s2);
  
  /* test getline */
  n = getlineNew(s3, 10);
  printf("\ngetline: %d-%s\n", n, s3);
  
  /* test getop */
  n = getopNew(s4);
  printf("\ngetop: %d-%s\n", n, s4);
  
  return 0;
}
