#ifndef FIREBASE_MANAGER_H
#define FIREBASE_MANAGER_H

void connectFirebase();
void sendAllData(float temperatur,
                 float luftfeuchtigkeit,
                 String niederschlag,
                 String timestamp);


void sendSolarData(float voltage, float current, float power);

#endif