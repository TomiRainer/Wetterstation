#include <Arduino.h>
#include <Firebase_ESP_Client.h>
#include "config.h"
#include "firebase_manager.h"

static int historyIndex = 0;
const int MAX_HISTORY = 5;

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


void sendAllData(float temperatur,
                 float luftfeuchtigkeit,
                 String niederschlag,
                 String timestamp) {

    // 1️⃣ Aktueller Zustand
    Firebase.RTDB.setFloat(&fbdo, "/DHT11/temperatur", temperatur);
    Firebase.RTDB.setFloat(&fbdo, "/DHT11/luftfeuchtigkeit", luftfeuchtigkeit);
    Firebase.RTDB.setString(&fbdo, "/sensorData/aktuellerZustand/niederschlag", niederschlag);
    Firebase.RTDB.setString(&fbdo, "/sensorData/aktuellerZustand/zeit", timestamp);

    // 2️⃣ History (Ringpuffer)

    String basePath = "/history/";
    basePath += String(historyIndex);

    String path;

    path = basePath;
    path += "/temperatur";
    Firebase.RTDB.setFloat(&fbdo, path.c_str(), temperatur);

    path = basePath;
    path += "/luftfeuchtigkeit";
    Firebase.RTDB.setFloat(&fbdo, path.c_str(), luftfeuchtigkeit);

    path = basePath;
    path += "/niederschlag";
    Firebase.RTDB.setString(&fbdo, path.c_str(), niederschlag);

    path = basePath;
    path += "/zeit";
    Firebase.RTDB.setString(&fbdo, path.c_str(), timestamp);

    historyIndex = (historyIndex + 1) % MAX_HISTORY;
}