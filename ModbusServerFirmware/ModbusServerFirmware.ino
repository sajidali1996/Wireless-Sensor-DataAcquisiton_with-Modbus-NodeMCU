/*
  Modbus-Arduino Example - Test Led (Modbus IP ESP8266)
  Control a Led on GPIO0 pin using Write Single Coil Modbus Function 
  Original library
  Copyright by André Sarmento Barbosa
  http://github.com/andresarmento/modbus-arduino

  Current version
  (c)2017 Alexander Emelianov (a.m.emelianov@gmail.com)
  https://github.com/emelianov/modbus-esp8266
*/

#ifdef ESP8266
 #include <ESP8266WiFi.h>
#else //ESP32
 #include <WiFi.h>
#endif
#include <ModbusIP_ESP8266.h>

//Modbus Registers Offsets
const int LED_COIL = 100;
//Used Pins
const int ledPin = D0; //GPIO0
const int Holding_reg1 = 100;
const int Holding_reg2=150;
//ModbusIP object
ModbusIP mb;
  
void setup() {
  Serial.begin(115200);
 pinMode(D2, INPUT);
  WiFi.begin("HUAWEI-301", "708090100");
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
 
  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  mb.server();

  pinMode(ledPin, OUTPUT);
  // before using holding register add them here
  mb.addHreg(Holding_reg1, 0xFFFF);
  mb.addHreg(Holding_reg2, 0xFFFF);

  //To read these values on matlab or any other place use address_here+1
  //e.g, if address here is 100 use 101 to call that register
  mb.addCoil(LED_COIL);
}
 
void loop() {
   //Call once inside loop() - all magic here
   mb.task();

   //Attach ledPin to LED_COIL register
   digitalWrite(ledPin, mb.Coil(LED_COIL));
   mb.Hreg(100,random(0,10)); 
   mb.Hreg(150,digitalRead(D2));
   Serial.println(digitalRead(D2));
   delay(10);
}
