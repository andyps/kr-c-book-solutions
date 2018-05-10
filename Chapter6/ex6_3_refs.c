#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define MAXWORD 100
#define MAXLINES 1000
#define MINWORDLEN 3

struct tnode {
  char *word;
  int count;
  int lines[MAXLINES];
  int lastLine;
  struct tnode *left;
  struct tnode *right;
};

char ignoreList[][MAXWORD] = {"and", "the"};
#define IGNORESNUM 3

struct tnode *addtree(struct tnode *, char *, int);
void treeprint(struct tnode *);
struct tnode *talloc(void);
char *__strdup(char *);

int getch(void);
void ungetch(int);
int getword(char *, int);
int binsearch(char *, char [][MAXWORD], int);

int main(void) {
  struct tnode *root;
  char word[MAXWORD];
  int c;
  int lineNum;

  root = NULL;
  lineNum = 1;
  while ((c = getword(word, MAXWORD)) != EOF) {
    if (c == '\n') {
      lineNum++;
    } else if (isalpha(word[0])) {
      if (strlen(word) < MINWORDLEN) {
        continue;
      }
      if (binsearch(word, ignoreList, IGNORESNUM) < 0)
        root = addtree(root, word, lineNum);
    }
  }
  
  treeprint(root);
  return 0;
}

int binsearch(char *word, char list[][MAXWORD], int n) {
  int cond;
  int low, high, mid;
  
  low = 0;
  high = n - 1;
  while (low <= high) {
    mid = (low + high) / 2;
    if ((cond = strcmp(word, list[mid])) < 0)
      high = mid - 1;
    else if (cond > 0)
      low = mid + 1;
    else
      return mid;
  }
  return -1;
}

struct tnode *addtree(struct tnode *p, char *w, int line) {
  int cond;
  
  if (p == NULL) {
    p = talloc();
    p->word = __strdup(w);
    p->lastLine = line;
    p->count = 1;
    p->lines[0] = line;
    p->left = p->right = NULL;
  } else if ((cond = strcmp(w, p->word)) == 0) {
    if (p->lastLine != line && p->count < MAXLINES) {
      p->lines[p->count] = line;
      p->count++;
      p->lastLine = line;
    }
  } else if (cond < 0) {
    p->left = addtree(p->left, w, line);
  } else {
    p->right = addtree(p->right, w, line);
  }
  return p;
}

void treeprint(struct tnode *p) {
  int i;

  if (p != NULL) {
    treeprint(p->left);
    printf("%s: ", p->word);
    for (i = 0; i < p->count; i++) {
      printf("%d", p->lines[i]);
      if (i < p->count - 1) {
        printf(",");
      }
    }
    printf("\n");
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

int skipSpacesExceptEndLine(void) {
  int c;

  while (isspace(c = getch()) && c != '\n')
    ;
  return c;
}

int getword(char *word, int lim)
{
  int c;
  char *w = word;
  
  c = skipSpacesExceptEndLine();

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
