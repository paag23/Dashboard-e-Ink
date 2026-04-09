#include "weather_widget.h"

#include "../display/display_manager.h"
#include "../services/weather_service.h"
#include "../assets/icons_weather.h"

String getUVLevel(float uv)
{
    if(uv < 3) return "Bajo";
    if(uv < 6) return "Moderado";
    if(uv < 8) return "Alto";
    if(uv < 11) return "Muy Alto";
    return "Extremo";
}

String getWeatherDescription(int code)
{
    if(code == 0) return "Soleado";
    if(code <= 3) return "Nublado";
    if(code <= 60) return "Lluvia";
    if(code <= 80) return "Tormenta";

    return "Clima";
}

void drawWeather()
{
    WeatherData data = getWeather();

    int iconX = 80;
    int iconY = 140;
    int tempX = 150;
    int tempY = 150;

    //---------------- Icono Clima   rojo 
    const unsigned char* icon;
    uint16_t iconColor = GxEPD_BLACK;

    if(data.weatherCode == 0)
    {
        icon = sun_icon;
    }
    else if(data.weatherCode <= 3)
    {
        icon = cloud_icon;
       
    }
    else if(data.weatherCode < 70)
    {
        icon = rain_icon;

        if(data.rainProbability >= 60)
            iconColor = GxEPD_RED;
    }
    else
    {
        icon = storm_icon;
        iconColor = GxEPD_RED; // tormenta siempre roja
    }

    display.drawBitmap(iconX-55, iconY, icon, 128, 64, iconColor);

    // -----------------UV Rojo
    display.setTextSize(4);
    if(data.uvIndex >= 8)
        display.setTextColor(GxEPD_RED);
    else
        display.setTextColor(GxEPD_BLACK);

    display.setCursor(tempX, tempY);
    display.print((int)data.temperature);

    display.drawCircle(tempX + 52, tempY - 3, 5, GxEPD_BLACK);
        // regresar a negro
    display.setTextColor(GxEPD_BLACK);


    //------------------Lluvia Rojo
    display.setTextSize(2);
    display.setCursor(tempX, tempY + 100);
    if(data.rainProbability >= 60)
        display.setTextColor(GxEPD_RED);
    else
        display.setTextColor(GxEPD_BLACK);

    display.print("Lluvia ");
    display.print(data.rainProbability);
    display.print("%");

    display.setTextColor(GxEPD_BLACK);
    
    //---------------------- UV Rojo
    display.setCursor(tempX, tempY + 130);
    if(data.uvIndex >= 8)
        display.setTextColor(GxEPD_RED);
    else
        display.setTextColor(GxEPD_BLACK);

    display.print("UV ");
    display.print(getUVLevel(data.uvIndex));

    display.setTextColor(GxEPD_BLACK);

  
    //---------------------- descripción
    display.setTextSize(2);
    display.setCursor(tempX, tempY + 40);
    display.print(getWeatherDescription(data.weatherCode));

    //----------------------- viento
    display.setCursor(tempX, tempY + 70);
    display.print("Viento ");
    display.print((int)data.windspeed);

}