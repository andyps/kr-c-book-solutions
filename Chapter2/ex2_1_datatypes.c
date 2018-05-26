#include <stdio.h>
#include <limits.h>
#include <float.h>
#include <math.h>

int main() {
    char xChar = 5;
    int xInt = 5;
    short xSInt = 5;
    long xLInt = 5;
    long long int xLLInt = 5;

    unsigned char xUChar = 5;
    unsigned int xUInt = 5;
    unsigned short xUSInt = 5;
    unsigned long xULInt = 5;
    unsigned long long xULLInt = 5;
    
    float xFloat = 5.0;
    double xDouble = 5.0;
    long double xLDouble = 5.0;

    printf("char: %ld=%dbits\n", sizeof(xChar), CHAR_BIT);
    printf("int: %ld\n", sizeof(xInt));
    
    printf("short int: %ld\n", sizeof(xSInt));
    printf("long int: %ld\n", sizeof(xLInt)); 
    printf("long long int: %ld\n", sizeof(xLLInt)); 
    
    printf("********\n");

    printf("unsigned char: %ld\n", sizeof(xUChar));
    printf("unsigned int: %ld\n", sizeof(xUInt));
    printf("unsigned short int: %ld\n", sizeof(xUSInt));
    printf("unsigned long int: %ld\n", sizeof(xULInt));    
    printf("unsigned long long int: %ld\n", sizeof(xULLInt));    

    printf("********\n");
    printf("float: %ld=%ld\n", sizeof(xFloat), sizeof(float));
    printf("double: %ld\n", sizeof(xDouble));
    printf("long double: %ld\n", sizeof(xLDouble));
    
    printf("********\n");
    printf("char min: %d\n", CHAR_MIN);
    printf("char max: %d\n", CHAR_MAX);
    printf("unsigned char max: %d\n", UCHAR_MAX);
    
    printf("********\n");
    printf("int min: %d\n", INT_MIN);
    printf("int max: %d\n", INT_MAX);
    printf("unsigned int max: %u\n", UINT_MAX);
    
    printf("********\n");
    printf("short int min: %d\n", SHRT_MIN);
    printf("short int max: %d\n", SHRT_MAX);
    printf("unsigned short int max: %u\n", USHRT_MAX);

    printf("********\n");
    printf("long int min: %ld\n", LONG_MIN);
    printf("long int max: %ld\n", LONG_MAX);
    printf("unsigned long int max: %lu\n", ULONG_MAX);

    printf("********\n");
    printf("long long int min: %lld\n", LLONG_MIN);
    printf("long long int max: %lld\n", LLONG_MAX);
    printf("unsigned long long int max: %llu\n", ULLONG_MAX);
    
    printf("********\n");
    printf("********\n");
    printf("********\n");
    
    printf("unsigned char max: %u\n", xUChar = ~0);
    printf("unsigned int max: %u\n", xUInt = ~0);
    printf("unsigned short int max: %u\n", xUSInt = ~0);
    printf("unsigned long int max: %lu\n", xULInt = ~0);
    printf("unsigned long long int max: %llu\n", xULLInt = ~0);
    
    unsigned char charBits = ~0;
    printf("char min: %d\n", ~(charBits / 2));
    printf("char max: %d\n", charBits / 2);
    
    unsigned short shortBits = ~0;
    printf("short int min: %d\n", ~(shortBits / 2));
    printf("short int max: %d\n", shortBits / 2);    
    
    unsigned long longBits = ~0;
    printf("long int min: %ld\n", ~(longBits / 2));
    printf("long int max: %ld\n", longBits / 2);    
    
    unsigned long long longLongBits = ~0;
    printf("long long int min: %lld\n", ~(longLongBits / 2));
    printf("long long int max: %lld\n", longLongBits / 2);
    
    unsigned short intBits = ~0;
    printf("int min: %d\n", ~(intBits / 2));
    printf("int max: %d\n", intBits / 2);    
    
    printf("********FLOATS********\n");
    printf("********\n");
    printf("float min 10 exp: %d\n", FLT_MIN_10_EXP);
    printf("float max 10 exp: %d\n", FLT_MAX_10_EXP);
    printf("double min 10 exp: %d\n", DBL_MIN_10_EXP);
    printf("double max 10 exp: %d\n", DBL_MAX_10_EXP);
    printf("long double 10 min exp: %d\n", LDBL_MIN_10_EXP);
    printf("long double 10 max exp: %d\n", LDBL_MAX_10_EXP);
    
    printf("********\n");
    
    printf("********float\n");
    printf("float min: %.100e\n", (float)pow(2, -126));
    printf("float min: %.100e\n", FLT_MIN);
    
    printf("float max: %.100e\n", (float) (pow(2, 127) * (2 - pow(2, -23))));
    printf("float max: %.100e\n", FLT_MAX);
    
    printf("********double\n");
    printf("double min: %.1000e\n", (double)pow(2, -1022));
    printf("double min: %.1000e\n", DBL_MIN);
    
    printf("double max: %.500e\n", (double)(pow(2, 1023) * (2 - pow(2, -52))));
    printf("double max: %.500e\n", DBL_MAX);
    
    printf("********long double\n");
    printf("long double min: %.1000Le...\n", (long double)powl(2, -16382));
    printf("long double min: %.1000Le...\n", LDBL_MIN);
    
    // powl(2, 16383) * (2 - powl(2, -112))) = (powl(2, 16383) - powl(2, 16270)) * 2
    printf("long double max: %.1000Le...\n", (long double) 2 * (powl(2, 16383) - powl(2, 16270))); // 1.1897 × 10^4932
    printf("long double max: %.1000Le...\n", (long double)LDBL_MAX);
    

    return 0;
}
