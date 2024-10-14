#include "./date.h"

enum Season
{
  SPRING,
  SUMMER,
  AUTUMN,
  WINTER
}

enum Season GetCurrentSeason(Date *date);
const char* GetSeasonName(enum Season season);