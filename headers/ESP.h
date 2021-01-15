#include <Arduino.h>
#include <string.h>
#include <ESP8266WiFi.h>
#include <MQTT.h>

// connect l'esp au broker MQTT
void connect();

// reception des messages du MQTT
void messageReceived(String &topic, String &payload);

//publie les données sur le MQTT
void serialEvent();

// envoie d'un debug sur le MQTT
void alive();

void setup();

void loop();
