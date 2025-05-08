#ifndef GREENHOUSE_LIMITS_H
#define GREENHOUSE_LIMITS_H

#include "config.h"
#include "sensors.hh"
#include "telegram.hh"

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
