# Arduino_DIYHUE_switch
 DIYHUE hub: https://github.com/diyhue/diyHue

# What you need
Rasbarry with DIYHUE (and it's IP ofc.)
[ESP32](https://dl.espressif.com/dl/package_esp32_index.json)

# How it works
Set-up your wifi/connection stuff (I use my own [Arduino-WiFiManager](https://github.com/jellewie/Arduino-WiFiManager) for it 

fillin the "bridgeIp" with your DIYHUE_hub ip (Sitenote: must be reachable for the ESP ofc.)

Call "DIYHUE_Register(byte mac[6])" to tell the hub about this '4 button unit'

Call "DIYHUE_sendHttpRequest(byte mac[6], byte button)" to press a button (for the button in the app "34"=0 "16"=1 "17"=2 "18"=3)