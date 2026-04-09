#include "calendar_widget.h"
#include "../display/display_manager.h"
#include <time.h>


/* Calcula el primer dia del mes
0 = Lunes
1 = Martes
2 = Miércoles
3 = Jueves
4 = Viernes
5 = Sábado
6 = Domingo
*/
int firstDayOfMonth(int year, int month)
{
    struct tm t = {0};

    t.tm_year = year - 1900;
    t.tm_mon = month - 1;
    t.tm_mday = 1;

    mktime(&t);

    int day = t.tm_wday;

    // convertir domingo=0 a lunes=0
    if(day == 0)
        day = 6;
    else
        day--;

    return day;
}

int daysInMonth(int year, int month)
{
    if(month == 2)
    {
        if((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
            return 29;

        return 28;
    }

    if(month == 4 || month == 6 || month == 9 || month == 11)
        return 30;

    return 31;
}

String getMonthName(int month)
{
    const char* months[] =
    {
        "ENERO","FEBRERO","MARZO","ABRIL","MAYO","JUNIO",
        "JULIO","AGOSTO","SEPTIEMBRE","OCTUBRE","NOVIEMBRE","DICIEMBRE"
    };

    return String(months[month-1]);
}

void drawCalendar()
{
    int startX = 360;
    int startY = 140;

    int cellW = 40;
    int cellH = 30;

    display.setTextSize(2);

    display.setCursor(startX, startY);
    display.print(" L   M   M  J  V  S  D");

    startY += 20;

    // obtener fecha actual
    time_t now = time(nullptr);
    struct tm *t = localtime(&now);

    int today = t->tm_mday;
    int month = t->tm_mon + 1;
    int year = t->tm_year + 1900;

    // ESCRIBE EL MES 
    String monthName = getMonthName(month);

    display.setTextSize(2);
    display.setCursor(startX, startY - 40); //CALCULA EL MES
    display.print(monthName + " " + String(year));


    int startDay = firstDayOfMonth(year, month);
    int totalDays = daysInMonth(year, month);

    int col = startDay;
    int row = 0;

    for(int day = 1; day <= totalDays; day++)
    {
        int x = startX + col * cellW;
        int y = startY + row * cellH;

        String d = String(day);

        int textWidth = d.length() * 12;
        int centeredX = x + (cellW - textWidth) / 2;

        if(day == today)
        {
            display.setTextColor(GxEPD_RED);
        }
        else
        {
            display.setTextColor(GxEPD_BLACK);
        }

        display.setCursor(centeredX, y);
        display.print(d);

        col++;

        if(col == 7)
        {
            col = 0;
            row++;
        }
    }

    display.setTextColor(GxEPD_BLACK);
}