#include <stdlib.h>
#include "../headers/random.h";

int RandomBetween(int min, int max)
{
  return rand() % (max - min + 1) + min;
}