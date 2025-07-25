#include "sd_read_write.h"
#include <Update.h>

bool initSDMMC() {
  return SD_MMC.begin("/sdcard", true); // true = 1-bit mode
}

bool isSDCardInserted() { return SD_MMC.cardType() != CARD_NONE; }

void performUpdate(Stream &updateSource, size_t updateSize) {
  if (Update.begin(updateSize)) {
    size_t written = Update.writeStream(updateSource);
    if (written == updateSize) {
      Serial.println("Written: " + String(written) + " bytes successfully");
    } else {
      Serial.println("Written only: " + String(written) + "/" +
                     String(updateSize));
    }

    if (Update.end()) {
      Serial.println("OTA done!");
      if (Update.isFinished()) {
        Serial.println("Update complete. Rebooting...");
        SD_MMC.remove("/update.bin"); // Optional cleanup
        delay(1000);
        ESP.restart();
      } else {
        Serial.println("Update not finished!");
      }
    } else {
      Serial.printf("Error #: %d\n", Update.getError());
    }
  } else {
    Serial.println("Not enough space to begin OTA");
  }
}

void updateFromSDMMC() {
  File updateBin = SD_MMC.open("/update.bin");
  if (!updateBin) {
    Serial.println("No update.bin found.");
    return;
  }

  if (updateBin.isDirectory()) {
    Serial.println("Error: update.bin is a directory!");
    updateBin.close();
    return;
  }

  size_t updateSize = updateBin.size();
  if (updateSize > 0) {
    Serial.println("Starting OTA from update.bin...");
    performUpdate(updateBin, updateSize);
    Serial.println("Updated from SD_MMC successfully.");
  } else {
    Serial.println("Error: update.bin is empty");
  }

  updateBin.close();
}
