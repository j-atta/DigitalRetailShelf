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
const char* ssid = "NetComm 9343";
const char* password = "harelagehi";
String URL = "http://192.168.20.18/retailshelf/index.php";

// INFO FOR DISPLAY
// const char productName[];
// const char productBrand[];
// int productPrice;
// int productPromoPrice;
// int productPromoStatus;
// int productSOH;

void setup() {
  // Initialisation
  Serial.begin(115200);
  display.init(115200, true, 2, false);
  setupWifi(ssid, password);
  printText();
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

void printText() {
  display.setRotation(1);
  display.setFont(&FreeMonoBold9pt7b);
  display.setTextColor(GxEPD_BLACK);
  display.firstPage();
  do
  {
    display.fillScreen(GxEPD_WHITE);
    display.setCursor(0, 20);
    display.println(String("SKU: " + getProductNumberFromServer()).c_str());
    display.println(String("Name: " + getProductNameFromServer()).c_str());
    display.println(String("Brand: " + getProductBrandFromServer()).c_str());
    display.println(String("Price: $" + getProductPriceFromServer()).c_str());

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

String getProductNumberFromServer() {
  HTTPClient http;
  http.begin(URL);
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  int response_code = http.POST("get_product_no");

  return http.getString();
}

String getProductNameFromServer() {
  HTTPClient http;
  http.begin(URL);
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  int response_code = http.POST("get_product_name");

  return http.getString();
}

String getProductBrandFromServer() {
  HTTPClient http;
  http.begin(URL);
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  int response_code = http.POST("get_product_brand");
  
  return http.getString();
}

String getProductPriceFromServer() {
  HTTPClient http;
  http.begin(URL);
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  int response_code = http.POST("get_product_price");
  
  return http.getString();
}

String getProductPromoStatusFromServer() {
  HTTPClient http;
  http.begin(URL);
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  int response_code = http.POST("get_product_promo_status");

  return http.getString();
}

String getProductPromoPriceFromServer() {
  HTTPClient http;
  http.begin(URL);
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  int response_code = http.POST("get_product_promo_price");
  
  return http.getString();
}

String getProductSohFromServer() {
  HTTPClient http;
  http.begin(URL);
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  int response_code = http.POST("get_product_soh");
  
  return http.getString();
}