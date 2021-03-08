/*
ESPboy i2c scanner
for www.ESPboy.com project by RomanS
v1.0
*/

#include "ESPboyInit.h"
#include "ESPboyLED.h"
#include <Wire.h>

ESPboyInit myESPboy;
ESPboyLED myLED;


void prntAddr(uint8_t address, String toPrint){
 if (address<16) toPrint+="0";
   toPrint+=String(address, HEX);
   Serial.println(toPrint);
   myESPboy.tft.println(toPrint);
}


void setup(){
  Serial.begin(115200);
  myESPboy.begin("i2c scanner");
  myLED.begin(&myESPboy.mcp);
  myESPboy.tft.setTextSize(1);
}


void loop(){
  uint8_t error, address;
  uint8_t nDevices;

  myESPboy.tft.setTextColor(TFT_MAGENTA);
  myESPboy.tft.println(millis());
  myESPboy.tft.println(F("Scanning i2c..."));
  myESPboy.tft.setTextColor(TFT_YELLOW);
  Serial.println(F("\nScanning i2c..."));
  
    nDevices = 0;
    
    for(address = 8; address < 127; address++ ){
        Wire.beginTransmission(address);
        if (!Wire.endTransmission()){
            nDevices++;
            prntAddr(address, "Addr 0x");
        }
        else
          if (error==4) prntAddr(address, "Error addr 0x");
    }
    
    if (!nDevices) {
      myESPboy.tft.setTextColor(TFT_RED);
      myESPboy.tft.println(F("No I2C devices"));
      myESPboy.tft.setTextColor(TFT_YELLOW);
      Serial.println(F("No I2C devices"));
    }
      
    delay(3000);
    myESPboy.tft.fillScreen(TFT_BLACK);
    myESPboy.tft.setCursor(0,0);
}
