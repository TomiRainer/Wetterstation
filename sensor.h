#ifndef SENSOR_H
#define SENSOR_H

void initSensors();
void readSolar(float &voltage, float &current, float &power);
void readClimate(float &temperature, float &humidity);
float readRain();

String berechneRegenZustand(float waterLevel);  

#endif