#include <stdio.h>
#include <string.h>

#define MAXLINE 1000
#define SPACE '-'
#define TAB '\t'

int readline(char s[], int lim);

void entabLine(char src[], char res[], unsigned char tabSize) {
  int len, i, j, spaces;
  
  len = strlen(src);
  
  for (i = j = spaces = 0; i < len && j < MAXLINE - 1; i++) {
    if ((i + 1) % tabSize == 0 && src[i] == ' ') {
      res[j++] = spaces > 0 ? TAB : SPACE;
      spaces = 0;
      continue;
    }
    if (src[i] == ' ') {
      spaces++;
    } else {
      while (spaces > 0 && j < MAXLINE - 1) {
        res[j++] = SPACE;
        spaces--;
      }
      if (j < MAXLINE - 1) 
        res[j++] = src[i];
    }
  }

  res[j] = '\0';
}

void entab(unsigned char tabSize) {
  char s[MAXLINE];
  char line[MAXLINE];

  while (readline(line, MAXLINE) > 0) {
    entabLine(line, s, tabSize);

    printf("Result Line: %s\n", s);
  }
}

int main(void) {
  entab(3);

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
