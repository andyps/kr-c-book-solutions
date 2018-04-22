#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXLINE 1000
#define DEFTAB 4
#define DEFSTART 0

int readline(char s[], int lim);

void detabLine(char src[], char res[], unsigned char start, unsigned char tabSize) {
  int len, i, j, spaces;
  
  len = strlen(src);
  
  for (i = j = 0; i < len && j < MAXLINE - 1; i++) {
    if (src[i] == '\t' && i >= start) {
      spaces = tabSize - (j - start) % tabSize;
      while (spaces > 0 && j < MAXLINE - 1) {
        res[j++] = '-';
        spaces--;
      }
    } else {
      res[j++] = src[i];
    }
  }
  
  res[j] = '\0';
}

void detab(unsigned char start, unsigned char tabSize) {
  char s[MAXLINE];
  char line[MAXLINE];

  while (readline(line, MAXLINE) > 0) {
    detabLine(line, s, start, tabSize);

    printf("Result Line: %s\n", s);
  }
}

int main(int argc, char *argv[]) {
  int n, m;
  
  n = m = -1;

  ++argv;
  while (--argc > 0 && (*argv[0] == '-' || *argv[0] == '+')) {
      if (*argv[0] == '-') {
          m = -atoi(*argv);
      }
      if (*argv[0] == '+') {
          n = atoi(*argv);
      }
      ++argv;
  }
  
  n = n < 2 ? DEFTAB : n;
  m = m < 0 ? DEFSTART : m;

  detab(m, n);
   
  return 0;
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
