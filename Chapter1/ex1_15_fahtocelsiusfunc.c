#include <stdio.h>

float fahToCelsius(float);

int main(void) {
  float fahr; 
  int lower, upper, step;
  
  lower = 0;
  upper = 300;
  step = 20;
  
  printf("From Fahrenheit to Celsius\n");
  fahr = lower;
  while (fahr <= upper) {
    printf("%3.0f %6.1f\n", fahr, fahToCelsius(fahr)); 
    fahr = fahr + step; 
  }

  return 0;
}

float fahToCelsius(float fahr) {
  return (5.0 / 9.0) * (fahr - 32.0);
}
