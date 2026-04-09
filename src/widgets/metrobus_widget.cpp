#include "metrobus_widget.h"

#include "../display/display_manager.h"
#include "../services/metrobus_service.h"

void drawMetrobusWidget()
{
    MetrobusData* data = getMetrobusData();

    int x = 5;
    int y = 3;
    int lineHeight = 25;

    int count = 0;
    int totalProblemas = 0;

    // contar líneas con problemas
    for (int i = 0; i < 7; i++)
    {
        if (!data[i].servicioNormal || data[i].hayAfectaciones)
        {
            totalProblemas++;
        }
    }

    // dibujar máximo 4
    for (int i = 0; i < 7 && count < 4; i++)
    {
        if (!data[i].servicioNormal || data[i].hayAfectaciones)
        {
            display.setTextColor(GxEPD_RED);
            display.setTextSize(2);

            display.setCursor(x, y + (count * lineHeight));

            String linea = "MB-L" + String(data[i].linea);

            String estado = data[i].estado;
            String estaciones = data[i].estaciones;
            String info = data[i].info;

            // limpiar valores innecesarios
            if (estado == "Servicio Regular") estado = "";
            if (estaciones == "Ninguna") estaciones = "";
            if (info == "") info = "";

            // evitar acentos (importante en e-paper)
            estado.replace("á","a");
            estado.replace("é","e");
            estado.replace("í","i");
            estado.replace("ó","o");
            estado.replace("ú","u");

            estaciones.replace("á","a");
            info.replace("á","a");

            // truncado básico (para evitar overflow)
            if (estado.length() > 18) estado = estado.substring(0, 18);
            if (estaciones.length() > 18) estaciones = estaciones.substring(0, 18);
            if (info.length() > 18) info = info.substring(0, 18);

            // construir línea
            String lineaFinal = linea;

            if (estado.length() > 0)
                lineaFinal += " " + estado;

            if (estaciones.length() > 0)
                lineaFinal += " - " + estaciones;

            if (info.length() > 0)
                lineaFinal += " - " + info;

            display.print(lineaFinal);

            count++;
        }
    }

    // indicador si hay más
    if (totalProblemas > 4)
    {
        display.setCursor(x, y + (4 * lineHeight));
        display.print("+" + String(totalProblemas - 4) + " mas...");
    }

    // reset color
    display.setTextColor(GxEPD_BLACK);
}