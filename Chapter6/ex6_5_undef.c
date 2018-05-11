#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define HASHSIZE 101

struct nlist {
  struct nlist *next;
  char *name;
  char *defn;
};

static struct nlist *hashtab[HASHSIZE];

struct nlist *lookup(char *);
struct nlist *install(char *, char *);
unsigned hash(char *);
void undef(char *);

int main(void) {
  struct nlist *np;

  install("x1", "xOne");
  install("x1", "xOne1");
  install("y1", "yOne");
  install("x2", "xTwo");
  
  np = lookup("x1");
  printf("%s: %s\n", np->name, np->defn);
  np = lookup("y1");
  printf("%s: %s\n", np->name, np->defn);
 
  undef("y1");
  np = lookup("y1");
  if (np == NULL) {
    printf("it works!");
  }
  return 0;
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

struct nlist *getParent(struct nlist *np) {
  struct nlist *p;
  unsigned hashval;

  hashval = hash(np->name);
  p = hashtab[hashval];
  if (p == np) {
    return NULL;
  }
  
  do {
    if (p->next == np)
      return p;
    p = p->next;
  } while (p != NULL);

  return NULL;
}

void undef(char *s) {
  struct nlist *np, *p;
  unsigned hashval;

  np = lookup(s);
  if (np == NULL) {
    return;
  }

  hashval = hash(np->name);
  if (hashtab[hashval] == np) {
    hashtab[hashval] = np->next;
  } else if ((p = getParent(np)) != NULL) {
    p->next = np->next;
  }
  
  free((void *) np->defn);
  free((void *) np->name);
  np->next = NULL;
  free((void *) np);
}
