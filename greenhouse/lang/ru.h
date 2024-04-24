// для greenhouse.ino
#define MSG_SOURCE "Источник: https://github.com/moodtodie/arduino/tree/main/greenhouse"
#define MSG_HEADER "-------Arduino-запущен--------"
#define MSG_FOUND_TERAL_SENSORS_PT_1 "Найдено"
#define MSG_FOUND_TERAL_SENSORS_PT_2 "датчики температуры"
#define MSG_TERAL_SENSORS_NOT_FOUND "Датчики температуры НЕ найдены"
#define MSG_SEND_TG_MESSAGE "*Отправить сообщение Telegram*"
#define MSG_FOOTER "------------------------------"

// для телеграма
#define TG_HEADER "Arduino WeNos D1 R1 запущен!"
#define TG_COUNT_TERAL_SENSORS "Датчиков температуры"
//  /info 
#define TG_DESC_TO_SET_NEW_LIMITS "Чтобы установить новый ограничения"
#define TG_DESC_TYPE_TEMPERATURE "температура (val - с плавающей запятой)"
#define TG_DESC_TYPE_MOISTURE "влажность (val - целочисленое)"
#define TG_DESC_UPPER_LIMIT "верхняя граница"
#define TG_DESC_LOWER_LIMIT "нижняя граница"
#define TG_DESC_TO_PRINT_PARAMETERS "Чтобы вывести значения параметров"
#define TG_DESC_TO_PRINT_LIMITS "Чтобы вывести значения ограничений"
#define TG_DESC_TO_PRINT_THIS_MESSAGE "Чтобы вывести это сообщение"
//  /setlimits
#define TG_SUCCESSFULLY_MODIFIED "Успешно изменено!"
#define TG_UNKNOWN_PARAMETER "Ошибка! Неизвестный параметр"
#define TG_UNKNOWN_TYPE "Ошибка! Неизвестный тип"
//  /limits
#define TG_LIMITATIONS "Ограничения"
#define TG_MAX_TEMPERATURE "Макс. температура"
#define TG_MIN_TEMPERATURE "Мин.  температура"
#define TG_AIR_MOISTURE "Влажность воздуха (нижний предел отн. влажности)"
#define TG_WATER_MOISTURE "Влажность воды (верхний предел отн. влажности)"
//  _
#define TG_UNKNOWN_COMMAND "Неизвестная команда"


// ошибки
#define ERR_MSG_FAILED_TO_EXTRACT_VALUES "Ошибка: Не удалось извлечь все значения из строки"

// для термодатчиков
#define MSG_TEMPERATURE "Температура"
#define MSG_SENSOR_N "датчик №"
#define MSG_NO_DATA "Нет данных"

// для датчика влажности
#define MSG_MOISTURE_SENSOR_VALUE "Значение датчика влажности"
#define MSG_RELATIVE_MOISTURE_SENSOR_VALUE "Относительная влажность почвы"

// для ESP8266
#define MSG_CONNECTING_TO "Подключение к"
#define MSG_CONNECTED "Подключено"
#define MSG_DATE "Дата"
#define MSG_NO_CONNECTION "Нет соединения"

// для ограничений
#define MSG_MAX_TEMPERATURE_LIMIT "ВНИМАНИЕ! Температура ВЫШЕ предела"
#define MSG_MIN_TEMPERATURE_LIMIT "ВНИМАНИЕ! Температура НИЖЕ предела"
