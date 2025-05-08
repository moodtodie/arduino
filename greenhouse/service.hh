#ifndef GREENHOUSE_SERVICE_HH
#define GREENHOUSE_SERVICE_HH

#include <Regexp.h>
#include <ArduinoJson.h>

#include "config.h"

float roundToTenths(float value);
String getDataTimeFromJson(String input);
bool isCorrectDateFormat(String dateTime);

#endif //GREENHOUSE_SERVICE_HH
