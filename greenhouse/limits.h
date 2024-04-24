#ifndef GREENHOUSE_LIMITS_H
#define GREENHOUSE_LIMITS_H

#include "config.h"
#include "DS18B20.h"
#include "ESP8266.h"

void setAirMoisture(int value);
int getAirMoisture();
void setWaterMoisture(int value);
int getWaterMoisture();

void setMaxTemperature(float value);
float getMaxTemperature();
void setMinTemperature(float value);
float getMinTemperature();

bool check_limits();

#endif // GREENHOUSE_LIMITS_H
