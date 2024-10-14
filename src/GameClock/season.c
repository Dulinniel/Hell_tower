#include "../headers/season.h"

#define IS_AUTUMN(month) ((month) <= 2)
#define IS_WINTER(month) ((month) >= 3 && (month) <= 5)
#define IS_SPRING(month) ((month) >= 6 && (month) <= 8)
#define IS_SUMMER(month) ((month) >= 9 && (month) <= 11)

enum Season GetCurrentSeason(Date *date)
{
  enum Season season;

  if ( IS_AUTUMN(date->month) ) season = AUTUMN;
  else if ( IS_WINTER(date->month) ) season = WINTER;
  else if ( IS_SPRING(date->month) ) season = SPRING;
  else if ( IS_SUMMER(date->month) ) season = SUMMER;

  return season;
}

const char* GetSeasonName(enum Season season)
{
  switch (season)
  {
  case AUTUMN: return "Autumn";
  case WINTER: return "Winter";
  case SPRING: return "Spring";
  case SUMMER: return "Summer";
  default: return "Unknown";
  }
}