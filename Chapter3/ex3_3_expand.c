#include "stdio.h"
#include "ctype.h"

int isSupportedPattern(char patternStart, char patternEnd) {
  return patternEnd > patternStart && (
    isdigit(patternStart) && isdigit(patternEnd) ||
    islower(patternStart) && islower(patternEnd) ||
    isupper(patternStart) && isupper(patternEnd)
  );
}

int replacePattern(char s[], int idx, char patternStart, char patternEnd) {
  char ch;
  int addedCnt = 0;

  if (!isSupportedPattern(patternStart, patternEnd)) {
    s[idx] = patternEnd;
    return 1;
  }
  
  s[idx - 1] = patternStart + 1;
  
  for (ch = patternStart + 2; ch <= patternEnd; ch++, idx++, addedCnt++) {
    s[idx] = ch;
  }
  return addedCnt;
}

/*
Expand patterns like a-z, A-Z, 0-9 from s1
and copy the result to s2
*/
void expand(char s1[], char s2[]) {
  int i, j, addedCnt;
  
  for (i = 0, j = 0; s1[i] != '\0'; i++) {
    if (i > 1 && s2[j - 1] == '-') {
      addedCnt = replacePattern(s2, j, s2[j - 2], s1[i]);
      j += addedCnt;
      continue;
    }

    s2[j++] = s1[i];
  }

  s2[j] = '\0';
}

int main(void) {
  char s1[] = "-a1-3bc-f3-7-9-Z-A-B-FA-b";
  char result[100];

  expand(s1, result);

  printf("String: %s\nResult: %s\n", s1, result);
  return 0;
}
