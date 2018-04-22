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

void itoa(int n, char s[]) {
  int i, sign;
  char ch;
  
  if ((sign = n) < 0) {
    // if n is still < 0 then it's the min value or n == INT_MIN
    n = -n;
  }

  i = 0;
  do {
    ch = n % 10;
    if (ch < 0) {
      ch = -ch;
    }

    s[i++] = ch + '0';
    
    n /= 10;
    if (n < 0) {
      n = -n;
    }
  } while (n > 0);
  
  if (sign < 0) {
    s[i++] = '-';
  }
  
  s[i] = '\0';
  
  reverse(s);
}

int main(void) {
  int n = INT_MIN;
  char result[100];
  
  itoa(n, result);
  
  printf("Number: %d\nResult: %s\n", n, result);
  return 0;
}
