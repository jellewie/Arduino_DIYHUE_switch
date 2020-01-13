#define DIYHUE_LED LED_BUILTIN
#define DIYHUE_SerialEnabled                        //Disable to not send Serial debug feedback

#ifndef DIYHUE_bridgeIp
char DIYHUE_bridgeIp[] = "192.168.1.128";           //replace with the hue emulator device IP
#endif
#ifndef DIYHUE_switchType
const char* DIYHUE_switchType = "ZGPSwitch";        //Has the buttons {34, 16, 17, 18}
const byte DIYHUE_ZGPSwitch[4] = {34, 16, 17, 18};  //Http button ID to send to DIYHUE
#endif

bool DIYHUE_Register(String DIYHUE_mac) {
  String DIYHUE_TEMP = "/switch?devicetype=" + String(DIYHUE_switchType) + "&mac=" + DIYHUE_mac;    //register device
#ifdef DIYHUE_SerialEnabled
  Serial.println("DH: Register Request " + DIYHUE_mac);
#endif //DIYHUE_SerialEnabled
  return DIYHUE_Send(DIYHUE_TEMP);
}
bool DIYHUE_sendHttpRequest(String DIYHUE_mac, byte DIYHUE_button) {
  String DIYHUE_TEMP = "/switch?mac=" + DIYHUE_mac + "&button=" + DIYHUE_ZGPSwitch[DIYHUE_button - 1];  //Send buttons pressed
#ifdef DIYHUE_SerialEnabled
  Serial.println("DH: Button state send " + DIYHUE_mac + " " + DIYHUE_button);
#endif //DIYHUE_SerialEnabled
  return DIYHUE_Send(DIYHUE_TEMP);
}
bool DIYHUE_Send(String DIYHUE_url) {
  WiFiClient client;
  if (!client.connect(DIYHUE_bridgeIp, 80)) {           //(Try) connect to hub
#ifdef DIYHUE_SerialEnabled
    Serial.println("DH: #ERROR Cant connect to DIYHUE '" + String(DIYHUE_bridgeIp) + DIYHUE_url + "'");
#endif //DIYHUE_SerialEnabled
    DIYHUE_Blink(200, 10);                              //Can't connect to hub: Just blink a bit to show this error
    return false;
  } else {
    client.println("GET " + DIYHUE_url + " HTTP/1.1");  //Send the data to the ub
    client.println("Host: " + String(DIYHUE_bridgeIp));
    client.println("Connection: close");
    client.println();
    return true;
  }
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
void DIYHUE_Set_bridgeIp(String DIYHUE_TEMP_bridgeIp) {
  DIYHUE_TEMP_bridgeIp.toCharArray(DIYHUE_bridgeIp, DIYHUE_TEMP_bridgeIp.length() + 1);
}
String DIYHUE_Get_bridgeIp() {
  return DIYHUE_bridgeIp;
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
