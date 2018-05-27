/*
The input that tests boundary conditions is the kind
of input that is most likely to uncover bugs.
For example:
completely empty input,
empty lines (with spaces only or completely empty),
words consisting of one character,
more than one space between words
*/
#include <stdio.h>

#define IN 1
#define OUT 0

int main(void) {
  int c, nl, nw, nc, state;
  
  state = OUT;
  nl = nw = nc = 0;
  
  while ((c = getchar()) != EOF) {
    ++nc;
    if (c == '\n') 
      ++nl;
    if (c == ' ' || c == '\n' || c == '\t') 
      state = OUT; 
    else if (state == OUT) {
      state = IN; 
      ++nw; 
    } 
  }
  
  printf("%d %d %d\n", nl, nw, nc); 

  return 0;
}
