#include <Arduino.h>
#include <capteur.cpp>
#include <afficheur.cpp>

ScannerRFID scannerRFID(10, 9);



void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  scannerRFID.begin();

}


void loop() {

  // put your main code here, to run repeatedly:

  if (scannerRFID.scanCard()) {
    Serial.println(scannerRFID.userinfo.c_str());
  }





}