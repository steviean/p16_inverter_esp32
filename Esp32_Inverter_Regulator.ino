#include <WiFi.h>          // ESP32 WiFi statt ESP8266WiFi
#include <PubSubClient.h>  // Für Home Assistant MQTT
#include "config.h"

WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  Serial.begin(115200);
  // Initialisierung der Kommunikation zum Inverter (ESP32 nutzt HardwareSerial 2)
  Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2); 

  setup_wifi();
  client.setServer(mqtt_server, 1883);
}

void setup_wifi() {
  delay(10);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) { delay(500); }
}

// Home Assistant MQTT Discovery
void sendDiscovery() {
  String topic = "homeassistant/sensor/inverter/config";
  String payload = "{\"name\": \"Inverter Power\", \"stat_t\": \"inverter/power\", \"unit_of_meas\": \"W\"}";
  client.publish(topic.c_str(), payload.c_str());
}

void loop() {
  if (!client.connected()) { reconnect(); }
  client.loop();

  // Hier kommt die Logik aus Bennys Projekt rein (Daten vom Inverter lesen)
  // Beispielhafter Export an Home Assistant:
  float currentPower = 150.5; // Platzhalter für echten Wert
  client.publish("inverter/power", String(currentPower).c_str());
  
  delay(5000); 
}

void reconnect() {
  while (!client.connected()) {
    if (client.connect("ESP32_Inverter", mqtt_user, mqtt_pass)) {
      sendDiscovery();
    } else { delay(5000); }
  }
}
