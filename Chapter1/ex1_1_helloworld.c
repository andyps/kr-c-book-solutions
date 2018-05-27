#include <stdio.h>

int main(void) {
  printf("hello, ");
  /* \ is for escaping symbols, can be used to specify long strings */
  printf("worl\
d");
  /*
  printf('world'); - error, use "
  printf("world); - error, missing "
  printf("world") - error, missing ;
  printf("world"; - error, missing )
  */
  printf("\n"); 

  return 0;
}
