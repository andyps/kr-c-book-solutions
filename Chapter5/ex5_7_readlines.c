#include "stdio.h"
#include "string.h"

#define MAXLINES 5000
#define MAXLEN 1000
#define ALLOCSIZE 10000

/*
Values for Solution 2:

#define MAXLINES 50
#define MAXLEN 100
*/

char *lineptr[MAXLINES];

int readlinesOriginal(char *lineptr[], int nlines);
int readlines1(char *lineptr[], char *buf, int nlines, int bufsize); /* for Solution 1*/
int readlines2(char *lineptr[], int nlines);  /* for Solution 2*/
void writelines(char *lineptr[], int nlines);
void qsort(char *lineptr[], int left, int right);

int main(void) {
  int nlines;
  
  /* Solution 1 */
  char buf[ALLOCSIZE];
  
  if ((nlines = readlines1(lineptr, buf, MAXLINES, ALLOCSIZE)) >= 0) {
    qsort(lineptr, 0, nlines - 1);
    writelines(lineptr, nlines);
    return 0;
  } else {
    printf("error: input too big to sort\n");
    return 1;
  }
  
  /* 
    Solution 2
    This solution uses mutlidimensional array, but the exercise goes before the paragraph about multidimensional arrays.
    Also in this solution you have to reduce MAXLINES and MAXLEN to prevent memory overflow.
  */
  /*
  char lines[MAXLINES][MAXLEN];
  int i;
  for (i = 0; i < MAXLINES; i++) {
      lineptr[i] = lines[i];
  }
  
  if ((nlines = readlines2(lineptr, MAXLINES)) >= 0) {
    qsort(lineptr, 0, nlines - 1);
    writelines(lineptr, nlines);
    return 0;
  } else {
    printf("error: input too big to sort\n");
    return 1;
  }
  */
}

int _getline(char *, int);
char *alloc(int);

int readlinesOriginal(char *lineptr[], int maxlines) {
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
/* For Solution 1 */
int readlines1(char *lineptr[], char *buf, int maxlines, int bufsize) {
  int len, nlines;
  char *p, line[MAXLEN];
  
  p = buf;
  nlines = 0;
  while((len = _getline(line, MAXLEN)) > 0)
    if (nlines >= maxlines || buf + bufsize - p < len)
      return -1;
    else {
      line[len - 1] = '\0';
      strcpy(p, line);
      lineptr[nlines++] = p;
      p += len;
    }

  return nlines;
}
/* For Solution 2 */
int readlines2(char *lineptr[], int maxlines) {
  int len, nlines;
  char line[MAXLEN];
  
  nlines = 0;
  while((len = _getline(line, MAXLEN)) > 0)
    if (nlines >= maxlines)
      return -1;
    else {
      line[len - 1] = '\0';
      strcpy(lineptr[nlines++], line);
    }

  return nlines;
}

void writelines(char *lineptr[], int nlines) {
  int i;
  
  for (i = 0; i < nlines; i++)
    printf("%s\n", lineptr[i]);
}

void swap(char *v[], int i, int j) {
  char *temp;
  
  temp = v[i];
  v[i] = v[j];
  v[j] = temp;
}

void qsort(char *v[], int left, int right) {
  int i, last;
  
  if (left >= right)
    return;
  swap(v, left, (left + right) / 2);
  
  last = left;
  for (i = left + 1; i <= right; i++)
    if (strcmp(v[i], v[left]) < 0)
      swap(v, ++last, i);
      
  swap(v, left, last);
  qsort(v, left, last - 1);
  qsort(v, last + 1, right);
}

int _getline(char s[], int lim) {
  int c, i;
  
  i = 0;
  while (--lim > 0 && (c = getchar()) != EOF && c != '\n')
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
