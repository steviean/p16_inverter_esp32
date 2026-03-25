// WLAN Einstellungen
const char* ssid = "DEIN_WLAN_NAME";
const char* password = "DEIN_PASSWORT";

// MQTT Einstellungen für Home Assistant
const char* mqtt_server = "192.168.x.x"; // IP deines HA-Servers
const char* mqtt_user = "mqtt_user";
const char* mqtt_pass = "mqtt_password";

// Pinbelegung ESP32 (Beispiel: HardwareSerial 2)
#define RXD2 16
#define TXD2 17
