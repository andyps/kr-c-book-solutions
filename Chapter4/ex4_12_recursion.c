#include "stdio.h"
#include "string.h"
#include "limits.h"

void reverse(char s[]) {
  int c, i, j;
  
  for (i = 0, j = strlen(s) - 1; i < j; i++, j--) {
    c = s[i];
    s[i] = s[j];
    s[j] = c;
  }
}

void itoaOriginal(int n, char s[]) {
  int i, sign;
  
  if ((sign = n) < 0)
    n = -n;
  
  i = 0;
  do {
    s[i++] = n % 10 + '0';
  } while ((n /= 10) > 0);
  
  if (sign < 0)
    s[i++] = '-';
    
  s[i] = '\0';
  
  reverse(s);
}


int i = 0;
/*
Recursive and supports INT_MIN
*/
void itoaRecursive(int n, char s[]) {
  char ch;
  int next;
  
  if (n < 0) {
    n = -n;
    s[i++] = '-';
  }
  
  next = n / 10;
  if (next < 0) {
    next = -next;
  }
  if (next) {
    itoaRecursive(next, s);
  }
  
  ch = n % 10;
  if (ch < 0) {
    ch = -ch;
  }
  s[i++] = ch + '0';
  s[i] = '\0';
}


int main(void) {
  int n = -125;
  char result1[100];
  char result2[100];
  
  printf("Number: %d\n", n);
  
  itoaOriginal(n, result1);
  printf("Result1: %s\n", result1);
  
  itoaRecursive(n, result2);
  printf("Result2: %s\n", result2);
  
  return 0;
}
