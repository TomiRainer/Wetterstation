#include <Arduino.h>
#include "wifi_manager.h"
#include "firebase_manager.h"
#include "sensor.h"

unsigned long lastUpdate = 0;
const unsigned long interval = 60000; // 1 Minute

void setup() {
    Serial.begin(115200);

    connectWiFi();
    connectFirebase();
    initSensors();
}

void loop() {
    if (millis() - lastUpdate >= interval) {
        lastUpdate = millis();

        float voltage, current, power;

        readSolar(voltage, current, power);

        Serial.println("------ SOLAR UPDATE ------");
        Serial.print("Spannung: ");
        Serial.print(voltage);
        Serial.println(" V");

        Serial.print("Strom: ");
        Serial.print(current);
        Serial.println(" mA");

        Serial.print("Leistung: ");
        Serial.print(power);
        Serial.println(" mW");

        sendSolarData(voltage, current, power);
    }
}