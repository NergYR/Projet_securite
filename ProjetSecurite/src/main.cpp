#include <Arduino.h>
#include <SPI.h>
#include <MFRC522.h>
#include <capteur.cpp>





void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  ScannerRFID begin();

}


void loop() {
  // put your main code here, to run repeatedly:
  String uid;
  ScannerRFID scannerRFID(10, 9);
  if(scannerRFID.scanCard(uid)){
    Serial.println("Card detected: ");
    Serial.println(uid);
  }


}