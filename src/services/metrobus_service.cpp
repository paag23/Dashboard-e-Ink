#include "metrobus_service.h"
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <ArduinoJson.h>

MetrobusData metrobus[MAX_LINEAS];

// Función para eliminar acentos y caracteres especiales
String limpiarTexto(String texto) {
    texto.replace("á", "a");
    texto.replace("é", "e");
    texto.replace("í", "i");
    texto.replace("ó", "o");
    texto.replace("ú", "u");
    texto.replace("Á", "A");
    texto.replace("É", "E");
    texto.replace("Í", "I");
    texto.replace("Ó", "O");
    texto.replace("Ú", "U");
    texto.replace("ñ", "n");
    texto.replace("Ñ", "N");
    texto.replace("ü", "u");
    texto.replace("Ü", "U");
    texto.replace("¿", "");
    texto.replace("?", "");
    texto.replace("¡", "");
    texto.replace("!", "");
    texto.replace(".", "");
    texto.replace(",", "");
    texto.replace(";", "");
    texto.replace(":", "");
    texto.replace("\n", " ");
    texto.replace("\r", " ");
    return texto;
}

void updateMetrobus()
{
    WiFiClient client;
    HTTPClient http;

    const char* url = "http://192.168.1.155:3000/metrobus";

    http.begin(client, url);
    int httpCode = http.GET();

    Serial.print("Metrobus HTTP: ");
    Serial.println(httpCode);

    if (httpCode == 200)
    {
        String payload = http.getString();
        Serial.println(payload);

        StaticJsonDocument<2048> doc;
        DeserializationError error = deserializeJson(doc, payload);

        if (error)
        {
            Serial.println("Error parsing Metrobus JSON");
            return;
        }

        // Limpiar todas las líneas
        for (int i = 0; i < MAX_LINEAS; i++)
        {
            metrobus[i].linea = i + 1;
            metrobus[i].servicioNormal = true;
            metrobus[i].hayAfectaciones = false;
            metrobus[i].estado = "OK";
            metrobus[i].estaciones = "";
            metrobus[i].info = "";
        }

        if (!doc.is<JsonArray>())
        {
            Serial.println("El JSON no es un array");
            http.end();
            return;
        }

        JsonArray array = doc.as<JsonArray>();
        int arraySize = array.size();

        if (arraySize == 0)
        {
            Serial.println("Servicio normal");
            http.end();
            return;
        }

        // Procesar solo incidentes
        for (int i = 0; i < arraySize; i++)
        {
            JsonObject obj = array[i];
            
            int linea = obj["l"] | 0;
            int estado = obj["e"] | 1;
            String estaciones = obj["s"] | "";
            String info = obj["i"] | "";
            
            // Limpiar acentos y caracteres raros
            estaciones = limpiarTexto(estaciones);
            info = limpiarTexto(info);

            if (estado == 0 && linea > 0 && linea <= MAX_LINEAS)
            {
                int index = linea - 1;
                metrobus[index].linea = linea;
                metrobus[index].servicioNormal = false;
                metrobus[index].hayAfectaciones = true;
                metrobus[index].estado = "AFECTADO";
                metrobus[index].estaciones = estaciones;
                metrobus[index].info = info;
                
                // Mostrar en una sola línea
                Serial.print("Linea ");
                Serial.print(linea);
                Serial.print(": ");
                Serial.print(estaciones);
                if (info.length() > 0) {
                    Serial.print(" - ");
                    Serial.print(info);
                }
                Serial.println();
            }
        }
    }

    http.end();
}

MetrobusData* getMetrobusData()
{
    return metrobus;
}