#include "limits.hh"

// Flags
bool max_temp_reached = false;
bool min_temp_reached = false;

// Moisture
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

// Relay
float relay_on_temperature;
float relay_off_temperature;

void setRelayOnTemperature(float value) {
  relay_on_temperature = value;
}

float getRelayOnTemperature() {
  return relay_on_temperature;
}

void setRelayOffTemperature(float value) {
  relay_off_temperature = value;
}

float getRelayOffTemperature() {
  return relay_off_temperature;
}

void check_relay_limits() {
  float cur_relay_temp = getRelayTemperature();

  if (!isActive() && cur_relay_temp <= relay_on_temperature) {
      relayOn();
      tg_send_message(String(MSG_RELAY_ON) + ". " + String(cur_relay_temp) + " " + DEGREE + "C");      
  } else if (isActive() && cur_relay_temp >= relay_off_temperature) {
    relayOff();
    tg_send_message(String(MSG_RELAY_OFF) + ". " + String(cur_relay_temp) + " " + DEGREE + "C");
  }
}

// Check
bool check_limits(){
    //  Actual temperature HIGHER than the limit value  
  if (getMaxTemperatureOnSensors() > max_temperature) {    
    if (!max_temp_reached)  //  Notify only once
      tg_send_message(MSG_MAX_TEMPERATURE_LIMIT);

    max_temp_reached = true;
    min_temp_reached = false;
    return false;
    //  Actual temperature LOWER than the limit value
  } else if (getMinTemperatureOnSensors() < min_temperature) {
    if (!min_temp_reached)  //  Notify only once
      tg_send_message(MSG_MIN_TEMPERATURE_LIMIT);

    max_temp_reached = false;
    min_temp_reached = true;
    return false;
  } else {
    //  Actual temperature within the limit range
    max_temp_reached = false;
    min_temp_reached = false;
  }
  return true;   
}
