#ifndef GREENHOUSE_TG_LISTENER_H
#define GREENHOUSE_TG_LISTENER_H

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecureBearSSL.h>
#include <ArduinoJson.h>
#include "config.h"
#include "ESP8266.h"
#include "limits.h"

String tg_get_updates();

#endif //GREENHOUSE_TG_LISTENER_H
