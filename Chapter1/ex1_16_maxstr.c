#include <stdio.h>

#define MAXLINE 1000

int _getline(char linef[], int maxline);
void copy(char to[], char from[]);

int main(void) {
  int len;
  int max;
  char line[MAXLINE];
  char longest[MAXLINE];
  
  max = 0; 
  while ((len = _getline(line, MAXLINE)) > 0) 
    if (len > max) {
      max = len; 
      copy(longest, line); 
    }
  if (max > 0)
    printf("(%d)%s", max, longest);
  
  return 0;
}

int _getline(char s[] , int lim) {
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

void copy (char to[], char from[]) {
  int i; 
  
  i = 0; 
  while ((to[i] = from[i]) != '\0')
    ++i;
}
