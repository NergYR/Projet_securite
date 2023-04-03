#include <Arduino.h>
#include <SPI.h>
#include <MFRC522.h>




class ScannerRFID {
  public:

      /// @brief Init mrfc522 with the given parameters
      /// @param ssPin 
      /// @param rstPin 
      ScannerRFID(int ssPin, int rstPin): mfrc522(ssPin, rstPin){}


      /// @brief Begin SPI and MRFC Connection
      void begin(){

        SPI.begin();
        mfrc522.PCD_Init();
      }
      /// @brief Scan the card and return the UUID
      /// @param uid 
      /// @return String var UUID of the card str format
      bool scanCard(String& uid){
  
        if (!mfrc522.PICC_IsNewCardPresent() || !mfrc522.PICC_ReadCardSerial()) {
            return false;
          }

          uid = "";
          for (byte i = 0; i < mfrc522.uid.size; i++) {
            if (mfrc522.uid.uidByte[i] < 0x10) {
              uid += "0";
            }
            uid += String(mfrc522.uid.uidByte[i], HEX);
          }
          uid.toUpperCase();
          return true;
      }
      
  private: 

    MFRC522 mfrc522;


};

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