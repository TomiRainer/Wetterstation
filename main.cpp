#include <Arduino.h>
#include "wifi_manager.h"
#include "firebase_manager.h"
#include "sensor.h"
#include <time.h>

const char* ntpServer = "pool.ntp.org";
const long gmtOffset_sec = 3600;
const int daylightOffset_sec = 3600;

void initTime() {
    configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
}

String getTimestamp() {
    time_t now = time(nullptr);
    struct tm *timeinfo = localtime(&now);
    char buffer[30];
    strftime(buffer, sizeof(buffer), "%d-%m-%Y | %H:%M Uhr", timeinfo);
    return String(buffer);
}

unsigned long lastUpdate = 0;
const unsigned long interval = 60000; // 1 Minute

void setup() {
    Serial.begin(115200);

    connectWiFi();
    connectFirebase();
    initSensors();
    initTime();
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

        float temperatur, luftfeuchtigkeit;
        float rainLevel;

        readClimate(temperatur, luftfeuchtigkeit);
        rainLevel = readRain();

        String niederschlag = berechneRegenZustand(rainLevel);
        String timestamp = getTimestamp();  // aus time_manager

        sendAllData(temperatur,
                    luftfeuchtigkeit,
                    niederschlag,
                    timestamp);
    }
}