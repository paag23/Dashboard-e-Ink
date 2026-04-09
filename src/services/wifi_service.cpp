#include <ESP8266WiFi.h>
#include "../config/config.h"
#include <Arduino.h>

void wifiInit()
{
    WiFi.begin(WIFI_SSID, WIFI_PASS);
    Serial.println("Conectando WiFi...");
    Serial.println("");
    Serial.println("WiFi conectado");
    Serial.println(WiFi.localIP());

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
}

