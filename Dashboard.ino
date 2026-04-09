#include "src/display/display_manager.h"
#include "src/dashboard/dashboard_renderer.h"
#include "src/services/wifi_service.h"
#include "src/services/ntp_service.h"
#include "src/widgets/clock_widget.h"
#include "src/services/weather_service.h"
#include "src/services/metrobus_service.h"

void setup()
{
    Serial.begin(115200);
    wifiInit();
    initTime();
    waitForTimeSync();
    updateWeather();
    updateMetrobus();
    displayInit();
    renderDashboard();
}

//inicializas estas variables
unsigned long lastClockUpdate = 0; // fuerza update inmediato
unsigned long lastWeatherUpdate = 0;
bool timeWasValid = false;
unsigned long lastMetrobusUpdate = 0;


void loop()
{
/*
    time_t now = time(nullptr); 

    if (now > 100000 && !timeWasValid)
    {
        Serial.println("Tiempo sincronizado detectado");
        //updateClockArea();
    
        timeWasValid = true;
    }
*/  
    if(millis() - lastWeatherUpdate >  600000) //  Actualiza clima cada 10 min
    {
        updateWeather(); 
        lastWeatherUpdate = millis();
                
        renderDashboard();  //updateCalendar() si lo tienes separado
    }

    if (millis() - lastMetrobusUpdate > 600000) // cada 10 min
    {
        updateMetrobus();
        lastMetrobusUpdate = millis();

        //Debug
        MetrobusData* data = getMetrobusData();

        for (int i = 0; i < 7; i++)
        {
            Serial.print("Linea ");
            Serial.print(data[i].linea);

            Serial.print(" Estado: ");
            Serial.print(data[i].servicioNormal ? "OK" : "PROBLEMA");

            Serial.print(" Afectaciones: ");
            Serial.println(data[i].hayAfectaciones ? "SI" : "NO");
        }
    }

    
/*  // Actualiza  el reloj 
    if(millis() - lastClockUpdate > 60000)//Actualiza hora cada min
    {
        updateClockArea(); 
        lastClockUpdate = millis();
    }
*/
}