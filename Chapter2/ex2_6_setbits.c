#include "stdio.h"

unsigned getbits(unsigned x, int p, int n) {
  if (p + 1 - n < 0) {
    return 0;
  }

  return (x >> (p + 1 - n)) & ~(~0 << n);
}

unsigned setbits(unsigned x, int p, int n, unsigned y) {
  int xLastBitsCnt = p + 1 - n;
  if (xLastBitsCnt < 0) {
    return 0;
  }

  unsigned yLastNBits = getbits(y, n - 1, n);
  unsigned xLastBits = xLastBitsCnt ? getbits(x, xLastBitsCnt - 1, xLastBitsCnt) : 0;
  unsigned mask = (~0 << (p + 1)) | xLastBits;
  return x & mask | (yLastNBits << xLastBitsCnt);
}

int main(void) {
  printf("Result: %d\n", setbits(29, 3, 3, 9));
  return 0;
}
