#pragma once
#include <Arduino.h>

struct WeatherData
{
    float temperature;
    int weatherCode;
    float windspeed;
    int rainProbability;   // %
    float uvIndex;         // índice UV
};

void updateWeather();
WeatherData getWeather();