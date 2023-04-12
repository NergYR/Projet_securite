#include <MFRC522.h>
#include <iostream>
#include <vector>

using namespace std;

class ScannerRFID {
  private: 
  public:
  
    
      /// @brief User struct
      /// @brief Find the user with the given uid    
      /// @param uid
      /// @return the name and surname of the user
      string find_user(string uid){
        struct User {
          string uid;
          string name;
          string surname;
          string id;
        };
        vector<User> users = {
          {"00000000", "Khabib", "Nurmagomedov", "1"},
          {"00000001", "Cedric", "Doumbe", "2"},
          {"00000002", "Conor", "McGregor", "3"},
          {"00000003", "Mike", "Tyson", "4"},
          {"00000004", "Mohamed", "Ali", "5"},
          {"00000005", "Jhon", "Jones", "6"},
          {"00000006", "Cyril", "Gane", "7"}
        };
        for (const auto& user : users) {
          if (user.uid == uid) {
              // return the name and surname of the user
              return user.name + " " + user.surname;
            }
        }

          // user with the given uid not found
          return "";
      }
      string userinfo;
      int ssPin;
      int rstPin;
      MFRC522 mfrc522;

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
      /// @return String var userinfo of the card string format
      bool scanCard(){
  
        if (!mfrc522.PICC_IsNewCardPresent() || !mfrc522.PICC_ReadCardSerial()) {
            return false;
          }

          string uid = "";
          for (byte i = 0; i < mfrc522.uid.size; i++) {
            if (mfrc522.uid.uidByte[i] < 0x10) {
              uid += "0";
            }
            uid += string(mfrc522.uid.uidByte[i], HEX);
          }

          userinfo = find_user(uid);

          return true;
      }
      
  
    };