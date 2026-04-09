#include "display_manager.h"

GxEPD2_3C<GxEPD2_750c, 16> display(
    GxEPD2_750c(15, 4, 2, 5)
);

void displayInit()
{
    display.init();
    display.setRotation(2);
    display.setTextColor(GxEPD_BLACK);
}

void displayClear()
{
    display.setFullWindow();
    display.firstPage();

    do
    {
        display.fillScreen(GxEPD_WHITE);
    }
    while (display.nextPage());
}