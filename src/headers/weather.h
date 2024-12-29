#ifndef WEATHER_H
#define WEATHER_H

#include "./season.h"

enum Weather
{
  RAINY,
  SUNNY,
  SNOWY,
  STORMY,
  FOGGY,
  CLOUDY,
};

struct Temperature_Range
{
  char minimal_temperature;
  char maximal_temperature;
};

struct MeteoProbability
{
  enum Weather weather;
  int probability;  // entre 0 et 100 pour représenter la probabilité en pourcentage
};

struct WeatherReport
{
  enum Weather weather;
  struct Temperature_Range temperature;
  char current_temperature;
};

enum Weather SetWeather(enum Season season);
void UpdateWeather(struct WeatherReport *weatherReport, enum Season season);
struct Temperature_Range GetTemperatureRange(enum Season season);
const char* GetMeteoName(enum Weather meteo);

#endif