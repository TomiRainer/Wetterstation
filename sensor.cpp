#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_INA219.h>
#include "config.h"
#include "sensor.h"

Adafruit_INA219 ina219;

void initSensors() {
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