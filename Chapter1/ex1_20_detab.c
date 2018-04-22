#include <stdio.h>
#include <string.h>

#define MAXLINE 1000

int readline(char s[], int lim);

void detabLine(char src[], char res[], unsigned char tabSize) {
  int len, i, j, spaces;
  
  len = strlen(src);
  
  for (i = j = 0; i < len && j < MAXLINE - 1; i++) {
    if (src[i] == '\t') {
      spaces = tabSize - j % tabSize;
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

void detab(unsigned char tabSize) {
  char s[MAXLINE];
  char line[MAXLINE];

  while (readline(line, MAXLINE) > 0) {
    detabLine(line, s, tabSize);

    printf("Result Line: %s\n", s);
  }
}

int main(void) {
  detab(4);

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
