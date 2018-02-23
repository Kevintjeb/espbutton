#include <PubSubClient.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>
#include <WiFiManager.h> //https://github.com/tzapu/WiFiManager
#include "RestClient.h"
#include "environment.h"

WiFiClientSecure espClient;
PubSubClient client(espClient);

const char* getRandomClientId(){
  char * clientId  = (char*)malloc(sizeof(char) * 50);
  sprintf(clientId, "ESPBUTTON-");

  const long randomLong = random(0xffff);
  char randomValue[sizeof(long)];

  sprintf(randomValue, "%d",randomLong);
  strcat(clientId, randomValue);

  return clientId;
}

void setup() {
  WiFiManager wifiManager;
  wifiManager.autoConnect("ESPBUTTON", "button");
  client.setServer(mqttHost, mqttPort); 

  if (client.connect(getRandomClientId(), MQTTUSERNAME, MQTTPASSWORD)) {
    client.publish("ESPBUTTON", "hello world");
  }
  // ESP-01S goes to sleep. 
  // Wakes up when RESET is connection to GND
  // Returns to setup() when waking up.
  ESP.deepSleep(0, RF_DISABLED);
}

void loop() {
  //Does not reach the loop().
}