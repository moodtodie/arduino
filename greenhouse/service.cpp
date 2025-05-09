#include "service.hh"

float roundToTenths(float value) {
  return (round(value * 10.0) / 10.0);
}

String formatIsoToShort(String isoformat) {
  // Извлекаем нужные части
  String datePart = isoformat.substring(0, 10);  // "YYYY-MM-DD"
  String timePart = isoformat.substring(11, 16); // "HH:MM"

  return datePart + " " + timePart;
}

String getDataTimeFromJson(String json_input) {
    DynamicJsonDocument json(1024);

    deserializeJson(json, json_input);

    return formatIsoToShort(json["timezone"]["current_time"].as<String>());
}
