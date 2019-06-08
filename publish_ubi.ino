/****************************************
 * Include Libraries
 ****************************************/
#include "UbidotsESPMQTT.h"
#include "Adafruit_Si7021.h"
#include <PubSubClient.h>

Adafruit_Si7021 sensor = Adafruit_Si7021();
#include <ESP8266WiFi.h>
/****************************************
 * Define Constants
 ****************************************/
#define TOKEN "...." // Your Ubidots TOKEN
#define WIFINAME "...." //Your SSID
#define WIFIPASS "...." // Your Wifi Pass

Ubidots client(TOKEN);
float temp=0.0;
/****************************************
 * Auxiliar Functions
 ****************************************/

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i=0;i<length;i++) 
  {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}

/****************************************
 * Main Functions
 ****************************************/

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  client.setDebug(true); // Pass a true or false bool value to activate debug messages
  client.wifiConnection(WIFINAME, WIFIPASS);
  Serial.println("connected");
  client.begin(callback);
  if(!sensor.begin())
  {Serial.println("did not find sensor si7021");
  while(true);
    }
  }

void loop() {
  // put your main code here, to run repeatedly:
  if(!client.connected()){
      client.reconnect();
      }
     temp = sensor.readTemperature();//reading temperature from sensor
     Serial.println(temp);
  
  client.add("temperature", temp); //Insert your variable Labels and the value to be sent
  client.ubidotsPublish("esp8266");
  client.loop();
  delay(500);
  }
