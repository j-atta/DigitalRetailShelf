/*
 * Controls the shelving module
 */

// CONSTANTS
#define ENABLE_GxEPD2_GFX 0

// INCLUDES
#include <GxEPD2_BW.h>
#include <Fonts/FreeMonoBold9pt7b.h>
#include <WiFi.h>
#include <HTTPClient.h>

// GLOBAL VARIABLES
GxEPD2_BW<GxEPD2_213_B74, GxEPD2_213_B74::HEIGHT> display(GxEPD2_213_B74(SS, 17, 16, 4));
const char TextToDisplay[] = "";
const char* ssid = "NetComm 9343";
const char* password = "harelagehi";
String check = "check_product_info";

String URL = "http://192.168.20.18/retailshelf/index.php";

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  setupWifi(ssid, password);
  HTTPClient http;
  http.begin(URL);
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  int response_code = http.POST(check);

  if(response_code > 0){
        Serial.println("HTTP code " + String(response_code));
  }

  if(response_code == 200) {
    Serial.print("Valid");
  }
  display.init(115200, true, 2, false);
  printText(http.getString().c_str());
}

void loop() {
  // put your main code here, to run repeatedly:
   if(WiFi.status()== WL_CONNECTED) {
    // Do stuff here
   }
   else {
    Serial.println("WIFI connection error");
   }
} 

void printText(const char message[]) {
  display.setRotation(1);
  display.setFont(&FreeMonoBold9pt7b);
  display.setTextColor(GxEPD_BLACK);
  int16_t tbx, tby; uint16_t tbw, tbh;
  display.getTextBounds(message, 0, 0, &tbx, &tby, &tbw, &tbh);
  // center the bounding box by transposition of the origin:
  uint16_t x = ((display.width() - tbw) / 2) - tbx;
  uint16_t y = ((display.height() - tbh) / 2) - tby;
  display.setFullWindow();
  display.firstPage();
  do
  {
    display.fillScreen(GxEPD_WHITE);
    display.setCursor(x, y);
    display.print(message);
  }
  while (display.nextPage());
}

void setupWifi(const char* initName, const char* initPassword ) {
   WiFi.begin(ssid, password);
   Serial.print("Connecting...");
  while (WiFi.status() != WL_CONNECTED) { //Check for the connection
    delay(500);
    Serial.print(".");
  }
}