#include <stdio.h>

#define IN 1
#define OUT 0

int main(void) {
  int c;
  int nums[10];
  int uppervals[26];
  int lowervals[26];
  
  int idx;
  
  for (idx = 0; idx < 10; idx++) {
    nums[idx] = 0;
  }
  for (idx = 0; idx < 26; idx++) {
    uppervals[idx] = 0;
    lowervals[idx] = 0;
  }
  
  while ((c = getchar()) != EOF) {
    if (c >= '0' && c <= '9') {
      nums[c - '0']++;
    }
    if (c >= 'A' && c <= 'Z') {
      uppervals[c - 'A']++;
    }
    if (c >= 'a' && c <= 'z') {
      lowervals[c - 'a']++;
    }
  }

  for (idx = 0; idx < 10; idx++) {
    printf("%c:", idx + '0');
    while (--nums[idx] >= 0) {
      putchar('*');
    }
    putchar('\n');
  }
  for (idx = 0; idx < 26; idx++) {
    printf("%c:", idx + 'A');
    while (--uppervals[idx] >= 0) {
      putchar('*');
    }
    putchar('\n');
  }
  for (idx = 0; idx < 26; idx++) {
    printf("%c:", idx + 'a');
    while (--lowervals[idx] >= 0) {
      putchar('*');
    }
    putchar('\n');
  }

  return 0;
}
