/*
1) Accepts only one modifier, that should be either static or const
and should go before datatype
2) Allows function arguments but doesn't validate them
*/
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXTOKEN 100
enum { NAME, PARENS, BRACKETS, INCOMPLETE_BRACKETS, MODIFIER };

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
void eatTillTheEndOfLine(void);

/* this stores the current line number starting from 1 */
int line, isError;
char err[50];

char modifier[MAXTOKEN];

int main(void) {
  line = 0;
  while (gettoken() != EOF) {
    err[0] = '\0';
    out[0] = '\0';
    name[0] = '\0';
    modifier[0] = '\0';
    isError = 0;
    line++;

    if (tokentype == MODIFIER) {
      strcpy(modifier, token);
      gettoken();
    }

    if (tokentype != NAME) {
      strcpy(err, "invalid data type");
      isError = 1;
    }
    
    if (!isError) {
      strcpy(datatype, token);
      dcl();
    }

    if (!isError) {
      if (tokentype != '\n' && tokentype != EOF) {
        strcpy(err, "syntax error");
        isError = 1;
      } else {
        /* output only if there're no errors */
        printf("%s %s: %s %s\n", modifier, name, out, datatype);
      }
    }
    
    if (isError) {
      /* skip the line with an error */
      printf("error on line %d: %s\n", line, err);
      if (tokentype != '\n' && tokentype != EOF)
        eatTillTheEndOfLine();
    }
    
    if (tokentype == EOF)
      break;
  }

  return 0;
}

void dcl(void) {
  int ns;
  
  if (isError)
    return;

  for (ns = 0; gettoken() == '*'; )
    ns++;
  dirdcl();
  while (ns-- > 0)
    strcat(out, " pointer to");
}
void dirdcl(void) {
  int type;
  int c;
  char *p = token;

  if (isError)
    return;

  if (tokentype == '(') {
    dcl();
    
    if (isError)
      return;

    if (tokentype != ')') {
      strcpy(err, "missing )");
      isError = 1;
      return;
    }
  } else if (tokentype == NAME) {
    strcpy(name, token);
  } else if (tokentype == INCOMPLETE_BRACKETS) {
    strcpy(err, "incomplete brackets");
    isError = 1;
    return;
  } else {
    strcpy(err, "expected name or (dcl)");
    isError = 1;
    return;
  }
  
  while ((type = gettoken()) == PARENS || type == BRACKETS || type == '(') {
    if (type == PARENS) {
      strcat(out, " function returning");
    } else if (type == '(') {

      for ( ; (c = getch()) != ')' && c != '\n' && c != EOF; )
        *p++ = c;
        
      if (c == ')') {
        *p = '\0';
        strcat(out, " function (");
        strcat(out, token);
        strcat(out, ") returning");
      } else {
        ungetch(c);
        strcpy(err, "incomplete parens");
        isError = 1;
        break;
      }
    } else {
      strcat(out, " array");
      strcat(out, token);
      strcat(out, " of");
    }
  }

  if (tokentype == INCOMPLETE_BRACKETS) {
    strcpy(err, "incomplete brackets");
    isError = 1;
    return;
  }
}

void eatTillTheEndOfLine(void) {
  int c;
  
  while ((c = getch()) != '\n' && c != EOF)
    ;

  if (c == EOF) {
    ungetch(c);
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
    for (*p++ = c; (c = getch()) != ']' && c != '\n' && c != EOF; )
      *p++ = c;
    
    if (c == '\n' || c == EOF) {
      ungetch(c);
      return tokentype = INCOMPLETE_BRACKETS;
    }
    
    *p++ = ']';
    *p = '\0';
    return tokentype = BRACKETS;
  } else if (isalpha(c)) {
    for (*p++ = c; isalnum(c = getch()); )
      *p++ = c;
    *p = '\0';
    ungetch(c);

    if (!strcmp(token, "const") || !strcmp(token, "static")) {
      return tokentype = MODIFIER;
    }
    return tokentype = NAME;
  } else
    return tokentype = c;
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
