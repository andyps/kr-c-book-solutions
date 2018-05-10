#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define MAXWORD 100
#define MAXNODES 100

struct tnode {
  char *word;
  int count;
  struct tnode *left;
  struct tnode *right;
};

struct tnode *addtree(struct tnode *, char *);
void treeprint(struct tnode *);
struct tnode *talloc(void);
char *__strdup(char *);

int getch(void);
void ungetch(int);
int getword(char *, int);

void swap(struct tnode *nodes[], int i, int j);
void _qsort(struct tnode *nodes[], int left, int right);

struct tnode *nodeptr[MAXNODES];
int nodesNum = 0;
void collectTreeToArray(struct tnode *);

int main(void) {
  struct tnode *root;
  char word[MAXWORD];
  int i;

  root = NULL;
  while (getword(word, MAXWORD) != EOF)
    if (isalpha(word[0]))
      root = addtree(root, word);

  collectTreeToArray(root);
  _qsort(nodeptr, 0, nodesNum - 1);
  
  for (i = 0; i < nodesNum; i++)
    printf("%4d %s\n", nodeptr[i]->count, nodeptr[i]->word);

  return 0;
}

void collectTreeToArray(struct tnode *p) {
  if (p != NULL) {
    collectTreeToArray(p->left);
    *(nodeptr + nodesNum) = p;
    nodesNum++;
    collectTreeToArray(p->right);
  }
}

struct tnode *addtree(struct tnode *p, char *w) {
  int cond;

  if (p == NULL) {
    p = talloc();
    p->word = __strdup(w);
    p->count = 1;
    p->left = p->right = NULL;
  } else if ((cond = strcmp(w, p->word)) == 0) {
    p->count++;
  } else if (cond < 0) {
    p->left = addtree(p->left, w);
  } else {
    p->right = addtree(p->right, w);
  }
  return p;
}

void _qsort(struct tnode *nodes[], int left, int right) {
  int i, last;
  
  if (left >= right)
    return;
  swap(nodes, left, (left + right) / 2);
  
  last = left;
  for (i = left + 1; i <= right; i++)
    if ((nodes[i]->count - nodes[left]->count) > 0)
      swap(nodes, ++last, i);
      
  swap(nodes, left, last);
  _qsort(nodes, left, last - 1);
  _qsort(nodes, last + 1, right);
}

void swap(struct tnode *nodes[], int i, int j) {
  struct tnode *temp;
  temp = nodes[i];
  nodes[i] = nodes[j];
  nodes[j] = temp;
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

int getword(char *word, int lim)
{
  int c;
  char *w = word;
  
  c = skipSpaces();

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
