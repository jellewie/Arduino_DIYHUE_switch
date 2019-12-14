#define DIYHUE_LED LED_BUILTIN

#ifndef bridgeIp
const char* DIYHUE_bridgeIp = "192.168.1.128";    //replace with the hue emulator device IP
#endif
#ifndef DIYHUE_switchType
const char* DIYHUE_switchType = "ZGPSwitch";     //Has the buttons {34, 16, 17, 18}
#endif

void DIYHUE_Register(String DIYHUE_mac) {
  WiFiClient client;
  if (!client.connect(DIYHUE_bridgeIp, 80)) {    //###Registering device
    DIYHUE_Blink(200, 10);                //Can't connect to hub: Just blink a bit to show this error
  } else {                                //Code to execute if connected
    String DIYHUE_url = "/switch?devicetype=" + (String)DIYHUE_switchType + "&mac=" + DIYHUE_mac;    //register device
    client.print(String("GET ") + DIYHUE_url + " HTTP/1.1\r\n" +
                 "Host: " + DIYHUE_bridgeIp + "\r\n" +
                 "Connection: close\r\n\r\n");
  }
}
void DIYHUE_sendHttpRequest(String DIYHUE_mac, int DIYHUE_button) {
  WiFiClient client;
  digitalWrite(DIYHUE_LED, HIGH);
  if (!client.connect(DIYHUE_bridgeIp, 80)) {    //###Registering device
    DIYHUE_Blink(200, 10); //Can't connect to hub: Just blink a bit to show this error
  } else {
    String DIYHUE_url = "/switch?mac=" + DIYHUE_mac + "&button=" + DIYHUE_button;
    client.print(String("GET ") + DIYHUE_url + " HTTP/1.1\r\n" +
                 "Host: " + DIYHUE_bridgeIp + "\r\n" +
                 "Connection: close\r\n\r\n");
  }
  digitalWrite(DIYHUE_LED, LOW);
}
String DIYHUE_macToStr(const byte* DIYHUE_mac) {
  String DIYHUE_result;
  for (int i = 0; i < 6; ++i) {
    DIYHUE_result += String(DIYHUE_mac[i], 16);
    if (i < 5)
      DIYHUE_result += ':';
  }
  return DIYHUE_result;
}
void DIYHUE_Blink(int DIYHUE_DelayMS, byte DIYHUE_amount) {
  for (byte i = 0; i < DIYHUE_amount; i++) {
    digitalWrite(DIYHUE_LED, !digitalRead(DIYHUE_LED)); //Blink LED
    delay(DIYHUE_DelayMS);
  }
  digitalWrite(DIYHUE_LED, LOW);
}
//void DIYHUE_Sleep() {
//  yield();
//  delay(100);    //Just in case there still things to handle off in the background
//
//  uint64_t Mask = 0xF00000000;
//
//  //  uint32_t MaskTemp = Mask >> 32;
//  //  unsigned long long1 = (unsigned long)((MaskTemp & 0xFFFF0000) >> 16 );
//  //  unsigned long long2 = (unsigned long)((MaskTemp & 0x0000FFFF));
//  //  String hex = String(long1, HEX) + String(long2, HEX); // six octets
//  //  Serial.print("mask=");
//  //  Serial.print(hex);
//  //  Serial.println("_");
//
//  esp_sleep_enable_ext1_wakeup(Mask, ESP_EXT1_WAKEUP_ANY_HIGH); //Set how the module can be woken up
//  esp_deep_sleep_start();                             //go right now into sleep mode
//}
