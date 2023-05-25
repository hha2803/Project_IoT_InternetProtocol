#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <ESP_Mail_Client.h>
#include "DHT.h"
#include <LiquidCrystal_I2C.h>
#define DHTTYPE DHT11   // DHT 11
// #define WIFI_SSID "IoT LAB"
// #define WIFI_PASSWORD "kvt1ptit"

#define WIFI_SSID "HHA2803"
#define WIFI_PASSWORD "24082001"

// #define mqtt_server "192.168.3.191"
#define mqtt_server "192.168.0.102"
#define SMTP_HOST "smtp.gmail.com"
#define SMTP_PORT 465

#define AUTHOR_EMAIL "uyenthunguyen2408@gmail.com"
#define AUTHOR_PASSWORD "cybhnkowlqteetxc"
#define RECIPIENT_EMAIL "had19ptit@gmail.com"

float h,t,f;
SMTPSession smtp;

WiFiClient espClient;
PubSubClient client(espClient);

// DHT Sensor - GPIO 0 = D3 on ESP-12E NodeMCU board
const int DHTPin = 2;
const int lcdColumns = 20;
const int lcdRows = 4;
LiquidCrystal_I2C lcd(0x3F, lcdColumns, lcdRows);  
// Lamp - LED - GPIO 4 = D2 on ESP-12E NodeMCU board
const int lamp = 14;
// const int fan = 0;
//const int motor = 14; 
// Initialize DHT sensor.
DHT dht(DHTPin, DHTTYPE);

// Timers auxiliar variables
long now = millis();
long lastMeasure = 0;

// Don't change the function below. This functions connects your ESP8266 to your router

void send_email();
void smtpCallback(SMTP_Status status);
void callback(String topic, byte* message, unsigned int length);
void sensor_DHT11();
void setup_wifi();
void reconnect();

void setup() {
  // pinMode(lamp, OUTPUT);
  // pinMode(fan, OUTPUT);
  dht.begin();
  lcd.init();
  lcd.backlight();
  Serial.begin(115200);
  setup_wifi();
//  send_email();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);

}

// For this project, you don't need to change anything in the loop function. Basically it ensures that you ESP is connected to your broker
void loop() {

  if (!client.connected()) {
    reconnect();
  }
  if(!client.loop())
    client.connect("ESP8266Client");

  now = millis();
  // Publishes new temperature and humidity every 30 seconds
  if (now - lastMeasure > 3000) {
    lastMeasure = now;
    sensor_DHT11();  
  }
  
} 
