#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>

#define MAXOP 100
#define NUMBER '0'
#define TYPE_NUM 1
#define TYPE_VAR 2

int getop(char s[]);
void push(double, char);
double pop(void);

double last(void);
void duplicate(void);
void swap(void);
void clearstack(void);
void printstack(void);

double vars[26];
char lastType(void);
char popType(void);
char popVar(void);
char lastVar(void);
void printvars(void);

/*
Added simple support for variables.
Variable names should consist of only one uppercase latin letter.
There's no check if variable is defined or not (by default all variables 
are defined and contain 0).
This is how to assign a value to a variable:
3 A =
*/
double lastOutput;
int main(void) {
  int type;
  double op2;
  char var;
  char s[MAXOP];
  char opType;
  
  lastOutput = 0;
  /*
  All variables are created and by default contain 0.
  */
  for (var = 0; var < 26; var++) {
    vars[var] = 0;
  }
  
  while ((type = getop(s)) != EOF) {
    switch (type) {
      case NUMBER:
        push(atof(s), TYPE_NUM);
        break;
      case '+':
        push(pop() + pop(), TYPE_NUM);
        break;
      case '*':
        push(pop() * pop(), TYPE_NUM);
        break;
      case '-':
        op2 = pop();
        push(pop() - op2, TYPE_NUM);
        break;
      case '%':
        op2 = pop();
        if (op2 != 0.0)
          push((int)pop() % (int)op2, TYPE_NUM);
        else
          printf("error: zero divisor\n");
        break;
      case '/':
        op2 = pop();
        if (op2 != 0.0)
          push(pop() / op2, TYPE_NUM);
        else
          printf("error: zero divisor\n");
        break;
      case '\n':
        // get the last element in the stack
        lastOutput = last();
        printf("\t%.8g\n", lastOutput);
        break;

      case 'd':
        duplicate();
        break;
      case 's':
        swap();
        break;
      case 'c':
        clearstack();
        break;
      case 'p':
        printstack();
        break;
        
      case '^':
        op2 = pop();
        push(pow(pop(), op2), TYPE_NUM);
        break;
      case '~':
        push(sin(pop()), TYPE_NUM);
        break;
      case 'e':
        push(exp(pop()), TYPE_NUM);
        break;
      case 'v':
        printvars();
        break;
      case '=':
        opType = lastType();
        var = popVar();
        if (opType == TYPE_VAR) {
          op2 = vars[var - 'A'] = pop();
          push(op2, TYPE_NUM);
        } else {
          printf(
            "error: value can be assigned only to a variable, variable name should go last\n"
            );
        }
        break;
      case '$':
        push(lastOutput, TYPE_NUM);
        break;
      default:
        if (isupper(type)) {
          // process variable names
          push(type, TYPE_VAR);
          break;
        }
        printf("error: unknown command %s\n", s);
        break;
    }
  }
  
  return 0;
}

#define MAXVAL 100

int sp = 0;
double val[MAXVAL][2];  // stack

void push(double f, char type) {
  int idx = sp;
  if (sp < MAXVAL) {
    val[idx][0] = f;
    val[idx][1] = type;
    ++sp;
  } else {
    printf("error: stack full, can't push %g\n", f);
  }
}

double getStackValue(int idx) {
  if (val[idx][1] == TYPE_VAR) {
    return vars[(char)val[idx][0] - 'A'];
  } else
    return val[idx][0];
}

double pop(void) {
  if (sp > 0) {
    return getStackValue(--sp);
  } else {
    printf("error: stack empty\n");
    return 0.0;
  }
}

char popVar(void) {
  if (sp > 0) {
    return (char)val[--sp][0];
  } else {
    printf("error: stack empty\n");
    return 0;
  }
}

char popType(void) {
  if (sp > 0)
    return val[--sp][1];
  else {
    printf("error: stack empty\n");
    return 0;
  }
}

/*
pop without deleting
*/
double last(void) {
  if (sp > 0)
    return getStackValue(sp - 1);
  else {
    printf("stack empty\n");
    return 0.0;
  }
}

char lastVar(void) {
  if (sp > 0)
    return (char)val[sp - 1][0];
  else {
    printf("stack empty\n");
    return 0;
  }
}

char lastType(void) {
  if (sp > 0)
    return val[sp - 1][1];
  else {
    printf("stack empty\n");
    return 0;
  }
}


/*
Duplicate the last element
*/
void duplicate(void) {
  if (sp > 0) {
    push(val[sp - 1][0], val[sp - 1][1]);
  } else {
    printf("error: stack empty\n");
  }
}
/*
Swap two last elements
*/
void swap(void) {
  double lastValue, lastbutoneValue;
  char lastType, lastbutoneType;

  if (sp > 1) {
    --sp;
    lastValue = val[sp][0];
    lastType = (char)val[sp][1];
    --sp;
    lastbutoneValue = val[sp][0];
    lastbutoneType = (char)val[sp][1];

    push(lastValue, lastType);
    push(lastbutoneValue, lastbutoneType);
  } else
    printf("error: less than two elements are in stack\n");
}

void clearstack(void) {
  sp = 0;
}

void printvars(void) {
  char var;
  
  printf("***Print variables***\n");
  for (var = 0; var < 26; var++) {
    printf(
      "Name: %c; Value: %.8g%c",
      var + 'A',
      vars[var],
      (var < 25) ? ',' : '\n'
    );
  }
  printf("***\n");
}

void printstack(void) {
  int i;
  
  printf("***Print stack***\n");
  for (i = 0; i < sp; i++) {
    if (val[i][1] == TYPE_NUM) {
      printf(
        "Type: %s; Value: %.8g%c",
        "Literal",
        val[i][0], 
        (i < sp - 1) ? ',' : '\n'
      );
    } else if(val[i][1] == TYPE_VAR) {
      printf(
        "Type: %s; Name: %c; Value: %.8g%c",
        "Variable",
        (char)val[i][0],
        getStackValue(i),
        (i < sp - 1) ? ',' : '\n'
      );
    }
  }
  printf("***\n");
}

int getch(void);
void ungetch(int);

int getop(char s[]) {
  int i, c;
  int assignment;
  
  while ((s[0] = c = getch()) == ' ' || c == '\t')
    ;
  s[1] = '\0';

  if (isupper(c)) {
    // process variable names
    return c;
  }
  
  i = 0;
  
  // check for a negative number
  if (c == '-') {
    c = getch();
    if (!isdigit(c) && c != '.') {
      if (c != EOF)
        ungetch(c);
      return '-';
    } else {
      i = 1;
      s[1] = c;
      s[2] = '\0';
    }
  } else if (!isdigit(c) && c != '.') {
      return c;
  }
  
  if (isdigit(c))
    while (isdigit(s[++i] = c = getch()))
      ;
      
  if (c == '.')
    while (isdigit(s[++i] = c = getch()))
      ;
      
  s[i] = '\0';
  if (c != EOF)
    ungetch(c);
  
  return NUMBER;
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
