#ifndef GREENHOUSE_SENSORS_HH
#define GREENHOUSE_SENSORS_HH

#include <OneWire.h>
#include <DallasTemperature.h>

#include "config.h"
#include "limits.hh"
#include "service.hh"

void init_thermal_sensors();
uint8_t getThermalSensorsCount();
String getTemperature();

float getMaxTemperatureOnSensors();
float getMinTemperatureOnSensors();

String get_soil_moisture();

#endif // GREENHOUSE_SENSORS_HH
