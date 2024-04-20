#include "DS18B20.h"

OneWire ow(TEMPERATURE_SENSOR_PIN);
DallasTemperature thermal_sensors(&ow);

void init_thermal_sensors() {
    pinMode(TEMPERATURE_SENSOR_PIN, INPUT);
    thermal_sensors.begin();
}

uint8_t getThermalSensorsCount() {
    return thermal_sensors.getDeviceCount();
}

// int getMaxTemperature() {
//     thermal_sensors.requestTemperatures();
//     int max = -1000;
//     for (int i = 0; i < thermal_sensors.getDeviceCount(); i++) {
//         float tempC = thermal_sensors.getTempCByIndex(i);
//         if (tempC > max) {
//             max = tempC;
//         }
//     }
//     return max;
// }

String getTemperature() {
    // Send the command for all devices on the bus to perform a temperature conversion:
    thermal_sensors.requestTemperatures();
    String message = "";
    for (int i = 0; i < thermal_sensors.getDeviceCount(); i++)
    {
        // Fetch the temperature in degrees Celsius for device index:
        float tempC = thermal_sensors.getTempCByIndex(i); // the index 0 refers to the first device

        // Print the temperature in Celsius in the Serial Monitor:
        message += String(MSG_TEMPERATURE) + " ";
        switch (i)
        {
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
            message += String(tempC) + " \xC2\xB0" + "C\n";
        else
            message += String(MSG_NO_DATA) + "\n";
    }
    return message;
}
