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
#define TOKEN "A1E-DEb67qiQPtT7MHMMMoK9ldh2L4FfwP" // Your Ubidots TOKEN
#define WIFINAME "RoboIndiaExt" //Your SSID
#define WIFIPASS "786#robo" // Your Wifi Pass
/*#define MQTT_CLIENT_NAME " client_test_1"
*/


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
     temp = sensor.readTemperature();
     Serial.println(temp);
     /*temp=sensor.getTempCByIndex(0);
  
  //Serial.println(sensor.getTempCByIndex(0));
  // Publish values to 2 different data sources*/
  
  client.add("temperature", temp); //Insert your variable Labels and the value to be sent
  client.ubidotsPublish("esp8266");
 /* client.add("temperature", temp);*/
  /*client.add("more-stuff", 120.2);
  client.ubidotsPublish("source2");*/
  /*String poster= "{\"temperature\": "+String(tem)+"}\r\n\r\n";
  int len=poster.length();
  Serial.println(poster);
  String post = "POST /api/v1.6/devices/esp8266/?token="+TOKEN+" HTTP/1.1\r\n";
    */     
  /*char context[25];
  sprintf(context, "\"lat\":1.2343, \"lng\":132.1233");
  client.add(temperature, 1, temp);
  client.sendAll();*/
  client.loop();
  delay(500);
  }
