#include "stdio.h"

/*
Rotate number to right
*/
unsigned rightrot(unsigned x, unsigned n) {
  unsigned mask = ~0u / 2;
  while (n > 0) {
    if (x & 1) {
      x = (x >> 1) | ~mask;
    } else {
      // as x is unsigned applying the mask is not necessary
      x = (x >> 1) & mask;
    }
    --n;
  }
  
  return x;
}

int main(void) {
  printf("Result: %u\n", rightrot(6, 2));

  return 0;
}
