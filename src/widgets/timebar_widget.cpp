#include "timebar_widget.h"
#include "../display/display_manager.h"
#include "../services/ntp_service.h"
#include <time.h>

void drawTimeBar()
{
    if (!isTimeValid()) return;

    time_t now = time(nullptr);
    struct tm* timeinfo = localtime(&now);

    if (!timeinfo) return;

    // cálculo de progreso del día
    int minutesOfDay = timeinfo->tm_hour * 60 + timeinfo->tm_min;
    float progress = minutesOfDay / 1440.0;

    // dimensiones (ajústalas a tu layout)
    int x = 10;
    int y = 340;
    int width = 620;
    int height = 17;
    int borderThickness = 3;//Grosor de rectangulo rojo 

    int filledWidth = progress * width;

    // progreso
    display.fillRect(x, y, filledWidth, height, GxEPD_RED);

    // borde rojo de la  barra (
    for (int i = 0; i < borderThickness; i++)
    {
        display.drawRect(
            x - i,
            y - i,
            width + 2 * i,
            height + 2 * i,
            GxEPD_BLACK
        );
    }
    

    // marcadores (cada 6 horas)
    int markers[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23,24};

    for (int i = 0; i < 25; i++)
    {
        int h = markers[i];
        int px = x + (h / 24.0) * width;

        // línea vertical
        display.drawLine(px, y - 5, px, y + height + 5, GxEPD_BLACK);

        // etiqueta
        display.setTextSize(1);
        display.setCursor(px - 10, y + height + 14);
        display.print(h);
    }
}