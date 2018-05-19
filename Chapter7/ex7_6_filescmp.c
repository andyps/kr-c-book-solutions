#include <stdio.h>
#include <string.h>

#define MAXLINE 100

int main(int argc, char *argv[]) {
  FILE *fp1, *fp2;
  char l1[MAXLINE], l2[MAXLINE];
  int diff = 0;
  int n = 0;
  char *res1, *res2;

  if (argc < 3) {
    fputs("not enough arguments, expected two\n", stderr);
    return 1;
  }
  
  if ((fp1 = fopen(argv[1], "r")) == NULL) {
    fprintf(stderr, "can't open file %s\n", argv[1]);
    return 2;
  }
  if ((fp2 = fopen(argv[2], "r")) == NULL) {
    fprintf(stderr, "can't open file %s\n", argv[2]);
    fclose(fp1);
    return 2;
  }
  
  res1 = fgets(l1, MAXLINE, fp1);
  res2 = fgets(l2, MAXLINE, fp2);
  while (res1 != NULL && res2 != NULL) {
    if (strcmp(l1, l2) != 0) {
      diff = 1;
      break;
    }
    n++;
    res1 = fgets(l1, MAXLINE, fp1);
    res2 = fgets(l2, MAXLINE, fp2);
  }
  
  if (diff) {
    printf("files are different on line %d\n", n + 1);
    printf("%s: %s\n", argv[1], l1);
    printf("%s: %s\n", argv[2], l2);
  } else if (res1 != NULL && res2 == NULL) {
    printf("file %s has more lines than the other one\n", argv[1]);
  } else if (res1 == NULL && res2 != NULL) {
    printf("file %s has more lines than the other one\n", argv[2]);
  } else {
    printf("all lines are equal\n");
  }

  fclose(fp1);
  fclose(fp2);
  return 0;
}
