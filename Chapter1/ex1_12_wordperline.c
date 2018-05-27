#include <stdio.h>

#define IN 1
#define OUT 0

int main(void) {
  int c, state;
  
  state = OUT;
  
  while ((c = getchar()) != EOF) {
    if (c == ' ' || c == '\n' || c == '\t') {
      if (state == IN && c != '\n') {
        putchar('\n');
      }
      state = OUT; 
    } else if (state == OUT) {
      state = IN;
      putchar(c);
    } else
      putchar(c);
  }

  return 0;
}
