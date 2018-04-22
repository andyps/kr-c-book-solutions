#include "stdio.h"


void escape(char s[], char t[]) {
  int i, j;
  
  for (i = 0, j = 0; t[i] != '\0'; i++, j++) {
    switch (t[i]) {
      case '\t':
        s[j] = '\\';
        s[++j] = 't';
        break;
      case '\n':
        s[j] = '\\';
        s[++j] = 'n';
        break;
      case '\r':
        s[j] = '\\';
        s[++j] = 'r';
        break;
      case '\v':
        s[j] = '\\';
        s[++j] = 'v';
        break;
      case '\f':
        s[j] = '\\';
        s[++j] = 'f';
        break;
      case '\a':
        s[j] = '\\';
        s[++j] = 'a';
        break;
      case '\b':
        s[j] = '\\';
        s[++j] = 'b';
        break;
      case '\e':
        s[j] = '\\';
        s[++j] = 'e';
        break;
      case '\?':
        s[j] = '\\';
        s[++j] = '?';
        break;
      case '\\':
        s[j] = '\\';
        s[++j] = '\\';
        break;
      case '\"':
        s[j] = '\\';
        s[++j] = '\"';
        break;
      case '\'':
        s[j] = '\\';
        s[++j] = '\'';
        break;
      default:
        s[j] = t[i];
        break;
    }
  }

  s[j] = '\0';
}

void unescape(char s[], char t[]) {
  int i, j, slash = 0;
  
  for (i = 0, j = 0; t[i] != '\0'; i++) {
    if (slash) {
      slash = 0;
      switch (t[i]) {
        case 't':
          s[j++] = '\t';
          break;
        case 'n':
          s[j++] = '\n';
          break;
        case 'r':
          s[j++] = '\r';
          break;
        case 'v':
          s[j++] = '\v';
          break;
        case 'f':
          s[j++] = '\f';
          break;
        case 'a':
          s[j++] = '\a';
          break;
        case 'b':
          s[j++] = '\b';
          break;
        case 'e':
          s[j++] = '\e';
          break;
        case '\?':
          s[j++] = '\?';
          break;
        case '\\':
          s[j++] = '\\';
          break;
        case '\"':
          s[j++] = '\"';
          break;
        case '\'':
          s[j++] = '\'';
          break;
        default:
          s[j++] = t[i];
          break;
      }
      continue;
    }
    if (t[i] == '\\') {
      slash = 1;
      continue;
    }
    s[j++] = t[i];
  }
  
  s[j] = '\0';
}

int main(void) {
  char source[] = "abc\t-\n-\b\"";
  char resultEscape[100];
  char resultUnescape[100];

  escape(resultEscape, source);
  printf("Source: %s\n***\nResult: %s\n***\n", source, resultEscape);
  
  unescape(resultUnescape, resultEscape);
  printf("Source: %s\n***\nResult: %s\n***\n", resultEscape, resultUnescape);
  return 0;
}
