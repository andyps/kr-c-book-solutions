#include <stdio.h>

#define MAXLINE 1000

int getline(char line[], int maxline);
int removeTrailingTabsAndSpaces(char line[]);

int main(void) {
  int len;
  char line[MAXLINE];
  
  while ((len = getline(line, MAXLINE)) > 0) 
    if (removeTrailingTabsAndSpaces(line) > 0)
      printf("%s", line);

  return 0;
}

int removeTrailingTabsAndSpaces(char line[]) {
  int i, lastPos;
  int hasNewLineCh;
  
  hasNewLineCh = 0;
  lastPos = -1;
  i = 0;
  while (line[i] != '\0') {
    if (line[i] == '\n') {
      hasNewLineCh = 1;
      i++;
      break;
    }
    if (line[i] == ' ' || line[i] == '\t') {
      if (lastPos == -1)
        lastPos = i;
    } else {
      lastPos = -1;
    }
    i++;
  }
  
  if (lastPos == 0) {
    line[0] = '\0';
    return 0;
  }
  if (lastPos > 0) {
    if (hasNewLineCh) {
      line[lastPos++] = '\n';
    }
    line[lastPos] = '\0';
    return lastPos;
  }

  return i;
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
