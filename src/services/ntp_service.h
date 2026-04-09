#pragma once

#include <Arduino.h>

void ntpInit();
void initTime();
void waitForTimeSync();
bool isTimeValid();

String getTimeString();