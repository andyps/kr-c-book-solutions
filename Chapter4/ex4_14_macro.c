#include "stdio.h"

#define swap(t, x, y) {\
t temp;\
temp = x;\
x = y;\
y = temp;\
}

int main(void) {
  int x, y;
  
  x = 3; y = 5;
  
  
  printf("Before: x = %d; y = %d\n", x, y);
  
  swap(int, x, y);
  
  printf("After: x = %d; y = %d\n", x, y);
  
  return 0;
}
