  #include <LiquidCrystal.h>
  
  // initialize the library by associating any needed LCD interface pin
  // with the arduino pin number it is connected to
  const int rs = A3, en = A5, d4 = A9, d5 = A10, d6 = A11, d7 = A12;
  LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

  #include <SPI.h>
  #include <MFRC522.h>
  #define RST_PIN         5           // Configurable, see typical pin layout above
  #define SS_PIN          53          // Configurable, see typical pin layout above
  MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance
  MFRC522::MIFARE_Key key;
  MFRC522::StatusCode status;
  
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
     
    lcd.begin(16, 2);
    // Print a message to the LCD.
    lcd.print("Hello, World!");



    
  
  }
  
  void loop() {
    // set the cursor to column 0, line 1
    // (note: line 1 is the second row, since counting begins with 0):
    lcd.setCursor(0, 1);
    // print the number of seconds since reset:
    lcd.print(millis() / 1000);
  }
