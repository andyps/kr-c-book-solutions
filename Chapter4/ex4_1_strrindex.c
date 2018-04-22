#include "stdio.h"

/*
Search the first position from left
*/
int strindex(char s[], char t[]) {
  int i, j, k;
  
  for (i = 0; s[i] != '\0'; i++) {
    for (j = i, k = 0; t[k] != '\0' && s[j] == t[k]; j++, k++)
      ;
    if (k > 0 && t[k] == '\0')
      return i;
  }
  return -1;
}

/*
Search the first position from right
*/
int strrindex(char s[], char t[]) {
  int i, j, k;
  int idx = -1;
  
  for (i = 0; s[i] != '\0'; i++) {
    for (j = i, k = 0; t[k] != '\0' && s[j] == t[k]; j++, k++)
      ;
    if (k > 0 && t[k] == '\0')
      idx = i;
  }
  return idx;
}

int main(void) {

  printf("Result1: %d\n", strindex("bolodolo", "olo"));
  printf("Result2: %d\n", strrindex("bolodolo", "olo"));
  
  return 0;
}
