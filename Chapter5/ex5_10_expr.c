#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define NUMBER '0'
#define UNKNOWN 'U'
#define MAXVAL 100

int getop(char *input);
void push(double);
double pop(void);

int main(int argc, char *argv[]) {
    int type;
    double op2;
    char *input;
    
    while (--argc > 0) {
        input = *++argv;
        type = getop(input);
        switch (type) {
            case NUMBER:
                push(atof(input));
                break;
            case '+':
                push(pop() + pop());
                break;
            case '*':
                push(pop() * pop());
                break;
            case '-':
                op2 = pop();
                push(pop() - op2);
                break;
            case '/':
                op2 = pop();
                if (op2 != 0.0)
                    push(pop() / op2);
                else
                    printf("error: zero divisor\n");
                break;
            default:
                printf("error: unknown command %s\n", input);
                break;
        }
    }
  
    printf("\t%.8g\n", pop());
    
    return 0;
}

int getop(char *input) {
    int c;

    c = *input;
    if (*(input + 1) != '\0' && !isdigit(c) && c != '.') {
        /* more than one symbol that are not digits or . */
        return UNKNOWN;
    }
    if (!isdigit(c) && c != '.') {
        /* one non-digit symbol */
        return c;
    }

    if (isdigit(c))
        while (isdigit(c = *++input))
            ;

    if (c == '.')
        while (isdigit(c = *++input))
            ;

    if (c != '\0') {
        /* some symbols after digits and . */
        return UNKNOWN;
    }
    /* a number */
    return NUMBER;
}

int sp = 0;
double val[MAXVAL];

void push(double f) {
  if (sp < MAXVAL)
    val[sp++] = f;
  else
    printf("error: stack full, can't push %g\n", f);
}

double pop(void) {
  if (sp > 0)
    return val[--sp];
  else {
    printf("error: stack empty\n");
    return 0.0;
  }
}
