# 📁 ESP32 SD Card Access (SDMMC - One-Bit Mode)

This tutorial demonstrates how to access an SD card on ESP32 using **SDMMC one-bit bus mode**.

---

## 🔌 SD Card Access Methods

This ESP32 board supports **two methods** to communicate with an SD card:

1. **SPI Interface**
   - Uses 4 GPIOs
   - Compatible with standard `SD.h` (SPI mode)

2. **SDMMC Interface**
   - Native high-speed SD interface
   - Two modes:
     - 🟦 **One-bit mode** (uses 3 GPIOs)
     - 🟨 **Four-bit mode** (uses 6 GPIOs)

---

## 🧪 This Tutorial: One-Bit SDMMC Mode

In this example, we use the **SDMMC one-bit bus mode** via the `SD_MMC.h` Arduino library.

### 📌 Pin Configuration

| Signal     | GPIO |
|------------|------|
| SDMMC CMD  | 38   |
| SDMMC CLK  | 39   |
| SDMMC D0   | 40   |

📌 You only need **3 IO pins** in this mode.

---

## 🖼️ Hardware Setup

![SD Card Wiring Diagram](https://github.com/user-attachments/assets/cc279a28-d017-4348-a3e3-965c501c64b7)

---

## 🧰 Libraries Used

- `SD_MMC.h` (built-in with Arduino ESP32 core)
- `FS.h` for file system operations

---

## 💡 Sample Code

```cpp
#include "SD_MMC.h"
#include "sd_read_write.h"


#define SD_MMC_CMD 38 // Please do not modify it.
#define SD_MMC_CLK 39 // Please do not modify it.
#define SD_MMC_D0 40  // Please do not modify it.

void setup() {
  Serial.begin(115200);
  SD_MMC.setPins(SD_MMC_CLK, SD_MMC_CMD, SD_MMC_D0);
  if (!SD_MMC.begin("/sdcard", true, true, SDMMC_FREQ_DEFAULT, 5)) {
    Serial.println("Card Mount Failed");
    return;
  }
  uint8_t cardType = SD_MMC.cardType();
  if (cardType == CARD_NONE) {
    Serial.println("No SD_MMC card attached");
    return;
  }

  Serial.print("SD_MMC Card Type: ");
  if (cardType == CARD_MMC) {
    Serial.println("MMC");
  } else if (cardType == CARD_SD) {
    Serial.println("SDSC");
  } else if (cardType == CARD_SDHC) {
    Serial.println("SDHC");
  } else {
    Serial.println("UNKNOWN");
  }

  uint64_t cardSize = SD_MMC.cardSize() / (1024 * 1024);
  Serial.printf("SD_MMC Card Size: %lluMB\n", cardSize);

  listDir(SD_MMC, "/", 0);

  createDir(SD_MMC, "/mydir");
  listDir(SD_MMC, "/", 0);

  removeDir(SD_MMC, "/mydir");
  listDir(SD_MMC, "/", 2);

  writeFile(SD_MMC, "/hello.txt", "Hello ");
  appendFile(SD_MMC, "/hello.txt", "World!\n");
  readFile(SD_MMC, "/hello.txt");

  deleteFile(SD_MMC, "/foo.txt");
  renameFile(SD_MMC, "/hello.txt", "/foo.txt");
  readFile(SD_MMC, "/foo.txt");

  testFileIO(SD_MMC, "/test.txt");

  Serial.printf("Total space: %lluMB\r\n", SD_MMC.totalBytes() / (1024 * 1024));
  Serial.printf("Used space: %lluMB\r\n", SD_MMC.usedBytes() / (1024 * 1024));
}

void loop() { delay(10000); }
