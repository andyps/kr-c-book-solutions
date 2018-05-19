#include <stdio.h>

#define PAGE_LEN 5
#define MAXLINE 100

void printfile(char *name, FILE *fp, int *page) {
  int ln = 0;
  char l[MAXLINE];
  
  (*page)++;
  if (*page > 1) {
    printf("\f");
  }
  printf("***(Page %d)\n===%s===\n\n", *page, name);
  ln += 2;
  
  while (fgets(l, MAXLINE, fp) != NULL) {
    ln++;
    if (ln > PAGE_LEN) {
      ln = 1;
      (*page)++;
      printf("\f***(Page %d)\n", *page);
    }
    fputs(l, stdout);
  }
}

int main(int argc, char *argv[]) {
  FILE *fp;
  int page = 0;

  if (argc == 1) {
    fputs("please, specify at least one file name\n", stderr);
    return 1;
  }
  while (--argc > 0) {
    if ((fp = fopen(*++argv, "r")) == NULL) {
      fprintf(stderr, "can't open file %s", *argv);
      return 1;
    }
    printfile(*argv, fp, &page);

    fclose(fp);
  }
  return 0;
}
