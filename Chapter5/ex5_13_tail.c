#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXLEN 100
#define MAXLINES 100
#define ALLOCSIZE 10000
#define DEFN 10

int readline(char s[], int lim);
char *alloc(int n);
void afree(char *p);

void tail(unsigned char nlines) {
  int len;
  char *r[MAXLINES], line[MAXLEN];
  int i, n, j;
  int moreThanNLines = 0;
  
  if (nlines > MAXLINES) {
      printf("error: max allowable number of lines is %d\n", MAXLINES);
      return;
  }
  /* initialize pointers */
  for (i = 0; i < nlines; i++) {
      if ((r[i] = alloc(MAXLEN)) == NULL) {
        printf("error: input too big to process everything");
        return;
      }
  }
  
  /* read */
  i = 0;
  while ((len = readline(line, MAXLEN)) > 0) {
    if (i == nlines) {
        moreThanNLines = 1;
    }
    i %= nlines;
    line[len - 1] = '\0';
    strcpy(r[i], line);
    i++;
  }
  
  /* write */
  n = 0;
  i--;
  for (j = i; j >= 0; j--) {
      printf("Line #%d: %s\n", n++, r[j]);
  }

  if (moreThanNLines) {
      j = nlines;
      while (--j > i) {
          printf("Line #%d: %s\n", n++, r[j]);
      }
  }
}

int main(int argc, char *argv[]) {
  int n;
  
  n = -1;

  ++argv;
  while (--argc > 0 && *argv[0] == '-') {
      n = -atoi(*argv);
      ++argv;
  }
  
  n = n <= 0 ? DEFN : n;

  tail(n);
   
  return 0;
}

int readline(char s[], int lim) {
  int c, i;

  i = 0;
  while (--lim > 0  && (c = getchar()) != EOF && c != '\n')
    s[i++] = c;
    
  if (c == '\n')
    s[i++] = c;

  s[i] = '\0';
  return i;
}

static char allocbuf[ALLOCSIZE];
static char *allocp = allocbuf;

char *alloc(int n) {
  if (allocbuf + ALLOCSIZE - allocp >= n) {
    allocp += n;
    return allocp - n;
  } else {
    return 0;
  }
}

void afree(char *p) {
  if (p >= allocbuf && p < allocbuf + ALLOCSIZE)
    allocp = p;
}
