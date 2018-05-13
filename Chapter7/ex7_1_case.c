#include <stdio.h>
#include <string.h>
#include <ctype.h>


void convert(int toUpper) {
  int c;
  
  while ((c = getchar()) != EOF) {
    if (toUpper)
      putchar(toupper(c));
    else
      putchar(tolower(c));
  }
}

int main(int argc, char *argv[]) {
  char *name;
  int i;
  
  for (i = strlen(argv[0]) - 1; i >= 0; i--) {
    if (argv[0][i] == '\\' || argv[0][i] == '/') {
      break;
    }
  }
  
  name = &argv[0][i + 1];
  
  printf("name: %s\n", name);
  
  if (islower(*name)) {
    /* to lower */
    convert(0);
  } else {
    /* to upper */
    convert(1);
  }
  
  printf("%s", name);
  return 0;
}
