#include <stdio.h>
#include <stdarg.h>
#include <ctype.h>
#include <string.h>

void minprintf(char *, ...);

int main(void) {
  minprintf("3.2 %s %d = %e%%\n", "plus", 2, 5.2);
  minprintf("5 + 3.22 = '%8.2f'", 8.22);

  return 0;
}

char *parseNumPart(char *p) {
  static char numpart[11];
  int i = 0;

  while (isdigit(*++p) && i < 10) {
    numpart[i++] = *p;
  }
  if (*p == '.' && i < 10) {
    numpart[i++] = *p;
    while (isdigit(*++p) && i < 10) {
      numpart[i++] = *p;
    }
  }
  numpart[i] = '\0';
  return numpart;
}

void minprintf(char *fmt, ...) {
  va_list ap;
  
  char *p, *sval;
  int ival;
  double dval;
  void *pt;
  char *numpart;
  char resfmt[20];

  va_start(ap, fmt);

  for (p = fmt; *p; p++) {
    if (*p != '%') {
      putchar(*p);
      continue;
    }

    numpart = parseNumPart(p);
    
    ++p;
    if (*p == '%') {
      putchar('%');
      continue;
    }
    if (*p == '\0') {
      break;
    }
    
    if (*numpart != '\0')
      sprintf(resfmt, "%%%s", numpart);
    else
      strcpy(resfmt, "%");

    p += strlen(numpart);

    switch (*p) {
      case 'd':
      case 'i':
        ival = va_arg(ap, int);
        strcat(resfmt, "d");
        printf(resfmt, ival);
        break;
      case 'u':
        ival = va_arg(ap, int);
        strcat(resfmt, "u");
        printf(resfmt, ival);
        break;
      case 'c':
        ival = va_arg(ap, int);
        strcat(resfmt, "c");
        printf(resfmt, ival);
        break;
      case 'o':
        ival = va_arg(ap, int);
        strcat(resfmt, "o");
        printf(resfmt, ival);
        break;
      case 'x':
        ival = va_arg(ap, int);
        strcat(resfmt, "x");
        printf(resfmt, ival);
        break;
      case 'X':
        ival = va_arg(ap, int);
        strcat(resfmt, "X");
        printf(resfmt, ival);
        break;
      case 'f':
        dval = va_arg(ap, double);
        strcat(resfmt, "f");
        printf(resfmt, dval);
        break;
      case 'g':
        dval = va_arg(ap, double);
        strcat(resfmt, "g");
        printf(resfmt, dval);
        break;
      case 'G':
        dval = va_arg(ap, double);
        strcat(resfmt, "G");
        printf(resfmt, dval);
        break;
      case 'e':
        dval = va_arg(ap, double);
        strcat(resfmt, "e");
        printf(resfmt, dval);
        break;
      case 'E':
        dval = va_arg(ap, double);
        strcat(resfmt, "E");
        printf(resfmt, dval);
        break;
      case 'p':
        pt = va_arg(ap, void *);
        strcat(resfmt, "p");
        printf(resfmt, pt);
        break;
      case '%':
        putchar('%');
        break;
      case 's':
        for (sval = va_arg(ap, char *); *sval; sval++)
          putchar(*sval);
        break;
      default:
        putchar(*p);
        break;
    }
  }
  
  va_end(ap);

}
