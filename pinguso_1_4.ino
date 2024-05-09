//*===========================================================//
// Ping(uso) 1.4
// Created by @wandermenezes - 2023
// Simple Monitoring Tool to check Internet
// connectivity using Home WiFi Connections
// *Board: ESP32-2432s028 and LovyanGFX Drive
//*===========================================================//

//#define LGFX_USE_V1
#include <LovyanGFX.hpp>
#include "lgfx_ESP32_2432S028.h"
#include <WiFi.h>
#include "time.h"
#include <ESP32Ping.h>
#include <Arduino.h>

// PING TARGETS
//Ping whatever you want
char* remoteHost = "www.google.com.br";
char* remoteResolver1 = "8.8.8.8";
char* remoteResolver2 = "208.67.222.222";

char* remoteServer1 = "twitter.com";
char* remoteServer2 = "whatsapp.com";

// WIFI CREDENTIALS
const char* ssid = "<your_wifi>";
const char* password = "<your_pass>";

// NTP Server Settings
// This setting is for Brazil (GNT -3), change it to your country, or the clock will not be very useful.

const char* ntpServer = "pool.ntp.org";
const long gmtOffset_sec = 0;
const int daylightOffset_sec = -3600 * 3; 

int GREEN_LED = 16;
int RED_LED = 4;
int BLUE_LED = 17;

const int onTime = 1000;  // On duration
const int offTime = 500;  // Off duration

// LDR PIN
int LDR = 34;

void setup() {
  // Initialize Serial communication
  Serial.begin(115200);

  // LDR setup
  pinMode(LDR, INPUT);

  // Initialize the display
  tft.init();
  tft.setRotation(1);
  tft.setColorDepth(16);
  tft.setSwapBytes(true);
  tft.setBaseColor(TFT_BLACK);
  tft.setFont(&fonts::DejaVu18);

  // Connect to WiFi
  tft.setCursor(20, 60);
  tft.setTextColor(TFT_GREEN);
  tft.setFont(&fonts::Font4);
  tft.printf("Ping(use) v1.4\n");
  tft.drawFastHLine(20, 100, 280, TFT_GREEN);

  tft.setCursor(20, 115);
  tft.setTextColor(TFT_WHITE);
  tft.setFont(&fonts::Font2);
  tft.setTextColor(TFT_GREEN);
  tft.printf("By @menezeswander");

  tft.setCursor(20, 140);
  tft.setTextColor(TFT_WHITE);
  tft.setFont(&fonts::Font4);
  tft.printf("Loading...");
  tft.fillRect(20, 170, 20, 40, TFT_RED);
  tft.fillRect(20, 180, 280, 40, TFT_GREEN);

  tft.setCursor(40, 190);
  tft.setFont(&fonts::Font4);
  tft.setTextColor(TFT_BLACK);
  tft.printf("WIFI: CONNECTED");
  WiFi.begin(ssid, password);
  delay(3000);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    tft.fillRect(20, 170, 40, 40, TFT_RED);
    tft.fillRect(20, 180, 280, 40, TFT_GREEN);
    tft.setCursor(40, 190);
    tft.setFont(&fonts::Font4);
    tft.setTextColor(TFT_BLACK);
    tft.print("WIFI: TRYING");
    delay(3000);
  }
  tft.fillRect(20, 170, 80, 40, TFT_RED);
  tft.fillRect(20, 180, 280, 40, TFT_GREEN);
  tft.setCursor(40, 190);
  tft.setFont(&fonts::Font4);
  tft.setTextColor(TFT_BLACK);
  tft.println("WIFI: CONNECTED");
  tft.setCursor(40, 190);
  delay(3000);

  // Network information
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());
  Serial.print("GATEWAY: ");
  Serial.println(WiFi.gatewayIP());
  Serial.print("SUBNET MASK: ");
  Serial.println(WiFi.subnetMask());
  Serial.print("MAC ADDRESS: ");
  Serial.println(WiFi.macAddress());

  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  tft.fillRect(20, 170, 280, 40, TFT_RED);
  tft.fillRect(20, 180, 280, 40, TFT_GREEN);
  tft.setCursor(40, 190);
  tft.setFont(&fonts::Font4);
  tft.setTextColor(TFT_BLACK);
  tft.println("SYNC NTP SERVER");
  delay(3000);
  tft.fillScreen(TFT_BLACK);
  printLocalTime();
}

