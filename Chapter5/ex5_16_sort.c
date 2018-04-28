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

void _qsort(void *lineptr[], int left, int right, int (*comp)(void *, void *, int), int caseins);
int numcmp(char *, char *, int caseins);
int _strcmp(char *, char *, int caseins);
int dircmp(char *, char *, int caseins);
int _strcasecmp(char *, char *);

int main(int argc, char *argv[]) {
  int nlines;
  int numeric = 0, caseins = 0, dirorder = 0;
  
  if (argc > 1) {
    ++argv;
    while (--argc > 0) {
      if (_strcmp(*argv, "-n", 0) == 0)
        numeric = 1;
      if (_strcmp(*argv, "-f", 0) == 0)
        caseins = 1;
      if (_strcmp(*argv, "-d", 0) == 0)
        dirorder = 1;
      ++argv;
    }
  }
  if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
    if (numeric) {
      _qsort((void **)lineptr, 0, nlines - 1, 
        (int (*)(void *, void *, int))numcmp, caseins);
    } else if (dirorder) {
      _qsort((void **)lineptr, 0, nlines - 1, 
        (int (*)(void *, void *, int))dircmp, caseins);
    } else {
      _qsort((void **)lineptr, 0, nlines - 1, 
        (int (*)(void *, void *, int))_strcmp, caseins);
    }

    writelines(lineptr, nlines);
    return 0;
  } else {
    printf("Input too big to sort\n");
    return 1;
  }
}

void _qsort(void *v[], int left, int right, int (*comp)(void *, void *, int), int caseins) {
  int i, last;
  void swap(void *v[], int i, int j);
  
  if (left >= right)
    return;
  swap(v, left, (left + right) / 2);
  
  last = left;
  for (i = left + 1; i <= right; i++)
    if ((*comp)(v[i], v[left], caseins) < 0)
      swap(v, ++last, i);
      
  swap(v, left, last);
  _qsort(v, left, last - 1, comp, caseins);
  _qsort(v, last + 1, right, comp, caseins);
}

int numcmp(char *s1, char *s2, int caseins) {
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

int dircmp(char *s, char *t, int caseins) {
  for (; *s == *t; s++, t++) {
    if (*s == '\0')
      return 0;
  }
  if (isalpha(*s)) {
    return isalpha(*t) ? _strcmp(s, t, caseins) : -1;
  }
  if (isdigit(*s)) {
    return isdigit(*t) ? (atof(s) - atof(t)) : (isalpha(*t) ? 1 : -1);
  }
  if (*s == ' ') {
    return isalpha(*t) || isdigit(*t) ? 1 : (*t == ' ' ? 0 : -1);
  }
  return (*s - *t);
}

int _strcmp(char *s, char *t, int caseins) {
  if (caseins) {
    return _strcasecmp(s, t);
  }
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
