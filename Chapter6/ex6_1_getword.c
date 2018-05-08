/*
Skips comments, directives and string constants
(doesn't take into account escapings)
*/
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAXWORD 100

struct key {
  char *word;
  int count;
} keytab[] = {
  "auto", 0,
  "break", 0,
  "case", 0,
  "char", 0,
  "const", 0,
  "continue", 0,
  "default", 0,
  /* ... */
  "unsigned", 0,
  "void", 0,
  "volatile", 0,
  "while", 0
};

#define NKEYS (sizeof keytab / sizeof keytab[0])

int getch(void);
void ungetch(int);
int getword(char *, int);
int binsearch(char *, struct key *, int);

int main(void) {
  int n;
  char word[MAXWORD];
  
  while (getword(word, MAXWORD) != EOF)
    if (isalpha(word[0]) || word[0] == '_')
      if ((n = binsearch(word, keytab, NKEYS)) >= 0)
        keytab[n].count++;
        
  for (n = 0; n < NKEYS; n++)
    if (keytab[n].count > 0)
      printf("%4d %s\n", keytab[n].count, keytab[n].word);

  return 0;
}

int binsearch(char *word, struct key tab[], int n) {
  int cond;
  int low, high, mid;
  
  low = 0;
  high = n - 1;
  while (low <= high) {
    mid = (low + high) / 2;
    if ((cond = strcmp(word, tab[mid].word)) < 0)
      high = mid - 1;
    else if (cond > 0)
      low = mid + 1;
    else
      return mid;
  }
  return -1;
}

int checkIfCommentStart(int c) {
  if (c != '/') {
    return 0;
  }
  c = getch();
  if (c != '*') {
    ungetch(c);
    return 0;
  }
  return 1;
}

int skipComment(void) {
  int c;
  int prev = '\0';

  while ((c = getch()) != EOF) {
    if (prev == '*' && c == '/') {
      break;
    }
    prev = c;
  }
  return c;
}

int skipSpaces(void) {
  int c;

  while (isspace(c = getch()))
    ;
  return c;
}

int skipString(void) {
  int c;

  while ((c = getch()) != '"' && c != EOF)
    ;
  return c;
}

int skipDirectives(void) {
  int c;

  while ((c = getch()) != '\n' && c != EOF)
    ;
  return c;
}

int skipCommentsSpacesStringsDirectives(void) {
  int c;

  while (1) {
    c = skipSpaces();

    if (checkIfCommentStart(c)) {
      c = skipComment();
    } else if (c == '"') {
      c = skipString();
    } else if (c == '#') {
      c = skipDirectives();
    } else
      break;

    if (c == EOF)
      break;
  }
  
  return c;
}

int getword(char *word, int lim)
{
  int c;
  char *w = word;
  
  c = skipCommentsSpacesStringsDirectives();

  if (c != EOF)
    *w++ = c;
  if (!isalpha(c) && c != '_') {
    *w = '\0';
    return c;
  }
  for ( ; --lim > 0; w++)
    if (!isalnum(*w = getch()) && *w != '_') {
      ungetch(*w);
      break;
    }
    
  *w = '\0';
  return word[0];
}

#define BUFSIZE 100

int buf[BUFSIZE];
int bufp = 0;

int getch(void) {
  return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) {
  if (bufp >= BUFSIZE)
    printf("ungetch: too many characters\n");
  else
    buf[bufp++] = c;
}
