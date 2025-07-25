# 🔁 ESP32-S3 Blink with SD Card OTA Update

This firmware for ESP32-S3 does two things:

1. Blinks the onboard LED
2. On every boot, checks the SD card for a file named `/firmware.bin`
   - If found, it flashes the binary to the device using OTA
   - Then deletes the file and restarts

---

## ⚙️ Features

- ✅ Automatic firmware update from SD card
- ✅ No USB or internet required
- ✅ Uses **SD_MMC 1-bit mode** (CMD/CLK/D0)
- ✅ Customizable path via `firmwarePath` variable

---

## 🔌 Pin Configuration (ESP32-S3 Default SD_MMC 1-bit)

| SD Signal | GPIO | Description       |
|-----------|------|-------------------|
| CMD       | 38   | Command Line      |
| CLK       | 39   | Clock             |
| D0        | 40   | Data Line 0       |

## 📁 SD Card Update Workflow

1. **Compile a new `.bin` firmware** (**must be include SD card OTA function❗❗**)
   - You can use **PlatformIO** or **Arduino IDE** to build your new application
   - The output will be something like `firmware.bin`

2. **Rename the file to:**
   ```plaintext
   firmware.bin
   Place it in the root directory of a FAT32-formatted microSD card

3. Insert the SD card into your ESP32-S3 board

4. Power on or press the reset button

5. The process will:

    ✅ Detect the file /firmware.bin

    ✅ Flash it to memory using OTA

    ✅ Delete firmware.bin after successful flashing

    ✅ Reboot automatically into the new firmware
