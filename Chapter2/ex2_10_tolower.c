#include "stdio.h"

/*
Uppercase to lowercase
*/
int lower(int c) {
  if (c >= 'A' && c <= 'Z')
    return c + 'a' - 'A';
  else
    return c;
}

int lower2(int c) {
  return c >= 'A' && c <= 'Z' ? c + 'a' - 'A' : c;
}

int main(void) {
  printf("%c=%c\n", lower('V'), lower2('V'));
  return 0;
}
