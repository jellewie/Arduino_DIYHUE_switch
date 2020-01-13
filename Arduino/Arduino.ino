/*
  Program written by JelleWho
  Board: https://dl.espressif.com/dl/package_esp32_index.json
  
  Dependencies (NOT INCLUDED!!, INCLUDE YOUR OWN OR INCLUDE IT YOURSELF)
  https://github.com/jellewie/Arduino-WiFiManager
*/
#include <WiFi.h>

byte mac[6];

void setup() {
  WiFiManager_Start();                    //Setup all WIFI stuff (NOT INCLUDED!!, INCLUDE YOUR OWN OR INCLUDE IT YOURSELF)
  WiFi.macAddress(mac);                   //Save this device it's mac adress
  DIYHUE_Register(DIYHUE_macToStr(mac));  //Tell the hub that we exist (It problably isn't good to keep doing this, change if you reboot the ESP a lot)
}
void loop() {
  for (byte i = 0; i < 4; i++) {          //For each button
    DIYHUE_sendHttpRequest(DIYHUE_macToStr(mac), i + 1); //Send Http request with max and appropriate buttonID (Also returns "TRUE" if it got send)
    delay(100);                           //My hub doesn't seem to like updates being hammered into it, this delay will just make sure we send more updates a bit later
  }
  delay(60000);                           //Just here to pause the loop for 1 min
}
