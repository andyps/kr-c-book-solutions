/*
Simple syntax checker
*/
#include <stdio.h>

int main() {
  int c, prev, startQuote;
  int inComment, inQuotes, inSomething;
  int braces, brackets, parens;

  prev = '\0';
  inComment = inQuotes = 0;
  braces = brackets = parens = 0;
  while ((c = getchar()) != EOF) {
    inSomething = inComment || inQuotes;

    if (c == '*' && prev == '/' && !inSomething) {
      inComment = 1;
    } else if (inComment && c == '/' && prev == '*') {
      inComment = 0;
    } else if ((c == '\'' || c == '"') && !inSomething) {
      inQuotes = 1;
      startQuote = c;
    } else if (inQuotes && c == startQuote && prev != '\\') {
      inQuotes = 0;
    } else if (!inSomething) {
      if (c == '{') {
        braces++;
      }
      if (c == '[') {
        brackets++;
      }
      if (c == '(') {
        parens++;
      }
      if (c == '}') {
        braces--;
      }
      if (c == ']') {
        brackets--;
      }
      if (c == ')') {
        parens--;
      }
    }

    prev = c;
  }

  if (inComment) {
    printf("Comment block is not closed\n");
  }
  if (inQuotes) {
    printf("Quotes are not closed\n");
  }

  if (braces != 0) {
    printf("Braces do not match\n");
  }
  if (brackets != 0) {
    printf("Brackets do not match\n");
  }
  if (parens != 0) {
    printf("Parentheses do not match\n");
  }
    
  if (!inComment && !inQuotes && braces == 0 && brackets == 0 && 
    parens == 0
  ) {
    printf("Valid\n");
  }

  return 0;
}
