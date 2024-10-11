#include <stdio.h>
#include "./headers/date.h"

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
  const char* name;
  switch (day)
  {
  case Lungernum:
    name = "Lungernum";
    break;
  case Marklonum:
    name = "Marklonum";
    break;
  case Mertenum:
    name = "Mertenum";
    break;
  case Jeuilonum:
    name = "Jeuilonum";
    break;
  case Venkartum:
    name = "Venkartum";
    break;
  case Samejum:
    name = "Samejum";
    break;
  case Dimalkum:
    name = "Dimalkum";
    break;
  default:
    name = "unknown";
    break;
  }

  return name;

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
  const char* name;
  switch (month)
  {
  case September:
    name = "September";
    break;
  case October:
    name = "October";
    break;
  case November:
    name = "November";
    break;
  case December:
    name = "December";
    break;
  case January:
    name = "January";
    break;
  case February:
    name = "February";
    break;
  case March:
    name = "March";
    break;
  case April:
    name = "April";
    break;
  case May:
    name = "May";
    break;
  case June:
    name = "June";
    break;
  case July:
    name = "July";
    break;
  default:
    name = "Unknown";
    break;
  }

  return name;

}