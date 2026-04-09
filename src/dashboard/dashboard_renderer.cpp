#include "dashboard_renderer.h"
#include "../display/display_manager.h"
#include "../widgets/clock_widget.h"
#include "../widgets/weather_widget.h"
#include "../widgets/calendar_widget.h"
#include "../widgets/layout_widget.h"
#include "../widgets/timebar_widget.h"
#include "../widgets/metrobus_widget.h"

void renderDashboard()
{
    display.setFullWindow();
    display.firstPage();
    do
    {
        display.fillScreen(GxEPD_WHITE);

        drawLayout();
        //drawClock();
        drawMetrobusWidget();
        drawWeather();
        drawCalendar();
        drawWeather();
        drawTimeBar();

    }
    while (display.nextPage());
}