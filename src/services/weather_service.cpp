#include "weather_service.h"

#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <ArduinoJson.h>

WeatherData currentWeather;

void updateWeather()
{   //Conexión HTTP
    WiFiClient client;
    HTTPClient http;
    
    //URL de Open-Meteo
    String url =
    "http://api.open-meteo.com/v1/forecast?"
    "latitude=19.47&longitude=-99.09"
    "&current_weather=true"
    "&hourly=precipitation_probability,uv_index"
    "&forecast_days=1"
    "&timezone=auto";

    // Petición HTTP
    http.begin(client, url);
    int httpCode = http.GET();
    
    // 200 → OK 404 → error -1 → fallo conexión
    Serial.print("HTTP CODE: ");
    Serial.println(httpCode);

    if(httpCode == 200)
    {   
        //Obtiene json
        String payload = http.getString();

        Serial.println("===== WEATHER RAW =====");
        Serial.println(payload);
        
        //Reserva 2KB para parsear JSON
        StaticJsonDocument<4096> doc;
        
        //Convierte texto → estructura navegable
        DeserializationError error = deserializeJson(doc, payload);

        // Si falla: JSON corrupto, Memoria insuficiente
        if(error)
        {
            Serial.println("Error parsing JSON");
            return;
        }

        //Datos actuales, current weather
        currentWeather.temperature =
            doc["current_weather"]["temperature"];

        currentWeather.windspeed =
            doc["current_weather"]["windspeed"];

        currentWeather.weatherCode =
            doc["current_weather"]["weathercode"];

        // hourly arrays
        JsonArray rainArray =
            doc["hourly"]["precipitation_probability"];

        JsonArray uvArray =
            doc["hourly"]["uv_index"];

        if(!rainArray.isNull())
        {
            currentWeather.rainProbability = rainArray[0];
        }

        if(!uvArray.isNull())
        {
            currentWeather.uvIndex = uvArray[0];
        }
        
        //Impresion Datos DEBUG
        Serial.println("Temp: " + String(currentWeather.temperature));
        Serial.println("Wind: " + String(currentWeather.windspeed));
        Serial.println("Rain: " + String(currentWeather.rainProbability));
        Serial.println("UV: " + String(currentWeather.uvIndex));
    }

    //Libera memoria y socket
    http.end();
}

// Permite acceder desde otras partes del código
WeatherData getWeather()
{
    return currentWeather;
}