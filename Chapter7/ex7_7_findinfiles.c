#include <stdio.h>
#include <string.h>

#define MAXLINE 1000

struct searchParams {
  int except;
  int number;
  int printName;
};

int searchInFileByPattern(char *pattern, FILE *fp, struct searchParams params, char *name) {
  char line[MAXLINE];
  int found = 0;
  int lineno = 0;
  
  if (params.printName) {
    printf("File %s\n", name);
  }

  while (fgets(line, MAXLINE, fp) != NULL) {
    lineno++;
    if ((strstr(line, pattern) != NULL) != params.except) {
      if (params.number)
        printf("%d:", lineno);
      printf("%s", line);
      found++;
    }
  }
  
  return found;
}

int main(int argc, char *argv[]) {
  struct searchParams params = {0, 0, 0};
  int c;
  long found = 0;
  char *pattern;
  
  FILE *fp;
  
  while (--argc > 0 && (*++argv)[0] == '-') {
    while (c = *++argv[0]) {
      switch (c) {
        case 'x':
          params.except = 1;
          break;
        case 'n':
          params.number = 1;
          break;
        default:
          printf("find: illegal option %c\n", c);
          argc = 0;
          found = -1;
          break;
      }
    }
  }
  
  if (argc < 1) {
    printf("Usage: find -x -n pattern optionalFile1 optionalFile2 ... optionalFileN ...\n");
    return -1;
  }

  pattern = *argv;
  
  if (argc == 1) {
    params.printName = 0;
    found += searchInFileByPattern(pattern, stdin, params, "");
  } else {
    params.printName = 1;
    while (--argc > 0) {
      if ((fp = fopen(*++argv, "r")) == NULL) {
        printf("find: can't open file %s\n", *argv);
        return -1;
      }
      found += searchInFileByPattern(pattern, fp, params, *argv);
      fclose(fp);
    }
  }

  return found;
}
