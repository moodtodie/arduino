#include "moisture_sensor.h"

String getSoilMoisture() {
    int soilMoistureValue = analogRead(MOISTURE_SENSOR_PIN);
    
    String message = "";
    message += "Moisture sensor value: " + String(soilMoistureValue) + "\n";   //  Показывает значение датчика
    message += "Relative soil moisture: ";  //  Относительная влажность
    
    int soilMoisturePercent = map(soilMoistureValue, AIR_MOISTURE_VALUE, WATER_MOISTURE_VALUE, 0, 100);

    if (soilMoisturePercent >= 100)
        message += "100";
    else if (soilMoisturePercent <= 0)
        message += "0";
    else if (soilMoisturePercent > 0 && soilMoisturePercent < 100)
        message += String(soilMoisturePercent);

    message += " %\n";
    return message;
}
