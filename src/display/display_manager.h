#pragma once

#include <GxEPD2_3C.h>
#include <Adafruit_GFX.h>

extern GxEPD2_3C<GxEPD2_750c, 16> display;

void displayInit();
void displayUpdate();
void displayClear();