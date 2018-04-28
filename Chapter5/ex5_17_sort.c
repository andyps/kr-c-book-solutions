#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAXLINES 5000
#define MAXLEN 1000
#define ALLOCSIZE 10000
#define OPTSCOUNT 2
#define DELIM ','
char *lineptr[MAXLINES];

char *alloc(int n);
void afree(char *p);
int _getline(char s[], int lim);
int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);

void _qsort(void *lineptr[], int left, int right, int (*comp)(void *, void *, int[][3]), int[][3]);
int numcmp(char *, char *, int caseins);
int _strcmp(char *, char *, int caseins);
int dircmp(char *, char *, int caseins);
int _strcasecmp(char *, char *);
int cmpbyfields(char *, char *, int[][3]);

int main(int argc, char *argv[]) {
  int nlines;
  /* 
  OPTSCOUNT fields and 3 options for each field in such an order:
  [isNumeric, dirOrder, caseInsensitive]
  */
  int opts[OPTSCOUNT][3];
  int i, j;
  
  ++argv;
  --argc;
  for (i = 0; i < OPTSCOUNT; i++) {
    for (j = 0; j < 3; j++) {
      opts[i][j] = 0;
    }
    if (argc > 0) {
      if (**argv == '-') {
        if (strstr(*argv, "n") != NULL)
          opts[i][0] = 1;
        if (strstr(*argv, "d") != NULL)
          opts[i][1] = 1;
        if (strstr(*argv, "f") != NULL)
          opts[i][2] = 1;
      }
      --argc;
      ++argv;
    }
  }
    
  if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
    _qsort(
      (void **)lineptr, 0, nlines - 1, 
      (int (*)(void *, void *, int[][3]))cmpbyfields,
      opts
    );

    writelines(lineptr, nlines);
    return 0;
  } else {
    printf("Input too big to sort\n");
    return 1;
  }
}

void _qsort(void *v[], int left, int right, int (*comp)(void *, void *, int[][3]), int opts[][3]) {
  int i, last;
  void swap(void *v[], int i, int j);
  
  if (left >= right)
    return;
  swap(v, left, (left + right) / 2);
  
  last = left;
  for (i = left + 1; i <= right; i++)
    if ((*comp)(v[i], v[left], opts) < 0)
      swap(v, ++last, i);
      
  swap(v, left, last);
  _qsort(v, left, last - 1, comp, opts);
  _qsort(v, last + 1, right, comp, opts);
}

int copyUntilDelim(char *from, char *to) {
  int i = 0;
  
  for (; *from != DELIM && *from != '\0'; to++, from++) {
    *to = *from;
    i++;
  }
  *to = '\0';
  
  return i;
}

int cmpbyfields(char *s, char *t, int opts[OPTSCOUNT][3]) {
  int i, cmpRes;
  int caseins;
  char field1[MAXLEN], field2[MAXLEN];
  int fieldLen1, fieldLen2;
  
  for (i = 0; i < OPTSCOUNT; i++) {
    caseins = opts[i][2];
    
    fieldLen1 = copyUntilDelim(s, field1);
    fieldLen2 = copyUntilDelim(t, field2);

    /* compare substring */
    if (opts[i][0]) {
      cmpRes = numcmp(field1, field2, 0);
    } else if (opts[i][1]) {
      cmpRes = dircmp(field1, field2, caseins);
    } else {
      cmpRes = _strcmp(field1, field2, caseins);
    }
    if (cmpRes != 0) {
      return cmpRes;
    }
    
    /* jump to the next field */
    s += fieldLen1;
    t += fieldLen2;
    if (*s == DELIM) {
      s++;
    }
    if (*t == DELIM) {
      t++;
    }
    if (*s == '\0' && *t == '\0') {
      /* quit earlier */
      break;
    }
  }

  return 0;
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