void printLocalTime() {
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    tft.setCursor(20, 25);
    tft.setFont(&fonts::Font2);
    tft.setTextColor(TFT_GREEN);
    tft.print("IP ADDRESS: ");
    tft.println(WiFi.localIP());

    tft.setCursor(20, 50);
    tft.setFont(&fonts::Font2);
    tft.setTextColor(TFT_GREEN);
    tft.print("GATEWAY: ");
    tft.println(WiFi.gatewayIP());

    tft.setCursor(20, 75);
    tft.setFont(&fonts::Font2);
    tft.setTextColor(TFT_GREEN);
    tft.print("SUBNET MASK: ");
    tft.println(WiFi.subnetMask());

    tft.setCursor(20, 100);
    tft.setFont(&fonts::Font2);
    tft.setTextColor(TFT_GREEN);
    tft.print("MAC ADDRESS: ");
    tft.println(WiFi.macAddress());

    tft.fillRect(20, 180, 280, 40, TFT_RED);
    tft.setCursor(45, 190);
    tft.setFont(&fonts::Font4);
    tft.setTextColor(TFT_WHITE);
    tft.println("INTERNET OFF-LINE");
    tft.display();
    delay(5000);
    printLocalTime();
  }

  // Date
  // Sprite Background for date/time data (refresh data without full clear)
  tft.fillRect(15, 89, 290, 18, TFT_BLACK);
  tft.fillRect(15, 110, 210, 48, TFT_BLACK);
  tft.fillRect(15, 15, 100, 65, TFT_BLACK);

  tft.setCursor(20, 20);
  tft.setFont(&fonts::Font4);
  tft.setTextColor(TFT_GREEN);
  tft.print(&timeinfo, "%a\n");

  tft.setCursor(20, 50);
  tft.setFont(&fonts::Font0);
  tft.setTextColor(TFT_WHITE);
  tft.print(&timeinfo, "%d, %b %Y");

  tft.setCursor(20, 65);
  tft.setFont(&fonts::Font0);
  tft.setTextColor(TFT_GREEN);
  tft.print("Ping(uso) v1.4");

  tft.setCursor(25, 115);
  tft.setFont(&fonts::Font6);
  tft.setTextColor(TFT_GREEN);
  tft.println(&timeinfo, "%H:%M:%S");

  // Average response time
  tft.setCursor(25, 90);
  tft.setFont(&fonts::Font2);
  tft.setTextColor(TFT_WHITE);
  tft.print(Ping.averageTime());  // Returns the average ping time
  tft.println(" ms - Ping: www.google.com");

  // Sprite
  tft.drawRect(5, 5, 310, 230, TFT_WHITE);
  tft.drawRect(10, 10, 300, 220, TFT_GREEN);
  tft.drawFastHLine(10, 85, 300, TFT_GREEN);
}

void LDR_S() {
  int LDR_Vp = analogRead(LDR);
  if (LDR_Vp > 1000) {
    tft.drawCircle(85, 30, 6, TFT_GREEN);
    tft.setBrightness(15);
    tft.setBrightness(25);
    tft.setBrightness(30);
  } else {
    tft.fillCircle(85, 30, 6, TFT_GREEN);
    tft.setBrightness(35);
    tft.setBrightness(25);
    tft.setBrightness(15);
  }
}

void WSignal() {
  if (WiFi.RSSI() > -70) {
    tft.fillCircle(265, 131, 24, TFT_GREEN);
    tft.setCursor(245, 115);
    tft.setTextColor(TFT_BLACK);
    tft.setFont(&fonts::Font4);
    tft.println(WiFi.RSSI());

    tft.setCursor(255, 135);
    tft.setTextColor(TFT_BLACK);
    tft.setFont(&fonts::Font2);
    tft.println("dBm");
    turnOffLEDs();
  } else {
