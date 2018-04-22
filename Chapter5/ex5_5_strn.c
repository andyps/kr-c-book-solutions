#include "stdio.h"


int strncmpVersion(char *s, char *t, int n) {
  for (; *s == *t; s++, t++) {
    n--;

    if (*s == '\0' || n <= 0)
      return 0;
  }
  
  return *s - *t;
}

void strncpyVersion(char *s, char *t, int n) {
  while (n > 0 && (*s++ = *t++))
    n--;
  
  if (n <= 0) {
    *s = '\0';
  }
}

void strncatVersion(char *s, char *t, int n)
{
  while (*s)
    s++;
    
  while (n > 0 && (*s++ = *t++))
    n--;
    
  if (n <= 0) {
    *s = '\0';
  }
}

int main(void) {
  char s1[] = "str";
  char s2[] = "string";

  strncpyVersion(s1, "123", 3);
  printf("Result strncpy: %s\n", s1);

  strncatVersion(s2, "tail", 3);
  printf("Result strncat: %s\n", s2);
  
  printf("Result strncmp: %d\n", strncmpVersion("abc", "abdef", 2));
  
  return 0;
}
