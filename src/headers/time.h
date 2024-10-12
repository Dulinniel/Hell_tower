enum Moment
{
  SUNRISE,
  MORNING,
  AFTERNOON,
  SUNSET,
  NIGHT,
}

struct Time
{
  unsigned char hour;
  unsigned char minute;
  enum Moment moment;
}

struct Time InitClock();
void UpdateCurrentTime(struct Time *clock, unsigned char minutes_elapsed);
void UpdateMoment(struct Time *clock);
const char* GetMomentDay(enum Moment moment);