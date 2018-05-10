#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define MAXWORD 100
#define NUM_TO_COMPARE 6

struct tnode {
  char *word;
  int count;
  struct tnode *left;
  struct tnode *right;
};

struct tnode *addtree(struct tnode *, char *, int n);
void treeprint(struct tnode *);
struct tnode *talloc(void);
char *__strdup(char *);

int getch(void);
void ungetch(int);
int getword(char *, int);

int main(int argc, char *argv[]) {
  struct tnode *root;
  char word[MAXWORD];
  int numToCompare = 0;
  
  if (argc >= 2) {
    numToCompare = atoi(argv[1]);
  }
  numToCompare = numToCompare > 0 ? numToCompare : NUM_TO_COMPARE;
  if (numToCompare >= MAXWORD) {
    numToCompare = MAXWORD;
  }

  root = NULL;
  while (getword(word, MAXWORD) != EOF)
    if (isalpha(word[0]))
      root = addtree(root, word, numToCompare);
  
  treeprint(root);
  return 0;
}

struct tnode *addtree(struct tnode *p, char *w, int n) {
  int cond;
  
  w[n] = '\0';
  if (p == NULL) {
    p = talloc();
    p->word = __strdup(w);
    p->count = 1;
    p->left = p->right = NULL;
  } else if ((cond = strcmp(w, p->word)) == 0) {
    p->count++;
  } else if (cond < 0) {
    p->left = addtree(p->left, w, n);
  } else {
    p->right = addtree(p->right, w, n);
  }
  return p;
}

void treeprint(struct tnode *p) {
  if (p != NULL) {
    treeprint(p->left);
    printf("%4d %s\n", p->count, p->word);
    treeprint(p->right);
  }
}

struct tnode *talloc(void) {
  return (struct tnode *)malloc(sizeof(struct tnode));
}

char *__strdup(char *s) {
  char *p;
  
  p = (char *)malloc(strlen(s) + 1);
  if (p != NULL)
    strcpy(p, s);
  return p;
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

int skipCommentsSpacesStrings(void) {
  int c;

  while (1) {
    c = skipSpaces();

    if (checkIfCommentStart(c)) {
      c = skipComment();
    } else if (c == '"') {
      c = skipString();
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
  
  c = skipCommentsSpacesStrings();

  if (c != EOF)
    *w++ = c;
  if (!isalpha(c)) {
    *w = '\0';
    return c;
  }
  for ( ; --lim > 0; w++)
    if (!isalnum(*w = getch())) {
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
