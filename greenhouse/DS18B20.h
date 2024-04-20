#ifndef GREENHOUSE_DS18B20_H
#define GREENHOUSE_DS18B20_H

#include <OneWire.h>
#include <DallasTemperature.h>
#include "config.h"

void init_thermal_sensors();

// int getTLimit();

uint8_t getThermalSensorsCount();

String getTemperature();
// int getMaxTemperature();

#endif // GREENHOUSE_DS18B20_H
