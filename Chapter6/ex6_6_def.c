/*TODO: to be done soon*/
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define HASHSIZE 101
#define MAXWORD 100

struct nlist {
  struct nlist *next;
  char *name;
  char *defn;
};

static struct nlist *hashtab[HASHSIZE];

struct nlist *lookup(char *);
struct nlist *install(char *, char *);
unsigned hash(char *);

int getch(void);
void ungetch(int);
int getword(char *, int);

void processString(void);
void processDirective(void);
int processDirectiveName(char *);
int processDirectiveDef(char *);
int skipSpacesExceptEndLine(void);
void skipLine(int);

int main(void) {
  struct nlist *np;
  char word[MAXWORD];
  int c;

  while ((c = getword(word, MAXWORD)) != EOF) {
    if (c == '#') {
      processDirective();
      continue;
    }
    if (c == '"') {
      processString();
      continue;
    }

    np = NULL;
    if (isalpha(word[0])) {
      np = lookup(word);
    }
    if (np != NULL) {
      printf("%s", np->defn);
    } else {
      printf("%s", word);
    }
  }

  return 0;
}

void skipLine(int c) {
  if (c == '\n' || c == EOF) {
    ungetch(c);
    return;
  }
  while ((c = getch()) != '\n' && c != EOF)
    ;
  ungetch(c);
}

int skipSpacesExceptEndLine(void) {
  int c;

  while (isspace(c = getch()) && c != '\n')
    ;
  ungetch(c);
  return c;
}

int processDirectiveName(char *name) {
  int c;

  if ((c = getch()) != ' ') {
    skipLine(c);
    return 0;
  }
  c = skipSpacesExceptEndLine();
  if (c == '\n' || c == EOF)
    return 0;
  
  c = getword(name, MAXWORD);
  if (!isalpha(c)) {
    skipLine(c);
    return 0;
  }
  return 1;
}

int processDirectiveDef(char *defn) {
  int c;
  char *dp = defn;

  if ((c = getch()) != ' ') {
    skipLine(c);
    return 0;
  }
  
  c = skipSpacesExceptEndLine();
  if (c == '\n' || c == EOF)
    return 0;
  
  while ((c = getch()) != '\n' && c != EOF && !isspace(c)) {
    *dp++ = c;
  }
  *dp = '\0';

  skipLine(c);

  return strlen(defn);
}

void processDirective(void) {
  char word[MAXWORD];
  char defn[MAXWORD];
  int c;
  
  c = getword(word, MAXWORD);
  if (!isalpha(c) || strcmp(word, "define") != 0) {
    skipLine(c);
    return;
  }
  
  if ((c = processDirectiveName(word)) == 0) {
    return;
  }

  if (processDirectiveDef(defn) != 0) {
    /* add definition */
    install(word, defn);
  }
}

void processString(void) {
  int c;

  printf("\"");

  while ((c = getch()) != '"' && c != EOF)
    printf("%c", c);
  
  if (c == '"') {
    printf("\"");
  } else
    ungetch(c);
}

unsigned hash(char *s) {
  unsigned hashval;
  
  for (hashval = 0; *s != '\0'; s++)
    hashval = *s + 31 * hashval;

  return hashval % HASHSIZE;
}

struct nlist *lookup(char *s) {
  struct nlist *np;

  for (np = hashtab[hash(s)]; np != NULL; np = np->next)
    if (strcmp(s, np->name) == 0)
      return np;
  return NULL;
}

struct nlist *install(char *name, char *defn) {
  struct nlist *np;
  unsigned hashval;

  if ((np = lookup(name)) == NULL) {
    np = (struct nlist *) malloc(sizeof(*np));
    if (np == NULL || (np->name = strdup(name)) == NULL)
      return NULL;
    hashval = hash(name);
    np->next = hashtab[hashval];
    hashtab[hashval] = np;
  } else
    free((void *) np->defn);

  if ((np->defn = strdup(defn)) == NULL)
    return NULL;

  return np;
}

int checkIfCommentStart(int);
int skipComment(void);

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
  if (c != EOF)
    c = getch();
  return c;
}

int getword(char *word, int lim) {
  int c;
  char *w = word;
  
  c = getch();

  if (checkIfCommentStart(c)) {
    c = skipComment();
  }
    
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
