#include "sensors.hh"

// Termal sensors

OneWire ow(TEMPERATURE_SENSOR_PIN);
DallasTemperature thermal_sensors(&ow);

void init_thermal_sensors() {
    pinMode(TEMPERATURE_SENSOR_PIN, INPUT);
    thermal_sensors.begin();
}

uint8_t getThermalSensorsCount() {
    return thermal_sensors.getDeviceCount();
}

String getTemperature() {
    // Send the command for all devices on the bus to perform a temperature conversion:
    thermal_sensors.requestTemperatures();
    String message = "";
    for (int i = 0; i < thermal_sensors.getDeviceCount(); i++)
    {
        // Fetch the temperature in degrees Celsius for device index:
        float tempC = thermal_sensors.getTempCByIndex(i); // the index 0 refers to the first device
        tempC = roundToTenths(tempC);

        // Print the temperature in Celsius in the Serial Monitor:
        message += String(MSG_TEMPERATURE) + " ";
        switch (i) {
        case 0:
            message += THERMAL_SENSOR_0;
            break;
        case 1:
            message += THERMAL_SENSOR_1;
            break;
        case 2:
            message += THERMAL_SENSOR_2;
            break;
        default:
            message += MSG_SENSOR_N + String(i + 1);
            break;
        }
        message += ": ";
        if (tempC > -100)
            message += String(tempC, 1) + " " + DEGREE + "C\n";
        else
            message += String(MSG_NO_DATA) + "\n";
    }
    return message;
}

float getRelayTemperature() {
    // Fetch the temperature in degrees Celsius for device index:
    float tempC = thermal_sensors.getTempCByIndex(THERMAL_SENSOR_FOR_RELAY);
    return roundToTenths(tempC);
}

float getMaxTemperatureOnSensors() {
    thermal_sensors.requestTemperatures();
    float max = -1000;
    for (int i = 0; i < thermal_sensors.getDeviceCount(); i++) {
        if (i == 2)
            continue;
            
        float tempC = thermal_sensors.getTempCByIndex(i);
        if (tempC > max) {
            max = tempC;
        }
    }
    return max;
}

float getMinTemperatureOnSensors() {
    thermal_sensors.requestTemperatures();
    float min = 1000;
    for (int i = 0; i < thermal_sensors.getDeviceCount(); i++) {
        if (i == 2)
            continue;
        
        float tempC = thermal_sensors.getTempCByIndex(i);
        if (tempC < min) {
            min = tempC;
        }
    }
    return min;
}

// Moisture sensors

String get_soil_moisture() {
    int soil_moisture_value = analogRead(MOISTURE_SENSOR_PIN);
    
    String message = "";
    message += String(MSG_MOISTURE_SENSOR_VALUE) + ": " + String(soil_moisture_value) + "\n";   //  Показывает значение датчика
    message += String(MSG_RELATIVE_MOISTURE_SENSOR_VALUE) + ": ";   //  Относительная влажность
    
    int soil_moisture_percent = map(soil_moisture_value, getAirMoisture(), getWaterMoisture(), 0, 100);

    if (soil_moisture_percent >= 100)
        message += "100";
    else if (soil_moisture_percent <= 0)
        message += "0";
    else if (soil_moisture_percent > 0 && soil_moisture_percent < 100)
        message += String(soil_moisture_percent);

    message += " %\n";
    return message;
}
