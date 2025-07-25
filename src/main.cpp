#include "sd_read_write.h"
#include <Arduino.h>

void rebootEspWithReason(String reason) {
  Serial.println(reason);
  delay(1000);
  ESP.restart();
}

void setup() {
  Serial.begin(115200);
  Serial.println("Welcome to the SD_MMC Update (1-bit) example!");

  // ✅ Set custom SDMMC pins (must be done BEFORE begin)
  SD_MMC.setPins(SD_MMC_CLK, SD_MMC_CMD, SD_MMC_D0);

  if (!initSDMMC()) {
    rebootEspWithReason("SD_MMC Card Mount Failed");
  }

  if (!isSDCardInserted()) {
    rebootEspWithReason("No SD_MMC card attached");
  }

  updateFromSDMMC();
}

void loop() {
  // Do nothing; runs only once on boot
}