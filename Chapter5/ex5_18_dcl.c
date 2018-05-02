/* TODO: to be completed soon */
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXTOKEN 100
enum { NAME, PARENS, BRACKETS };

char token[MAXTOKEN];
char name[MAXTOKEN];
char datatype[MAXTOKEN];
int tokentype;
char out[1000];

void dcl(void);
void dirdcl(void);
int gettoken(void);

int getch(void);
void ungetch(int);

int eatInputSpaces(void);

int main(void) {
  while (gettoken() != EOF) {
    strcpy(datatype, token);
    out[0] = '\0';
    dcl();
    if (tokentype != '\n')
      printf("syntax error\n");
    else
      /* output only if there're no errors */
      printf("%s: %s %s\n", name, out, datatype);
  }

  return 0;
}

void dcl(void) {
  int ns;
  for (ns = 0; gettoken() == '*'; )
    ns++;
  dirdcl();
  while (ns-- > 0)
    strcat(out, " pointer to");
}
void dirdcl(void) {
  int type;
  if (tokentype == '(') {
    dcl();
    if (tokentype != ')')
      printf("error: missing )\n");
  } else if (tokentype == NAME) {
    strcpy(name, token);
  } else
    printf("error: expected name or (dcl)\n");
  
  while ((type = gettoken()) == PARENS || type == BRACKETS) {
    if (type == PARENS) {
      strcat(out, " function returning");
    } else {
      strcat(out, " array");
      strcat(out, token);
      strcat(out, " of");
    }
  }
}

int eatInputSpaces(void) {
  int c;
  
  while ((c = getch()) == ' ' || c == '\t')
    ;
  return c;
}

int gettoken(void) {
  int c, getch(void);
  void ungetch(int);
  char *p = token;
  
  c = eatInputSpaces();

  if (c == '(') {
    /* do not fail if there're spaces */
    c = eatInputSpaces();
    if (c == ')') {
      strcpy(token, "()");
      return tokentype = PARENS;
    } else {
      ungetch(c);
      return tokentype = '(';
    }
  } else if (c == '[') {
    for (*p++ = c; (*p++ = getch()) != ']'; )
      ;
    *p = '\0';
    return tokentype = BRACKETS;
  } else if (isalpha(c)) {
    for (*p++ = c; isalnum(c = getch()); )
      *p++ = c;
    *p = '\0';
    ungetch(c);
    return tokentype = NAME;
  } else
    return tokentype = c;
}

#define BUFSIZE 100

char buf[BUFSIZE];
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
