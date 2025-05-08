#include "limits.hh"

// Moisture
// int air_moisture_value    = AIR_MOISTURE_VALUE;     //  Значение датчика в воздухе
// int water_moisture_value  = WATER_MOISTURE_VALUE;   //  Значение датчика в воде
int air_moisture_value;   //  Значение датчика в воздухе
int water_moisture_value; //  Значение датчика в воде

void setAirMoisture(int value){
    air_moisture_value = value;
}

int getAirMoisture(){
    return air_moisture_value;
}

void setWaterMoisture(int value){
    water_moisture_value = value;
}

int getWaterMoisture(){
    return water_moisture_value;
}

// Temperature
// float max_temperature = MAX_TEMPERATURE_VALUE;
// float min_temperature = MIN_TEMPERATURE_VALUE;
float max_temperature;
float min_temperature;

void setMaxTemperature(float value) {
  max_temperature = value;
}

float getMaxTemperature() {
  return max_temperature;
}

void setMinTemperature(float value) {
  min_temperature = value;
}

float getMinTemperature() {
  return min_temperature;
}

// Check
bool check_limits(){
    if (getMaxTemperatureOnSensors() > max_temperature) {
        tg_send_message(MSG_MAX_TEMPERATURE_LIMIT);
        return false;
    } else if (getMinTemperatureOnSensors() < min_temperature) {
        tg_send_message(MSG_MIN_TEMPERATURE_LIMIT);
        return false;
    }
    return true;   
}
