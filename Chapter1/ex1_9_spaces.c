#include <stdio.h>

int main(void) {
  int c, last;
  
  last = EOF;
  while ((c = getchar()) != EOF) {
    if (c != ' ')
      putchar(c);
    else if (last != ' ')
      putchar(c);
    
    last = c;
  }

  return 0;
}
