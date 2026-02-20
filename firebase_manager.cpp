#include <Arduino.h>
#include <Firebase_ESP_Client.h>
#include "config.h"
#include "firebase_manager.h"

FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

void connectFirebase() {
    config.database_url = DATABASE_URL;
    config.signer.tokens.legacy_token = DATABASE_SECRET;

    Firebase.begin(&config, &auth);
    Firebase.reconnectWiFi(true);

    Serial.println("Firebase verbunden ✔");
}

void sendSolarData(float voltage, float current, float power) {
    Firebase.RTDB.setFloat(&fbdo, "/Solarspannung/Spannung_V", voltage);
    Firebase.RTDB.setFloat(&fbdo, "/Solarspannung/Strom_mA", current);
    Firebase.RTDB.setFloat(&fbdo, "/Solarspannung/Leistung_mW", power);
}