#include "stdio.h"

/*
Remove symbol from string
*/
void squeeze(char s[], int c) {
  int i, j;

  for (i = j = 0; s[i] != '\0'; i++)
    if (s[i] != c)
      s[j++] = s[i];
  s[j] = '\0';
}

/*
Remove symbols contained in s2 from string s (version 1)
*/
void squeezeStr(char s[], char s2[]) {
  int i;

  for (i = 0; s2[i] != '\0'; i++)
    squeeze(s, s2[i]);
}

/*
Remove symbols contained in s2 from string s (version 2)
*/
void squeezeStr2(char s[], char s2[]) {
  int i, j, k;
  int found;
  
  for (i = k = 0; s[i] != '\0'; i++) {
    found = 0;
    for (j = 0; s2[j] != '\0'; j++) {
      if (s[i] == s2[j]) {
        found = 1;
        break;
      }
    }
    if (!found) {
      s[k++] = s[i];
    }
  }

  s[k] = '\0';
}

int main(void) {
  char s[] = "1abcd2abcd3abcd";
  char s2[] = "1abcd2abcd3abcd";
  char s3[] = "1abcd2abcd3abcd";
  
  squeeze(s, 'd');
  printf("%s\n", s);
  
  squeezeStr(s2, "dbd");
  printf("%s\n", s2);

  squeezeStr2(s3, "bdb52");
  printf("%s\n", s3);

  return 0;
}
