#include <Arduino.h>
#include <WiFi.h>
#include "config.h"
#include "wifi_manager.h"

void connectWiFi() {
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    Serial.print("Verbinde WLAN");

    while (WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        delay(500);
    }

    Serial.println("\nWLAN verbunden ✔");
}