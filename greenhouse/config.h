#ifndef GREENHOUSE_CONFIG_H
#define GREENHOUSE_CONFIG_H

#include "lang/ru.h"
#include <Arduino.h>

//  Параметры для Wi-Fi модуля
#define STASSID "your_SSID" //  Название Wi-Fi сети
#define STAPSK "your_password"  //  Пароль от Wi-Fi сети

#define TIME_API    "https://ipwho.is"
#define FREQUENCY   60  // Периодичность уведомлений (N min)

//  Настройка API Telegram
#define TELEGRAM_BOT_TOKEN "your_token"
#define CHAT_ID {"chat_id_1", "chat_id_2"}  //  Multi

//  Настройка датчика влажности
#define MOISTURE_SENSOR_PIN A0      //  Пин (аналоговый)

//  Пин для реле
#define RELAY_PIN 1
#define THERMAL_SENSOR_FOR_RELAY    1
#define RELAY_ON_TEMPERATURE_VALUE  8   //  Значение температуры для включения реле
#define RELAY_OFF_TEMPERATURE_VALUE 11  //  Значение температуры для выключения реле

//  Настройка датчика температуры
#define TEMPERATURE_SENSOR_PIN  4   //  Пин (цифровой)
#define THERMAL_SENSOR_0        "почвы"    //  Имя термо-датчика №1
#define THERMAL_SENSOR_1        "воздуха теплицы"    //  Имя термо-датчика №2
#define THERMAL_SENSOR_2        "воздуха улицы"    //  Имя термо-датчика №3

//  Значения по умолчанию
#define AIR_MOISTURE_VALUE      856 //  Значение датчика в воздухе
#define WATER_MOISTURE_VALUE    488 //  Значение датчика в воде
#define MAX_TEMPERATURE_VALUE   40  //  Максимально допустимое значение температуры
#define MIN_TEMPERATURE_VALUE   -10 //  Минимально допустимое значение температуры

#endif //GREENHOUSE_CONFIG_H
