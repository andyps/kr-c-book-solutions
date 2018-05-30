#include <stdio.h>

int skipComment(void);
int processString(int);

int main(void) {
  int c1, c2;
  
  while ((c1 = getchar()) != EOF) {
    c2 = '\0';
    if (c1 == '/') {
      c2 = getchar();
      if (c2 == '*') {
        c2 = skipComment();
      } else {
        putchar(c1);
        if (c2 != EOF)
          putchar(c2);
      }
    } else if (c1 == '"' || c1 == '\'') {
      c2 = processString(c1);
    } else
      putchar(c1);
    
    if (c2 == EOF)
      break;
  }
  
  return 0;
}

int processString(int delim) {
  int c1;

  putchar(delim);

  while ((c1 = getchar()) != delim && c1 != EOF) {
    if (c1 == '\\') {
      c1 = getchar();
      if (c1 == '\'' || c1 == '"')
        putchar(c1);
      else if (c1 == EOF) {
        putchar('\\');
        break;
      } else {
        putchar('\\');
        putchar(c1);
      }
    } else
      putchar(c1);
  }
  
  if (c1 != EOF) {
    putchar(delim);
  }
  return c1;
}

int skipComment(void) {
  int c;
  int prev = '\0';

  while ((c = getchar()) != EOF) {
    if (prev == '*' && c == '/') {
      break;
    }
    prev = c;
  }
  return c;
}
