#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAXLINES 5000
#define MAXLEN 1000
#define ALLOCSIZE 10000
char *lineptr[MAXLINES];

char *alloc(int n);
void afree(char *p);
int _getline(char s[], int lim);
int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);

void _qsort(void *lineptr[], int left, int right, int (*comp)(void *, void *));
int numcmp(char *, char *);
int _strcmp(char *, char *);
int _strcasecmp(char *, char *);

int main(int argc, char *argv[]) {
  int nlines;
  int numeric = 0, caseins = 0;
  
  if (argc > 1) {
    ++argv;
    while (--argc > 0) {
      if (_strcmp(*argv, "-n") == 0)
        numeric = 1;
      if (_strcmp(*argv, "-f") == 0)
        caseins = 1;
      ++argv;
    }
  }

  if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
    _qsort((void **)lineptr, 0, nlines - 1, 
      (int (*)(void *, void *))(numeric ? numcmp : (caseins ? _strcasecmp : _strcmp)));
    writelines(lineptr, nlines);
    return 0;
  } else {
    printf("Input too big to sort\n");
    return 1;
  }
}

void _qsort(void *v[], int left, int right, int (*comp)(void *, void *)) {
  int i, last;
  void swap(void *v[], int i, int j);
  
  if (left >= right)
    return;
  swap(v, left, (left + right) / 2);
  
  last = left;
  for (i = left + 1; i <= right; i++)
    if ((*comp)(v[i], v[left]) < 0)
      swap(v, ++last, i);
      
  swap(v, left, last);
  _qsort(v, left, last - 1, comp);
  _qsort(v, last + 1, right, comp);
}

int numcmp(char *s1, char *s2) {
  double v1, v2;
  
  v1 = atof(s1);
  v2 = atof(s2);
  if (v1 < v2)
    return -1;
  else if (v1 > v2)
    return 1;
  else
    return 0;
}

int _strcmp(char *s, char *t) {
  for (; *s == *t; s++, t++) {
    if (*s == '\0')
      return 0;
  }
  return (*s - *t);
}

int _strcasecmp(char *s, char *t) {
  for (; *s == *t; s++, t++) {
    if (*s == '\0')
      return 0;
  }
  if (isalpha(*s) && isalpha(*t)) {
    return tolower(*s) - tolower(*t);
  }
  
  return (*s - *t);
}

void swap(void *v[], int i, int j) {
  void *temp;
  
  temp = v[i];
  v[i] = v[j];
  v[j] = temp;
}

void writelines(char *lineptr[], int nlines) {
  int i;
  
  for (i = 0; i < nlines; i++)
    printf("%s\n", lineptr[i]);
}

int readlines(char *lineptr[], int maxlines) {
  int len, nlines;
  char *p, line[MAXLEN];
  
  nlines = 0;
  while((len = _getline(line, MAXLEN)) > 0)
    if (nlines >= maxlines || (p = alloc(len)) == NULL)
      return -1;
    else {
      line[len - 1] = '\0';
      strcpy(p, line);
      lineptr[nlines++] = p;
    }

  return nlines;
}

int _getline(char s[], int lim) {
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
