#include "stdio.h"
#include "time.h"

/*
Original version
*/
int binsearch(int x, int v[], int n) {
  int low, high, mid;
  
  low = 0;
  high = n - 1;
  while (low <= high) {
    mid = (low + high) / 2;
    if (x < v[mid]) {
      high = mid - 1;
    } else if (x > v[mid]) {
      low = mid + 1;  
    } else {
      return mid;
    }
  }
  return -1;
}
/*
The second version with one condition inside the loop
*/
int binsearch2(int x, int v[], int n) {
  int low, high, mid;

  low = 0;
  high = n - 1;
  while (low + 1 < high) {
    mid = (low + high) / 2;
    if (x < v[mid]) {
      high = mid - 1;
    } else {
      low = mid;  
    }
  }

  if (x == v[low]) {
    return low;
  }
  if (x == v[high]) {
    return high;
  }
  return -1;
}

int main(void) {
  clock_t time;
  int x = 5;
  int orderedArray[] = {
    1, 3, 5, 7, 8, 11, 12, 13, 144, 158,
    160, 163, 165, 167, 168, 171, 172, 173, 174, 358,
    359, 360, 365, 367, 368, 371, 372, 373, 374, 458,
    459, 460, 465, 467, 468, 471, 472, 473, 474, 558,
    559, 560, 565, 567, 568, 571, 572, 573, 574, 658
  };
  int orderedArraySize = 50;
        
  time = clock();
  int res1 = binsearch(x, orderedArray, orderedArraySize);
  time = clock() - time;
  
  printf("Version 1: %d\nTaken: %lu\n", res1, time);
  
  time = clock();
  int res2 = binsearch(x, orderedArray, orderedArraySize);
  time = clock() - time;
  
  printf("Version 2: %d\nTaken: %lu\n", res2, time);
  
  return 0;
}
