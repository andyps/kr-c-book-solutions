#include <stdio.h>

unsigned int strend(char *s, char *t) {
  unsigned sLen, tLen;

  sLen = tLen = 0;

  while (*s) {
    s++;
    sLen++;
  }
    
  while (*t) {
    t++;
    tLen++;
  }
  
  if (sLen < tLen) {
    return 0;
  }
  
  while (tLen > 0) {
    if (*--t != *--s) {
      return 0;
    }

    tLen--;
  }
  
  return 1;
}

int main(void) {
  char s[] = "string-t1";

  printf("Result1: %u\n", strend(s, "t1"));
  printf("Result2: %u\n", strend(s, "t2"));
  printf("Result3: %u\n", strend(s, "string-t1"));
  printf("Result4: %u\n", strend(s, "string-t1-too large"));
  printf("Result5: %u\n", strend(s, ""));

  return 0;
}
