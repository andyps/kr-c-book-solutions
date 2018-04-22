#include "stdio.h"

int any(char s[], char s2[]) {
  int i, j;

  for (i = 0; s[i] != '\0'; i++) {
    for (j = 0; s2[j] != '\0'; j++) {
      if (s[i] == s2[j]) {
        return i;
      }
    }
  }

  return -1;
}

int main(void) {
  char s[] = "1abcd2abcd3abcd";
  char s2[] = "32c";

  printf("%d\n", any(s, s2));

  return 0;
}
