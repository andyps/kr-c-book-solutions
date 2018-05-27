#include <stdio.h>

#define IN 1
#define OUT 0
#define WORDLEN 10

int main(void) {
  int c, state, len;
  int vals[WORDLEN + 1];
  int idx, maxval;
  
  state = OUT;
  len = maxval = 0;
  
  for (idx = 0; idx < WORDLEN + 1; idx++) {
    vals[idx] = 0;
  }
  while ((c = getchar()) != EOF) {
    if (c == ' ' || c == '\n' || c == '\t') {
      if (state == IN) {
        idx = len > WORDLEN ? 0 : len;
        vals[idx]++;
        maxval = vals[idx] > maxval ? vals[idx] : maxval;
      }
      state = OUT; 
    } else {
      if (state == OUT) {
        state = IN;
        len = 0;
      }
      len++;
    }
  }

  while (maxval > 0) {
    for (idx = 0; idx < WORDLEN + 1; idx++) {
      if (vals[idx] >= maxval) {
        printf("  *");
      } else {
        printf("   ");
      }
    }
    putchar('\n');
    maxval--;
  }
  for (idx = 0; idx < WORDLEN + 1; idx++) {
    if (idx > 0) {
      printf(" %2d", idx);
    } else {
      printf(">%2d", WORDLEN);
    }
  }
  
  return 0;
}
