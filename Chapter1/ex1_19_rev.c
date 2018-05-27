#include <stdio.h>

#define MAXLINE 1000

int getline(char line[], int maxline);
void reverse(char line[]);

int main(void) {
  int len;
  char line[MAXLINE];
  
  while ((len = getline(line, MAXLINE)) > 0) {
    reverse(line);
    printf("%s", line);
  }

  return 0;
}

void reverse(char line[]) {
  int i, len, c;
  
  i = 0;
  while (line[i] != '\n' && line[i] != '\0') {
    i++;
  }
  len = i; /* length excluding \n */
  
  for (i = 0; i < len; i++) {
    if (i < len - i - 1) {
      c = line[i];
      line[i] = line[len - i - 1];
      line[len - i - 1] = c;
    } else
      break;
  }
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
