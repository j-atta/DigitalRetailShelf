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

unsigned int Actual_Millis, Previous_Millis;
int refreshTime = 1000; // ms

// INFO FOR DISPLAY
String productNumber = "";
String productName = "";
String productBrand =  "";
String productPrice = "";
String productPromoPrice = "";
String productPromoStatus = "";
String productSOH = "";

void setup() {
  // Initialisation
  Serial.begin(115200);
  display.init(115200, true, 2, false);
  setupWifi(ssid, password);
  SetFromServer();
  updateDisplay();

  Actual_Millis = millis();               //Save time for refresh loop
  Previous_Millis = Actual_Millis; 
}

void loop() {
  // put your main code here, to run repeatedly:
  Actual_Millis = millis();
  if(Actual_Millis - Previous_Millis > refreshTime) {
    Previous_Millis = Actual_Millis;
    if(WiFi.status()== WL_CONNECTED) {
      if(CheckServer()) {
        SetFromServer();
        updateDisplay();
      }
    }
    else {
      Serial.println("WIFI connection error");
    }
  }
} 

void updateDisplay() {
  display.setRotation(1);
  display.setFont(&FreeMonoBold9pt7b);
  display.setTextColor(GxEPD_BLACK);
  display.firstPage();
  do
  {
    display.fillScreen(GxEPD_WHITE);
    display.setCursor(0, 20);
    if (productPromoStatus.toInt() == 1) {
      display.println(String("SKU: " + productNumber).c_str());
      display.println(String("Name: " + productName).c_str());
      display.println(String("Brand: " + productBrand).c_str());
      display.println(String("Sale Price: $" + productPromoPrice).c_str());
    }
    else {
      display.println(String("SKU: " + productNumber).c_str());
      display.println(String("Name: " + productName).c_str());
      display.println(String("Brand: " + productBrand).c_str());
      display.println(String("Price: $" + productPrice).c_str());
    }

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

void SetFromServer() {
  productNumber = getProductNumberFromServer();
  productName = getProductNameFromServer();
  productBrand =  getProductBrandFromServer();
  productPrice = getProductPriceFromServer();
  productPromoStatus = getProductPromoStatusFromServer();
  productPromoPrice = getProductPromoPriceFromServer();
  productSOH = getProductSohFromServer();
}

bool CheckServer() {
  if(!productNumber.equals(getProductNumberFromServer())) return true;
  if(!productName.equals(getProductNameFromServer())) return true;
  if(!productBrand.equals(getProductBrandFromServer())) return true;
  if(!productPrice.equals(getProductPriceFromServer())) return true;
  if(!productPromoStatus.equals(getProductPromoStatusFromServer())) return true;
  if(!productPromoPrice.equals(getProductPromoPriceFromServer())) return true;
  if(!productSOH.equals(getProductSohFromServer())) return true;

  return false;
}