/**********************************************************************
  Filename    : Drive LiquidCrystal I2C to display characters
  Description : I2C is used to control the display characters of LCD1602.
  Auther      : www.freenove.com
  Modification: 2024/06/19
**********************************************************************/
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

#define SDA 13                    //Define SDA pins
#define SCL 14                    //Define SCL pins

/*
 * note:If lcd1602 uses PCF8574T, IIC's address is 0x27,
 *      or lcd1602 uses PCF8574AT, IIC's address is 0x3F.
*/
LiquidCrystal_I2C lcd(0x27,16,2); 

String inputString = "N/A";      //a String to hold incoming data
bool stringComplete = false;  // whether the string is complete

void setup() {

  Serial.begin(115200);

  Serial.println(String("\nESP32 initialization completed!\n")
                + String("Please input some characters,\n")
                + String("select \"Newline\" below and click send button. \n"));

  
  Wire.begin(SDA, SCL);           // attach the IIC pin
  if (!i2CAddrTest(0x27)) {
    lcd = LiquidCrystal_I2C(0x3F, 16, 2);
  }
  lcd.init();                     // LCD driver initialization
  lcd.backlight();                // Open the backlight
  lcd.setCursor(0,0);             // Move the cursor to row 0, column 0
  lcd.print(" input : ");     // The print content is displayed on the LCD

  
}

void loop() {

  if (Serial.available()) {         // judge whether data has been received
    char inChar = Serial.read();         // read one character
    inputString += char2moorse(inChar);
    inputString += inChar;
    if (inChar == '\n') {
      stringComplete = true;
    }
  }

  if (stringComplete) {
    Serial.printf("inputString: %s \n", inputString);
    inputString = "";
    stringComplete = false;
  }

  /*
  if (!stringComplete) {
    Serial.printf("inputString: %s \n", inputString);
    //inputString = "not";
    stringComplete = false;
  }
  */

  delay(1000);

  
  lcd.setCursor(0,1);             // Move the cursor to row 1, column 0
  lcd.print(inputString);          // The count is displayed every second
  //lcd.print(millis() / 1000);
  lcd.print(" ");
  delay(1000);
  
}

bool i2CAddrTest(uint8_t addr) {
  Wire.beginTransmission(addr);
  if (Wire.endTransmission() == 0) {
    return true;
  }
  return false;
}

String char2moorse(char myChar) {

  if (myChar == 'a' || myChar == 'A') { return ".- "; }

    if (myChar == 'b' || myChar == 'B') { return "-... "; }
  if (myChar == 'c' || myChar == 'C') { return "-.-. "; }
  if (myChar == 'd' || myChar == 'D') { return "-... "; }
  if (myChar == 'e' || myChar == 'E') { return ". "; }
  if (myChar == 'f' || myChar == 'F') { return "...-. "; }
  if (myChar == 'g' || myChar == 'G') { return "--. "; }
  if (myChar == 'h' || myChar == 'H') { return "... "; }
    if (myChar == 'i' || myChar == 'I') { return "... "; }
  if (myChar == 'j' || myChar == 'J') { return ".-- "; }
  if (myChar == 'k' || myChar == 'K') { return "-.- "; }
  if (myChar == 'l' || myChar == 'L') { return ".-... "; }
  if (myChar == 'm' || myChar == 'M') { return "-- "; }
  if (myChar == 'n' || myChar == 'N') { return "-. "; }
  if (myChar == 'o' || myChar == 'O') { return "--- "; }
  if (myChar == 'p' || myChar == 'P') { return ".--. "; }
  if (myChar == 'q' || myChar == 'Q') { return "--.- "; }
  if (myChar == 'r' || myChar == 'R') { return ".-. "; }
  if (myChar == 's' || myChar == 'S') { return "... "; }
  if (myChar == 't' || myChar == 'T') { return "- "; }
  if (myChar == 'u' || myChar == 'U') { return "...- "; }
  if (myChar == 'v' || myChar == 'V') { return "...- "; }
  if (myChar == 'w' || myChar == 'W') { return ".-- "; }
  if (myChar == 'x' || myChar == 'X') { return "-.--- "; }
    if (myChar == 'y' || myChar == 'Y') { return "-.-- "; }
  if (myChar == 'z' || myChar == 'Z') { return "--... "; }


  if (myChar == 'å' || myChar == 'Å') { return ".--.- "; }
  if (myChar == 'ä' || myChar == 'Ä') { return ".-.- "; }
  if (myChar == 'ö' || myChar == 'Ö') { return "--. "; }

  

  
}