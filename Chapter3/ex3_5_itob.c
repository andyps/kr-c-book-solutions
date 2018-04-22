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

void itob(int n, char s[], int b) {
  int i, sign;
  char ch;
  
  if (b > 16 || b < 2) {
    s[0] = '\0';
    return;
  }
  
  if ((sign = n) < 0) {
    // if n is still < 0 then it's the min value or n == INT_MIN
    n = -n;
  }

  i = 0;
  do {
    ch = n % b;
    if (ch < 0) {
      ch = -ch;
    }
    if (ch < 10) {
      ch += '0';
    } else {
      ch = ch - 10 + 'a';
    }
    
    s[i++] = ch;
    
    n /= b;
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
  int base = 16;
  int n = INT_MIN;
  char result[100];
  
  itob(n, result, base);
  
  printf("Number: %d\nBase: %d\nResult: %s\n", n, base, result);
  return 0;
}
