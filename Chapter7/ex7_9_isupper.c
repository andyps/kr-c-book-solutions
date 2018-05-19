/*
We can use tables to look for uppercase symbols
or we can use some calculations to save space
*/
#include <stdio.h>
#include <ctype.h>

/* bit masks */
#define DIGIT 1
#define UPPER 2
#define LOWER 4

char TABLE[] = {
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, // numbers 0 - 9
  0, 0, 0, 0, 0, 0, 0,
  2, 2, 2, 2, 2, //from A
  2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
  2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
  2, // to Z
  0, 0, 0, 0, 0, 0,
  4, 4, 4 // from a to c and so on
};

/* works for ASCII and that is why it's simple */
int isupper1(unsigned c) {
  return c <= 'Z' && c >= 'A';
}

int islower1(unsigned c) {
  return c <= 'z' && c >= 'a';
}

int isdigit1(unsigned c) {
  return c <= '9' && c >= '0';
}

/* uses a lookup table */
int isupper2(unsigned c) {
  return TABLE[c] & UPPER;
}

int islower2(unsigned c) {
  return TABLE[c] & LOWER;
}

int isdigit2(unsigned c) {
  return TABLE[c] & DIGIT;
}

int main(void) {
  printf("isdigit1 %d:%d:%d\n", isdigit1('0') != 0, isdigit1('9') != 0, isdigit1('A') != 0);
  printf("isdigit2 %d:%d:%d\n", isdigit2('0') != 0, isdigit2('9') != 0, isdigit2('A') != 0);
  
  printf("isupper1 %d:%d\n", isupper1('B') != 0, isupper1('b') != 0);
  printf("isupper2 %d:%d\n", isupper2('B') != 0, isupper2('b') != 0);
  printf("islower1 %d:%d\n", islower1('B') != 0, islower1('b') != 0);
  printf("islower2 %d:%d\n", islower2('B') != 0, islower2('b') != 0);
  
  return 0;
}
