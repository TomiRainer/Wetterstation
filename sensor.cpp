#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_INA219.h>
#include "config.h"
#include "sensor.h"
#include <DHT.h>
#include "config.h"

#define DHTTYPE DHT11

DHT dht(DHT_PIN, DHTTYPE);
String berechneRegenZustand(float waterLevel);
Adafruit_INA219 ina219;

void initSensors() {
    dht.begin();
    Wire.begin(I2C_SDA, I2C_SCL);

    if (!ina219.begin()) {
        Serial.println("INA219 nicht gefunden!");
        while (1);
    }

    Serial.println("INA219 gestartet ✔");
}

void readSolar(float &voltage, float &current, float &power) {
    voltage = ina219.getBusVoltage_V();
    current = ina219.getCurrent_mA();
    power   = ina219.getPower_mW();
}

void readClimate(float &temperature, float &humidity) {
    temperature = dht.readTemperature();
    humidity = dht.readHumidity();
}

float readRain() {
    int rainRaw = analogRead(RAIN_SENSOR_PIN);
    return (rainRaw / 4095.0) * 16.0;
}


String berechneRegenZustand(float waterLevel) {
    if (waterLevel < 1) return "Kein Regen";
    else if (waterLevel < 2) return "Leichter Regen";
    else if (waterLevel < 4) return "Regen";
    else return "Starker Regen";
}


