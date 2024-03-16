#include "moisture_sensor.h"

int AIR_MOISTURE_VALUE = 856;      //  Значение датчика в воздухе
int WATER_MOISTURE_VALUE = 488;    //  Значение датчика в воде

void setAirMoisture(int value){
    AIR_MOISTURE_VALUE = value;
}

void setWaterMoisture(int value){
    WATER_MOISTURE_VALUE = value;
}

String getSoilMoisture() {
    int soilMoistureValue = analogRead(MOISTURE_SENSOR_PIN);
    
    String message = "";
    message += MSG_MOISTURE_SENSOR_VALUE + String(soilMoistureValue) + "\n";   //  Показывает значение датчика
    message += MSG_RELATIVE_MOISTURE_SENSOR_VALUE;  //  Относительная влажность
    
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
