#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXTOKEN 100
enum { NAME, PARENS, BRACKETS };

char token[MAXTOKEN];
int tokentype;
char out[1000];

int gettoken(void);

int getch(void);
void ungetch(int);

int main(void) {
  int type;
  char temp[MAXTOKEN];
  int prevtype = -1;
  
  while(gettoken() != EOF) {
    strcpy(out, token);
    while ((type = gettoken()) != '\n') {
      if (type == PARENS ||  type == BRACKETS) {
        if (prevtype == '*') {
          /* this is when parentheses are necessary */
          sprintf(temp, "(%s)", out);
          strcpy(out, temp);
        }
        strcat(out, token);
      } else if (type == '*') {
        sprintf(temp, "*%s", out);
        strcpy(out, temp);
      } else if (type == NAME) {
        sprintf(temp, "%s %s", token, out);
        strcpy(out, temp);
      } else
        printf("invalid input at %s\n", token);
        
      prevtype = type;
    }
    
    printf("%s\n", out);
  }

  return 0;
}

int gettoken(void) {
  int c, getch(void);
  void ungetch(int);
  char *p = token;
  
  while ((c = getch()) == ' ' || c == '\t')
    ;
  
  if (c == '(') {
    if ((c = getch()) == ')') {
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
