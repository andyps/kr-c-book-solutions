#include "stdio.h"
#include "ctype.h"
#include "math.h"

#define MAXLINE 100

int readline(char s[], int lim) {
  int c, i;
  
  i = 0;
  while (--lim > 0  && (c = getchar()) != EOF && c != '\n')
    s[i++] = c;
    
  if (c == '\n')
    s[i++] = c;

  s[i] = '\0';
  return i;
}

double atof2(char s[]) {
  double val, power, exp;
  int i, sign, expsign;
  
  for (i = 0; isspace(s[i]); i++)
    ;
  
  sign = (s[i] == '-') ? -1 : 1;
  if (s[i] =='+' || s[i] == '-')
    i++;
  
  for (val = 0.0; isdigit(s[i]); i++)
    val = 10.0 * val + (s[i] - '0');
    
  if (s[i] == '.')
    i++;
    
  for (power = 1.0; isdigit(s[i]); i++) {
    val = 10.0 * val + (s[i] - '0');
    power *= 10;
  }

  /* process exponent part */
  exp = 0;
  if (s[i] == 'e' || s[i] == 'E') {
    i++;
    expsign = (s[i] == '-') ? -1 : 1;
    if (s[i] =='+' || s[i] == '-')
      i++;

    while (isdigit(s[i])) {
      exp = 10.0 * exp + (s[i] - '0');
      i++;
    }
    exp *= expsign;
  }

  return (sign * val / power) * pow(10, exp);
}

int main(void) {
  double sum;
  char line[MAXLINE];
  
  sum = 0;
  while (readline(line, MAXLINE) > 0)
    printf("\t%g\n", sum += atof2(line));
  
  return 0;
}
