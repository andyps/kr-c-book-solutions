#include <stdio.h>

int main(void) {
  int c, r;

  while (r = ((c = getchar()) != EOF)) {
    printf("%d", r);
  }
  printf("\nAt the end should be 0 - %d\n", r);

  return 0;
}
