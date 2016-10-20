#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

extern "C" {
#include<user_interface.h>
}

int connectedClients = 0;

long nextCheck = 0;

Adafruit_SSD1306 display = Adafruit_SSD1306();

#ifdef ARDUINO_SAMD_ZERO
#define Serial SerialUSB
#endif

/* configuration  wifi */
const char *ssid = "MySSID";
const char *password = "";

#if defined(ESP8266)
  #define BUTTON_A 0
  #define BUTTON_B 16
  #define BUTTON_C 2
  #define LED      0
#elif defined(ARDUINO_STM32F2_FEATHER)
  #define BUTTON_A PA15
  #define BUTTON_B PC7
  #define BUTTON_C PC5
  #define LED PB5
#else 
  #define BUTTON_A 9
  #define BUTTON_B 6
  #define BUTTON_C 5
  #define LED      13
#endif

#if (SSD1306_LCDHEIGHT != 32)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

bool buttonIsPressed = false;

void setup() {  
#if !defined(ESP8266)
  while (!Serial) delay(1);
#endif

  delay(1000);
  
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x32)
  // init done

  // text display tests
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.clearDisplay();
  display.display();
  
  initializeAP();
  
  pinMode(BUTTON_A, INPUT_PULLUP);
  pinMode(BUTTON_B, INPUT_PULLUP);
  pinMode(BUTTON_C, INPUT_PULLUP);

  
  
  
  
}

void initializeAP() {

  WiFi.softAP(ssid, password);
  
  String dotString = ".";

  //Give the feather time to set up the AP
  for (int i = 0; i < 10; i++) {

    display.clearDisplay();
    display.display();
    display.setTextSize(1);
    display.setCursor(0,0);
    display.print("Initializing AP");

    display.setCursor(0, 10);
    display.println(dotString);
    display.display();
    
    dotString += ".";
    delay(500);
  }
  
  
  display.clearDisplay();
  display.display();
  display.setCursor(0,0);
  
  display.print("AP SSID: ");
  display.setTextSize(2);
  display.setCursor(0, 10);
  display.println(ssid);
  display.display();
  
}

void loop() {

  if (millis() >= nextCheck) {
    client_status();

    nextCheck = millis() + 5000;
  }
   
}

void displaySSID() {

  display.setTextSize(1);
  display.clearDisplay();
  display.display();
  display.setCursor(0,0);
  IPAddress myIP = WiFi.softAPIP();
  display.print("AP SSID: ");
  display.setTextSize(2);
  display.setCursor(0, 10);
  display.println(ssid);
  display.display();
      
}

void client_status() {

  unsigned char number_client;
  struct station_info *stat_info;

  struct ip_addr *IPaddress;
  IPAddress address;
  int i=1;
  
  number_client= wifi_softap_get_station_num(); // Count of stations which are connected to ESP8266 soft-AP
  stat_info = wifi_softap_get_station_info();

  if (number_client > connectedClients) {
     display.setTextSize(1);
     display.clearDisplay();
     display.setCursor(0, 0);
     display.setTextSize(1);
     display.print("Client Connected!");
     display.display();  
     delay(2000);
  } 

  if (number_client < connectedClients) {
     display.setTextSize(1);
     display.clearDisplay();
     display.setCursor(0, 0);
     display.setTextSize(1);
     display.print("Client Disconnected!");
     display.display();
     delay(2000); 

     if (number_client == 0) {
      displaySSID();
      
    }
    
  }
  
  connectedClients = number_client;

  
  
  while (stat_info != NULL) {
  
    IPaddress = &stat_info->ip;
    address = IPaddress->addr;
    
    display.clearDisplay();
    display.setCursor(0, 0);
    display.print("Client MAC:");

    display.setCursor(0, 10);
    
    
    if (stat_info->bssid[0] < 0xF) {
      display.print("0");
    }
    
    display.print(stat_info->bssid[0],HEX);
    display.print(":");
    
    if (stat_info->bssid[1] < 0xF) {
      display.print("0");
    }
    
    display.print(stat_info->bssid[1],HEX);
    display.print(":");
    
    if (stat_info->bssid[2] < 0xF) {
      display.print("0");
    }
    
    display.print(stat_info->bssid[2],HEX);
    display.print(":");
    
    if (stat_info->bssid[3] < 0xF) {
      display.print("0");
    
    }
    display.print(stat_info->bssid[3],HEX);
    display.print(":");
    
    if (stat_info->bssid[4] < 0xF) {
      display.print("0");
    }
    
    display.print(stat_info->bssid[4],HEX);
    display.print(":");
    
    if (stat_info->bssid[5] < 0xF) {
      display.print("0");
    }
    
    display.print(stat_info->bssid[5],HEX);

    display.display();
    
    stat_info = STAILQ_NEXT(stat_info, next);
    i++;
  
  }
}
