#define THINGER_SERVER "<your Thinger server ip or domain name "
#include <ESP8266WiFi.h>
#include <ThingerESP8266.h>

#define USERNAME "<your Thinger server username>"
#define DEVICE_ID "<your device ID, create it in your Thinger server interface>"
#define DEVICE_CREDENTIAL "<your device credential>"

#define SSID "<your WiFi SSID>"
#define SSID_PASSWORD "<your Wifi password>"

ThingerESP8266 thing(USERNAME, DEVICE_ID, DEVICE_CREDENTIAL);

int outputpin = A0; 

void setup() {
  //pinMode(BUILTIN_LED, OUTPUT);
  pinMode(D1, OUTPUT); //GREEN LED
  pinMode(D6, OUTPUT); //RED LED
  
  
  //connect to wifi with the given credentials
  thing.add_wifi(SSID, SSID_PASSWORD);

  //creating resources that to be managed by thinger server
  thing["greenled"] << digitalPin(D1);
  thing["redled"] << digitalPin(D6);

  //reading temprature value from analog L35 senson on pin A0
  
  
  thing["temperature"] >> [](pson& out){
  int analogValue = analogRead(outputpin);
  float millivolts = (analogValue/1024.0) * 3300; //3300 is the voltage provided by NodeMCU
  int celsius = millivolts/10; // taking the value in int so that it will leave the parts after decimal
  //Serial.print("in DegreeC=   ");
  Serial.println(analogRead(outputpin));
  out = celsius;
  };
 
}

void loop() {
  thing.handle();
}
