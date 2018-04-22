#include "stdio.h"
#include "string.h"

void reverseOriginal(char s[]) {
  int c, i, j;
  
  for (i = 0, j = strlen(s) - 1; i < j; i++, j--) {
    c = s[i];
    s[i] = s[j];
    s[j] = c;
  }
}

void reverseRecursive(char s[], int left, int right) {
  int c;

  if (left >= right) {
    return;
  }
  
  c = s[left];
  s[left] = s[right];
  s[right] = c;
  
  reverseRecursive(s, left + 1, right - 1);
}


int main(void) {
  char result1[] = "123456789";
  char result2[] = "123456789";
  
  printf("\nReverse:\n");
  reverseOriginal(result1);
  reverseRecursive(result2, 0, strlen(result2) - 1);
  
  printf("Result1: %s\n", result1);
  printf("Result2: %s\n", result2);

  return 0;
}
