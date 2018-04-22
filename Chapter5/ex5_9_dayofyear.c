#include <stdio.h>

int day_of_year(int year, int month, int day);
int month_day(int year, int yearday, int *pmonth, int *pday);

int main(void) {
  int month, day;
  
  printf("day_of_year1: %d\n", day_of_year(2018, 4, 19));
  
  month_day(2018, 109, &month, &day);
  printf("month_day1: %d-%d\n", month, day);
  
  printf("day_of_year2: %d\n", day_of_year(2018, 1, 119));
  
  month_day(2018, 367, &month, &day);
  printf("month_day2: %d-%d\n", month, day);
  
  return 0;
}

static char daytab[2][13] =  {
    {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
};


int day_of_year(int year, int month, int day) {
  int i, leap;
  char *pyear;
  
  if (month > 12 || month < 1) {
    printf("error: wrong month number %d\n", month);
    return -1;
  }
  
  leap = year % 4 == 0 && year % 100 != 0 || year % 400 == 0;
  pyear = *(daytab + leap);

  if (day <= 0) {
    printf("error: wrong day number %d\n", day);
    return -1;
  }
  if (day > *(pyear + month)) {
    printf(
      "error: month %d in year %d contains %d days, but "
      "you specified day number %d\n",
      month, year, *(pyear + month), day
    );
    return -1;
  }
  
  for (i = 1; i < month; i++)
    day += *(pyear + i);
    
  return day;
}

int month_day(int year, int yearday, int *pmonth, int *pday) {
  int i, leap, totaldays;
  
  if (yearday <= 0) {
    printf("error: wrong day number %d\n", yearday);
    return -1;
  }

  leap = year % 4 == 0 && year % 100 != 0 || year % 400 == 0;
  
  totaldays = leap ? 366 : 365;
  
  if (yearday > totaldays) {
    printf(
      "error:year %d contains %d days, but "
      "you specified day number %d\n",
      year, totaldays, yearday
    );
    return -1;
  }

  for (i = 1; yearday > *(*(daytab + leap) + i); i++)
    yearday -= *(*(daytab + leap) + i);
    
  *pmonth = i;
  *pday = yearday;
  return 0;
}
