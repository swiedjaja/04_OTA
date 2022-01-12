// BasicOTA.ino
// from ArduinoOTA by Ivan Grokhotkov and Hristo Gochkov (built-in ESP32 library)/
// EPS32Cam have special build flag to support OTA: https://community.platformio.org/t/esp32-cam-ota-upload-problem/17179/13
//  board tested: Esp32cam, esp32doit-devkit-v1, esp12e
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#if defined(ESP8266)
  #include <ESP8266WiFi.h>
  #define ON 0
  #define OFF 1
  #define PIN_LED LED_BUILTIN
#elif defined(ESP32)
  #include <WiFi.h>
  #ifndef LED_BUILTIN // ESP32Cam
    #define ON 0
    #define OFF 1      
    #define LED_BUILTIN 33
  #else
    #define ON 1 // esp32doit-devkit-v1
    #define OFF 0      
  #endif
  #define PIN_LED LED_BUILTIN
#endif

const char* ssid = "Steff-IoT";
const char* password = "steffiot123";

void setup() {
  pinMode(PIN_LED, OUTPUT);
  Serial.begin(9600);
  Serial.println("Booting");
  Serial.printf("Board: %s, variant: %s\n", ARDUINO_BOARD, ARDUINO_VARIANT);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("Connection Failed! Rebooting...");
    delay(5000);
    ESP.restart();
  }  
  ArduinoOTA.setHostname("comp_eng_esp_iot");
  ArduinoOTA.begin();

  Serial.println("Ready");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.printf("RSSI: %d\n", WiFi.RSSI());
}

void loop() {
  Serial.println("Hello");
  digitalWrite(PIN_LED, ON);
  delay(100);
  digitalWrite(PIN_LED, OFF);
  delay(900);
  ArduinoOTA.handle();
}