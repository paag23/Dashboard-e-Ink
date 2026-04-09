#include "clock_widget.h"
#include "../display/display_manager.h"
#include "../services/ntp_service.h"

// Funcion refresca solo la hora
void updateClockArea()
{
    /*
    int x = 200;
    int y = 20;
    int w = 400;
    int h = 80;
    
    if (!isTimeValid()) {
        Serial.println("Tiempo no válido aún (clock)");
        return;
    }

    display.setPartialWindow(x, y, w, h);
    display.firstPage();
    do
    {
        display.fillRect(x, y, w, h, GxEPD_WHITE);
        drawClock();
    }
    while(display.nextPage());

    */
}

void drawClock()
{
    String timeStr = getTimeString();

    display.setTextSize(4);
    display.setCursor(300,60);
    display.print(timeStr);
}