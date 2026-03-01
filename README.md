# Проекты:

* [Greenhouse manager](#greenhouse-manager) - Система управление теплицей

---

## Greenhouse manager

### About project:

Used [Arduino WeMos D1 R1 board](#board-specification)

#### Board specification
Microcontroller: ESP-8266EX
Operating Voltage: 3.3V
Digital I/O Pins: 11
Analog Input Pins: 1
Clock Speed: 80MHz/160MHz
Flash: 4M bytes

### Guide:

#### Development Environment Setup

[Source](https://www.instructables.com/Arduino-WeMos-D1-WiFi-UNO-ESP-8266-IoT-IDE-Compati/)

#### Recommended board settings

Board: "LOLIN(WeMos) D1 R1"
Upload Speed: "921600"
CPU Frequency: "80 MHz"
Flash Size: "4MB (FS:2MB OTA:~1019KB)"
Debug port: "Disable"
Debug Level: "None"
IwIP Variant: "v2 Lower Memory"
VTables: "Flash"
C++ Exceptions: "Disable (new aborts on oom)"
Stack Protection: "Disable"
Erase Flash: "Only Sketch"
SSL Support: "All SSL ciphers (most compatible)"
NNU: "16KB cache + 48KB IRAM (IRAM)"
Non-32-Bit Access: "Use pgm_read macros for IRAM/PROGMEM"

### Версии:

* v 2.0 - **Alert sender** [[Ссылка на код]](https://github.com/moodtodie/arduino/tree/f3d4413d316671e8d2d01c95df9ff2939665ee95)

**Alert sender** отслеживает показания датчиков и отправляет уведомления.

---
