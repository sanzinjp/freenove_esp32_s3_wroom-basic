#include "sd_read_write.cpp"
#include "sd_read_write.h"
#include <Arduino.h>

#define LED_PIN 2 // Change this to match your board's LED

void checkAndUpdateFromSD();

void setup() {
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(115200);
  Serial.println("Booting firmware with SD Card...");
  SD_MMC.setPins(SD_MMC_CLK, SD_MMC_CMD,
                 SD_MMC_D0); // Set custom SD_MMC pins (before begin)
  checkAndUpdateFromSD(); // call the function to check and perform OTA update
}

void loop() {
  digitalWrite(LED_PIN, HIGH);
  delay(3000);
  digitalWrite(LED_PIN, LOW);
  delay(500);
}
