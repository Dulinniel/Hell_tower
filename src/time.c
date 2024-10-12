#include <stdio>
#include "./headers/time.h"

const unsigned char FIRST_MORNING_HOUR = 6;
const unsigned char FIRST_MORNING_MINUTE = 0;
const unsigned char MINUTES_IN_AN_HOUR = 60;

struct Time InitClock()
{
  struct Time clock;
  clock.hour = FIRST_MORNING_HOUR;
  clock.minute = FIRST_MORNING_MINUTE;
  clock.moment = SUNRISE;
  return clock
}

void UpdateCurrentTime(struct Time *clock, unsigned char minutes_elapsed)
{
  if ( clock == NULL ) &clock = InitClock();
  clock->hour += minutes_elapsed / MINUTES_IN_AN_HOUR;
  minutes_elapsed %= MINUTES_IN_AN_HOUR;
  clock->minute += minutes_elapsed;
  UpdateMoment(clock);
}

void UpdateMoment(struct Time *clock)
{
  if ( clock->hour >= 4 && clock->hour <= 6 ) clock->moment = SUNRISE;
  if ( clock->hour >= 7 && clock->hour <= 11 ) clock->moment = MORNING;
  if ( clock->hour >= 12 && clock->hour <= 16 ) clock->moment = AFTERNOON;
  if ( clock->hour >= 17 && clock->hour <= 21 ) clock->moment = SUNSET;
  else clock->moment = NIGHT;
}

const char* GetMomentDay(enum Moment moment)
{
  switch (moment)
  {
  case SUNRISE: return "Sunrise";
  case MORNING: return "Morning";
  case AFTERNOON: return "Afternoon";
  case SUNSET: return "Sunset";
  default: return "Unknown";
  }
}