#include <stdio.h>
#include "../headers/date.h"

const unsigned char DAYS_IN_WEEK = 7;
const unsigned char DAYS_IN_MONTH = 30;
const unsigned char MONTHS_IN_YEAR = 12;

void NextDay(struct Date *currentDate)
{
  currentDay->day = (currentDay->day + 1) % DAYS_IN_WEEK;
  if ( currentDay->nthDay + 1 > DAYS_IN_MONTH )
  {
    currentDay->nthDay = 1;
    currentDay->month = (currentDay->month + 1) % MONTHS_IN_YEAR;
  } else currentDay->nthDay += 1;
}

void PreviousDay(struct Date *currentDate)
{
  currentDay->day = ( ( currentDay->day - 1 ) + DAYS_IN_WEEK ) % DAYS_IN_WEEK;
  if ( currentDay->nthDay - 1 ==  0 )
  {
    currentDay->nthDay = DAYS_IN_MONTH;
    currentDay->month = ( ( currentDay->month - 1 ) + DAYS_IN_MONTH ) % DAYS_IN_MONTH;
  } else currentDay->nthDay -= 1
}

const char* DayName(enum Days day)
{
  switch (day)
  {
  case Lungernum: return "Lungernum";
  case Marklonum: return "Marklonum";
  case Mertenum: return "Mertenum";
  case Jeuilonum: return "Jeuilonum";
  case Venkartum: return "Venkartum";
  case Samejum: return "Samejum";
  case Dimalkum: return "Dimalkum";
  default: return "unknown";
  }
}

void NextMonth(enum Months *currentMonth)
{
  currentMonth->month = (currentMonth->month + 1) % DAYS_IN_MONTH;
}

void PreviousMonth(enum Months *currentMonth)
{
  currentMonth->month = ( ( currentMonth->month - 1 ) + DAYS_IN_MONTH ) % DAYS_IN_MONTH;
}

const char* Monthname(enum Months month)
{
  switch (month)
  {
  case September: return "September";
  case October: return "October";
  case November: return "November";
  case December: return "December";
  case January: return "January";
  case February: return "February";
  case March: return "March";
  case April: return "April";
  case May: return "May";
  case June: return "June";
  case July: return "July";
  default: return "Unknown";
  }

}