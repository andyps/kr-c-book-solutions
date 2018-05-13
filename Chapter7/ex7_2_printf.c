#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define LINELEN 80

int main(int argc, char *argv[]) {
  int c, n, r;
  char hexOct[] = "[%x]";
  
  if (argc > 1) {
    ++argv;
    while (--argc > 0) {
      if (strcmp(*argv, "-o") == 0)
        hexOct[2] = 'o';
      if (strcmp(*argv, "-x") == 0)
        hexOct[2] = isupper((*argv)[1]) ? 'X' : 'x';
      ++argv;
    }
  }
  
  n = r = 0;
  while ((c = getchar()) != EOF) {
    if (c == '\n') {
      n = 0;
      putchar(c);
      continue;
    }

    if (n >= LINELEN) {
      putchar('\n');
      n = 0;
    }
    if (!isprint(c)) {
      r = printf(hexOct, c);
      r = r > 0 ? r : 0;
    } else {
      r = putchar(c) != EOF ? 1 : 0;
    }
    n += r;
  }

  return 0;
}
