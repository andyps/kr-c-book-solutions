#include <stdio.h>

void strcatOriginal(char s[], char t[])
{
  int i, j;
  
  i = j = 0;
  
  while (s[i] != '\0') 
    i++;
    
  while ((s[i++] = t[j++]) != '\0')
    ;
}
void strcatPointers(char *s, char *t)
{
  while (*s)
    s++;
    
  while (*s++ = *t++)
    ;
}
int main(void) {
  char s1[] = "string";
  char s2[] = "string";
  char t[] = "tail";
  
  strcatOriginal(s1, t);
  printf("Result1: %s\n", s1);
  
  strcatPointers(s2, t);
  printf("Result2: %s\n", s2);

  return 0;
}
