#ifndef SEASON_H
#define SEASON_H

#include "./date.h"

enum Season
{
  SPRING,
  SUMMER,
  AUTUMN,
  WINTER,
};

enum Season GetCurrentSeason(struct Date *date);
const char* GetSeasonName(enum Season season);

#endif