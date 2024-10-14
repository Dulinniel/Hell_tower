#include <stdlib.h>
#include "../headers/weather.h"
#include "../Random/random.c";

struct MeteoProbability springProbabilities[] = 
{
  {SUNNY, 40},
  {RAINY, 30},
  {FOGGY, 10},
  {CLOUDY, 10},
  {STORMY, 10}
};

struct MeteoProbability summerProbabilities[] = 
{
  {SUNNY, 70},
  {CLOUDY, 15},
  {RAINY, 10},
  {STORMY, 5}
};

struct MeteoProbability autumnProbabilities[] = 
{
  {SUNNY, 20},
  {RAINY, 30},
  {CLOUDY, 20},
  {FOGGY, 15},
  {STORMY, 15}
};

struct MeteoProbability winterProbabilities[] = 
{
  {SNOWY, 30},
  {CLOUDY, 20},
  {SUNNY, 15},
  {RAINY, 20},
  {FOGGY, 15}
};

struct MeteoProbability* GetSeasonProbabilities(enum Season season, int *probabilitiesCount) 
{
  switch (season) 
  {
  case SPRING:
    *probabilitiesCount = sizeof(springProbabilities) / sizeof(springProbabilities[0]);
    return springProbabilities;
  case SUMMER:
    *probabilitiesCount = sizeof(summerProbabilities) / sizeof(summerProbabilities[0]);
    return summerProbabilities;
  case AUTUMN:
    *probabilitiesCount = sizeof(autumnProbabilities) / sizeof(autumnProbabilities[0]);
    return autumnProbabilities;
  case WINTER:
    *probabilitiesCount = sizeof(winterProbabilities) / sizeof(winterProbabilities[0]);
    return winterProbabilities;
  default:
    *probabilitiesCount = 0;
    return NULL;
  }
}

enum Weather SetWeather(enum Season season)
{
  enum Weather resultingMeteo;
  int probabilitiesCount = 0;
  struct MeteoProbability* probabilities = GetSeasonProbabilities(season, &probabilitiesCount);

  // If the season does not exist return a generic meteo
  if (probabilities != NULL && probabilitiesCount != 0) 
  {  
    // Sum up probabilities
    int totalProbability = 0;
    for (int i = 0; i < probabilitiesCount; i++) totalProbability += probabilities[i].probability;

    // Generate a random number from the total range
    int randomValue = rand() % totalProbability;

    // Select the resulting weather based on the out random value
    int cumulativeProbability = 0;
    for (int i = 0; i < probabilitiesCount; i++) 
    {
      cumulativeProbability += probabilities[i].probability;
      if (randomValue < cumulativeProbability) resultingMeteo = probabilities[i].meteo;
    }
  } else resultingMeteo = SUNNY;

  return resultingMeteo;
}

void UpdateWeather(struct WeatherReport *weatherReport, enum Season season)
{
  weatherReport->temperature_range = GetTemperatureRange(season);
  enum Weather cuurentWeather = SetWeater(season);
  weatherReport->current_temperature = RandomBetween(weatherReport->temperature_range->minimal_temperature,
                                                     weatherReport->temperature_range->maximal_temperature);
  weatherReport->weather = cuurentWeather;
}

struct Temperature_Range GetTemperatureRange(enum Season season)
{
  switch (season)
  {
  case SPRING: return (struct Temperature_Range){5, 15};
  case SUMMER: return (struct Temperature_Range){20, 35};
  case AUTUMN: return (struct Temperature_Range){10, 20};
  case WINTER: return (struct Temperature_Range){-10, 5};
  default: return (struct Temperature_Range){0, 0}; // Valeur par défaut
  }
}

const char* GetMeteoName(Meteo meteo)
{
  switch (meteo)
  {
  case RAINY: return "Rainy";
  case SUNNY: return "Sunny";
  case SNOWY: return "Snowy";
  case STORMY: return "Stormy";
  case FOGGY: return "Foggy";
  case CLOUDY: return "Cloudy";
  default: return "Unknown";
  }
}