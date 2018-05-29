#include <stdio.h>

#define COLSIZE 10

int printfoldline(char[], int);

int main(void) {
  char line[COLSIZE + 2];
  int c, pos;
  int blankPos;
  
  line[0] = '\0';
  blankPos = -1;
  pos = 0;
  while ((c = getchar()) != EOF) {
    if (c == ' ' || c == '\t') {
      blankPos = pos;
    }
    if (c == '\n') {
      printf("%s", line);
      putchar('\n');
      pos = 0;
      blankPos = -1;
    } else if (pos + 1 < COLSIZE) {
      line[pos++] = c;
    } else {
      pos = printfoldline(line, blankPos);
      if (c != ' ' && c != '\t')
        line[pos++] = c;
      blankPos = -1;
    }
    line[pos] = '\0';
  }
  printf("%s", line);
  
  return 0;
}

int printfoldline(char line[], int blankPos) {
  int i, j;
  
  if (blankPos == -1) {
    for (i = 0; i < COLSIZE - 1; i++) {
      putchar(line[i]);
    }
    putchar('\n');
    return 0;
  }
  
  for (i = 0; i < blankPos; i++) {
    putchar(line[i]);
  }
  putchar('\n');
  
  j = 0;
  for (i = blankPos + 1; i < COLSIZE - 1; i++) {
    line[j++] = line[i];
  }
  line[j] = '\0';
  return j;
}
