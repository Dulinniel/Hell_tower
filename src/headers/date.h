enum Days
{
  Lungernum, // Monday
  Marklonum, // Tuesday
  Mertenum, // Wednesday
  Jeuilonum, // Thursday
  Venkartum, // Friday
  Samejum, // Saturday
  Dimalkum // Sunday
};

enum Months
{
  September;
  October;
  November;
  December;
  January;
  February;
  March;
  April;
  May;
  June;
  July;
  August
};

struct Date
{
  unsigned char nthDay;
  enum Days day;
  enum Months month;
};

void NextDay(struct Date *currentDate);
void PreviousDay(struct Date *currentDate);
const char* DayName(enum Days);

void NextMonth(enum Months *currentMonth);
void PreviousMonth(enum Months *currentMonth);
const char* Monthname(enum Months);
