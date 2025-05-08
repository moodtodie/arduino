#ifndef GREENHOUSE_CONFIG_H
#define GREENHOUSE_CONFIG_H

#include "lang/ru.h"
#include <Arduino.h>

//  Параметры для Wi-Fi модуля
// #define STASSID "your_SSID" //  Название Wi-Fi сети
// #define STAPSK "your_password"  //  Пароль от Wi-Fi сети
#define LOCATION_IP "86.57.251.89"  //  IP-адрес, для которого будет получено текущее время
#define FREQUENCY   60          // Периодичность уведомлений (N min)

//  Настройка API Telegram
#define TELEGRAM_BOT_TOKEN "your_token"
#define CHAT_ID {"chat_id_1", "chat_id_2"}  //  Multi

//  Настройка датчика влажности
#define MOISTURE_SENSOR_PIN A0      //  Пин (аналоговый)

//  Настройка датчика температуры
#define TEMPERATURE_SENSOR_PIN  4   //  Пин (цифровой)
#define THERMAL_SENSOR_0        "датчика #1"    //  Имя термо-датчика №1
#define THERMAL_SENSOR_1        "датчика #2"    //  Имя термо-датчика №2
#define THERMAL_SENSOR_2        "датчика #3"    //  Имя термо-датчика №3

//  Значения по умолчанию
#define AIR_MOISTURE_VALUE      856 //  Значение датчика в воздухе
#define WATER_MOISTURE_VALUE    488 //  Значение датчика в воде
#define MAX_TEMPERATURE_VALUE   40  //  Максимально допустимое значение температуры
#define MIN_TEMPERATURE_VALUE   -10 //  Минимально допустимое значение температуры

#endif //GREENHOUSE_CONFIG_H
