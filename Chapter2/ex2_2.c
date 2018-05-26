#include <stdio.h>
#include <limits.h>
#include <float.h>
#include <math.h>
#include <string.h>

#define SIZE 3

int _getline(char s[], int lim) {
    int c, i;
    /*
    for (i = 0; i < lim-1 && (c = getchar()) != '\n' && c != EOF; ++i)
        s[i] = c;
    */
    i = 0;
    while (i < lim-1) {
        c = getchar();
        if (c == '\n') {
            break;
        }
        if (c == EOF) {
            break;
        }
        s[i] = c;
        ++i;
    }
   
    if (c == '\n') {
        s[i] = c;
        ++i;
    }
    s[i] = '\0';
    return i;
}

int main() {
    char s[SIZE];
    char s2[3] = "123";
    int i;
    int lim = SIZE;

    int cnt = _getline(s, SIZE);
    
    printf("Output%d-%d-%d\n", strlen(s), cnt, strlen(s2));
    for (i = 0; i < cnt; ++i)
        printf("%d:%c-", i, s[i]);
    return 0;
}

