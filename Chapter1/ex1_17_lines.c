#include <stdio.h>

#define MAXLINE 1000

int getline(char line[], int maxline);

int main(void) {
  int len;
  char line[MAXLINE];
  
  while ((len = getline(line, MAXLINE)) > 0) 
    if (len > 80)
      printf("(%d)%s", len, line);

  return 0;
}

int getline(char s[] , int lim) {
  int c, i, j;
  
  for (i = 0, j = 0; (c = getchar()) != EOF && c != '\n'; ++i) {
    if (i < lim - 1)
      s[j++] = c;
  }
  if (c == '\n') {
    ++i;
    if (j < lim - 1)
      s[j++] = c;
  }
  s[j] = '\0'; 
  return i;
}
