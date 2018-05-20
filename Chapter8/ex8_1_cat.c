#include <stdio.h>
#include <stdlib.h>
#include "fcntl.h"
#include "unistd.h"

void filecopy(int ifp, int ofp) {
  char c;

  while (read(ifp, &c, 1) == 1) {
    write(ofp, &c, 1);
  }
}

int main(int argc, char *argv[]) {
  int fp;
  char *prog = argv[0];
  char msg[100];
  
  if (argc == 1) {
    filecopy(0, 1);
  } else {
    while (--argc > 0) {
      if ((fp = open(*++argv, O_RDONLY, 0)) == -1) {
        sprintf(msg, "%s: can't open %s\n", prog, *argv);
        write(2, msg, strlen(msg));
        exit(1);
      } else {
        filecopy(fp, 1);
        close(fp);
      }
    }
  }

  return 0;
}
