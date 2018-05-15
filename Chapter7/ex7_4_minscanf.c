#include <stdio.h>
#include <stdarg.h>

void minscanf(char *fmt, ...) {
  va_list ap;
  char *p, *sval;
  int *ival;
  unsigned int *uval;
  float *fval;
  
  va_start(ap, fmt);
  
  for (p = fmt; *p; p++) {
    if (*p != '%') {
      continue;
    }
    switch (*++p) {
      case 'd':
        ival = va_arg(ap, int *);
        scanf("%d", ival);
        break;
      case 'f':
        fval = va_arg(ap, float *);
        scanf("%f", fval);
        break;
      case 'x':
        uval = va_arg(ap, unsigned int *);
        scanf("%x", uval);
        break;
      case 'o':
        uval = va_arg(ap, unsigned int *);
        scanf("%o", uval);
        break;
      case 'i':
        ival = va_arg(ap, int *);
        scanf("%i", ival);
        break;
      case 's':
        sval = va_arg(ap, char *);
        scanf("%s", sval);
        break;
    }
  }
  
  va_end(ap);
}

int main(void) {
  int i = 0;
  float j = 0.;
  char s[100] = "\0";
  
  minscanf("%x%f%s", &i, &j, &s);
  
  printf("%d-%f-%s\n", i, j, s);
  
  return 0;
}
