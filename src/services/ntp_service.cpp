#include "ntp_service.h"
#include <time.h>
#include <Arduino.h>


void initTime()
{
    // UTC-6 fijo (sin Horario de Verano
    configTime(-6 * 3600, 0, "pool.ntp.org");
}

void waitForTimeSync()
{
    Serial.print("Sincronizando tiempo");
    time_t now = time(nullptr);
    int retries = 0;

    while (now < 100000 && retries < 40)
    {
        delay(500);
        Serial.print(".");
        now = time(nullptr);
        retries++;
    }

    if (now < 100000)
    {
        Serial.println("\nERROR: NTP no sincronizado");
    }
    else
    {
        Serial.println("\nTiempo sincronizado");
    }
}

bool isTimeValid()
{
    return time(nullptr) > 100000;
}

String getTimeString()
{
    time_t now = time(nullptr);

    if (now < 100000) {
        return "--:--";
    }

    struct tm* timeinfo = localtime(&now);

    if (!timeinfo) {
        return "--:--";
    }

    char buffer[6];
    sprintf(buffer,"%02d:%02d",timeinfo->tm_hour,timeinfo->tm_min);

    return String(buffer);
}