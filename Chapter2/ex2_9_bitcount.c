#include "stdio.h"
/*
Counts 1 bits
*/
int bitcount(unsigned x) {
  int b;
  
  for (b = 0; x != 0; x >>= 1)
    if (x & 01)
      b++;

  return b;
}
/*
Counts 1 bits and uses x &= (x - 1)
*/
int bitcount2(unsigned x) {
  int b = 0;
  
  while (x > 0) {
    x &= (x - 1);
    b++;
  }

  return b;
}

int main(void) {
  int x = 5;
  
  printf("%d=%d\n", x & (x - 1), x & ~1); // the result is equal for odd
  
  printf("%d=%d\n", bitcount(x), bitcount2(x));
  
  return 0;
}
