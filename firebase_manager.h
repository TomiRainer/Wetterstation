#ifndef FIREBASE_MANAGER_H
#define FIREBASE_MANAGER_H

#include <Firebase_ESP_Client.h>

extern FirebaseData fbdo;

void connectFirebase();
void sendSolarData(float voltage, float current, float power);

#endif