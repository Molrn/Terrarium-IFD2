#include "ESP.h"


MQTTClient client;
WiFiClient wificlient;
const char ssid[] = "MSIARTHUR&";
const char pass[] = "11111111";
const char hostname[16] = "192.168.137.1";
const char* mqqtTopicIN = "/IFD2/IN";
const char* mqqtTopicOUT = "INFOOUT";
String inString;
unsigned long lastMillis = 0;

void connect() {
    Serial.println("[DEBUG#ESP Checking wifi...]");
    while (WiFi.status() != WL_CONNECTED) {
        Serial.println(".");
        delay(100);
    }
    Serial.println("[DEBUG#ESP Wifi connected, MQTT connecting...]");
    while (!client.connect("NGAUD", "try", "try")) {
        Serial.println("+");
        delay(100);
    }
    Serial.println("[DEBUG#ESP MQTT connected!]");
    client.subscribe(mqqtTopicIN);  
}

void messageReceived(String &topic, String &payload) {
    Serial.println("[DEBUG#ESP Forwarding to MEGA Incoming message from MQTT on topic: "); 
    Serial.println(topic);
    Serial.println(" - "); 
    Serial.println(payload);
    Serial.println("]");
}

void serialEvent() {
    while (Serial.available()) {
        char inChar = Serial.read();
        inString += inChar;
        if (inChar == ']') {
            client.publish(mqqtTopicOUT, inString);
            inString = "";
        }
    }
  
}

void alive() {
    if (millis() - lastMillis > 5000) {
        lastMillis = millis();
        client.publish("/esp/alive", "coucou");
    }
}

void setup() {
    Serial.begin(115200);//vers ATMega
    Serial.println("[DEBUG#ESP Welcome]");
    WiFi.begin(ssid, pass);
    client.begin(hostname, 1883, wificlient);
    client.onMessage(messageReceived);
    connect();
}

void loop() {  
    client.loop();
    if (!client.connected()) {
        connect();
    }
    serialEvent();
    alive();
}




