#include <SPI.h>
#include <MFRC522.h>

#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = A3, en = A5, d4 = A9, d5 = A10, d6 = A11, d7 = A12;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

#define RST_PIN         5          // Configurable, see typical pin layout above
#define SS_PIN          53          // Configurable, see typical pin layout above
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance
MFRC522::MIFARE_Key key;
MFRC522::StatusCode status;
//*****************************************************************************************//







void setup() {
      Serial.begin(9600);                                           // Initialize serial communications with the PC
      SPI.begin();                                                  // Init SPI bus
      mfrc522.PCD_Init();                                              // Init MFRC522 card
      Serial.println(F("Read personal data on a MIFARE PICC:"));    //shows in serial that it is ready to read


   pinMode(A14,OUTPUT);
   pinMode(A13,OUTPUT);
   pinMode(A4,OUTPUT);
   pinMode(A0,OUTPUT);
   pinMode(A2,OUTPUT);
   pinMode(A1,OUTPUT);
   
   digitalWrite(A14,LOW); 
   digitalWrite(A13,HIGH); 
   digitalWrite(A4,LOW); 
   digitalWrite(A0,LOW);
   digitalWrite(A2,LOW);
   digitalWrite(A1,HIGH);

	mfrc522.PD_DuCmpVersionToSerial();	// Show details of PCD - MFRC522 Card Reader details

   
   lcd.begin(16, 2);
   // Print a message to the LCD.
   lcd.print("Rfid Reader");
}
//*****************************************************************************************//



void loop() {
      // Prepare key - all keys are set to FFFFFFFFFFFFh at chip delivery from the factory.
      for (byte i = 0; i < 6; i++) key.keyByte[i] = 0xFF;
      byte block;
      byte len;
      //-------------------------------------------
      // Reset the loop if no new card present on the sensor/reader. This saves the entire process when idle.
      if ( ! mfrc522.PICC_IsNewCardPresent()) {
        return;
      }
      // Select one of the cards
      if ( ! mfrc522.PICC_ReadCardSerial()) {
        return;
      }
      Serial.println(F("**Card Detected:**"));
      byte buffer1[18];
      block = 4;
      len = 18;
      status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, 4, &key, &(mfrc522.uid));
      if (status != MFRC522::STATUS_OK) {
        Serial.print(F("Authentication failed: "));
        Serial.println(mfrc522.GetStatusCodeName(status));
        return;
      }
      status = mfrc522.MIFARE_Read(block, buffer1, &len);
      if (status != MFRC522::STATUS_OK) {
        Serial.print(F("Reading failed: "));
        Serial.println(mfrc522.GetStatusCodeName(status));
        return;
      }
      String value = "";
      for (uint8_t i = 0; i < 16; i++)
      {
        value += (char)buffer1[i];
      }
      value.trim();
      Serial.print(value);
      Serial.println(F("\n**End Reading**\n"));
      delay(1000);
      mfrc522.PICC_HaltA();
      mfrc522.PCD_StopCrypto1();

      lcd.setCursor(0,1);
      lcd.print(value);
}
