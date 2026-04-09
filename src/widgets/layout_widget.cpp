#include "layout_widget.h"
#include "../display/display_manager.h"

void drawLayout()
{
    for(int i = 0; i < 3; i++)
    {
        // línea superior
        display.drawLine(0, 100 + i, 780, 100 + i, GxEPD_BLACK);

        // división clima / calendario
        display.drawLine(340 + i, 100, 340 + i , 330, GxEPD_BLACK);

        // línea superior status bar
        ///display.drawLine(20,400,780,400,GxEPD_BLACK);   
        
    }
}