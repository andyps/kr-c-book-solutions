#include <stdio.h>

int main(void) {
  int c, nl, ns, nt;

  nl = ns = nt = 0;
  
  while ((c = getchar()) != EOF) {
    if (c == '\n')
      ++nl;
    if (c == ' ')
      ++ns;
    if (c == '\t')
      ++nt;
  }
  
  printf("Lines: %d\n", nl);
  printf("Spaces: %d\n", ns);
  printf("Tabs: %d\n", nt);

  return 0;
}
