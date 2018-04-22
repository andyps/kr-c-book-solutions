#include "stdio.h"

int htoi(char s[]) {
  int i, n, start;
  start = n = 0;

  if (s[0] == '0' && (s[1] == 'x' || s[1] == 'X')) {
    start = 2;
  }
  for (i = start; ; ++i) {
    char delta;
    if (s[i] >= '0' && s[i] <= '9') {
      delta = s[i] - '0';
    } else if (s[i] >= 'a' && s[i] <= 'f') {
      delta = s[i] - 'a' + 10;
    } else if(s[i] >= 'A' && s[i] <= 'F') {
      delta = s[i] - 'A' + 10;
    } else {
      break;
    }
    n = 16 * n + delta;
  }
  return n;
}

int main(void) {

  printf("test: %d\n", htoi("fff"));
  return 0;
}
