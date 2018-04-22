#include "stdio.h"

/*
Get n bits of x starting from position p.
p is a position from right and the very right bit is at position 0
*/
unsigned getbits(unsigned x, int p, int n) {
  if (p + 1 - n < 0) {
    return 0;
  }

  return (x >> (p + 1 - n)) & ~(~0 << n);
}
/*
Fill n bits of x starting from position p with last n bits from y.
p is a position from right and the very right bit is at position 0
*/
unsigned setbits(unsigned x, int p, int n, unsigned y) {
  int xLastBitsCnt = p + 1 - n;
  if (xLastBitsCnt < 0) {
    return 0;
  }
  // get last n bits of y
  unsigned yLastNBits = getbits(y, n - 1, n);
  // get last bits of x that go after a cut piece
  unsigned xLastBits = xLastBitsCnt ? getbits(x, xLastBitsCnt - 1, xLastBitsCnt) : 0;
  // left bits of gapMask are all 1, then goes a gap filled with 0 and then last bits of x
  unsigned gapMask = (~0 << (p + 1)) | xLastBits;
  /*
  1) x & gapMask gives us x with a gap filled with 0
  2) yLastNBits << xLastBitsCnt consists of all 0 with a gap filled with yLastNBits
  3) and finally x & gapMask | (yLastNBits << xLastBitsCnt) fills the gap in x with yLastNBits
  */
  return x & gapMask | (yLastNBits << xLastBitsCnt);
}
/*
Invert n bits of x starting from position p.
p is a position from right and the very right bit is at position 0
*/
unsigned invert(unsigned x, int p, int n) {
  int xLastBitsCnt = p + 1 - n;
  if (xLastBitsCnt < 0) {
    return 0;
  }
  unsigned invertedBits = ~getbits(x, p, n);
  return setbits(x, p, n, invertedBits);
}

int main(void) {
  printf("Result: %d\n", invert(26, 3, 3));

  return 0;
}
