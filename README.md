<a href="https://107-systems.org/"><img align="right" src="https://raw.githubusercontent.com/107-systems/.github/main/logo/107-systems.png" width="15%"></a>
`107-Arduino-AS504x`
====================
[![Arduino Library Badge](https://www.ardu-badge.com/badge/107-Arduino-AS504x.svg?)](https://www.ardu-badge.com/107-Arduino-AS504x)
[![Compile Examples](https://github.com/107-systems/107-Arduino-AS504x/workflows/Compile%20Examples/badge.svg)](https://github.com/107-systems/107-Arduino-AS504x/actions?workflow=Compile+Examples)
[![Check Arduino](https://github.com/107-systems/107-Arduino-AS504x/actions/workflows/check-arduino.yml/badge.svg)](https://github.com/107-systems/107-Arduino-AS504x/actions/workflows/check-arduino.yml)
[![Check keywords.txt](https://github.com/107-systems/107-Arduino-AS504x/actions/workflows/check-keywords-txt.yml/badge.svg)](https://github.com/107-systems/107-Arduino-AS504x/actions/workflows/check-keywords-txt.yml)
[![General Formatting Checks](https://github.com/107-systems/107-Arduino-AS504x/workflows/General%20Formatting%20Checks/badge.svg)](https://github.com/107-systems/107-Arduino-AS504x/actions?workflow=General+Formatting+Checks)
[![Spell Check](https://github.com/107-systems/107-Arduino-AS504x/workflows/Spell%20Check/badge.svg)](https://github.com/107-systems/107-Arduino-AS504x/actions?workflow=Spell+Check)

Arduino library for interfacing with various Austria Micro Systems angle position sensors.

<p align="center">
  <a href="https://github.com/107-systems/l3xz"><img src="https://raw.githubusercontent.com/107-systems/.github/main/logo/l3xz-logo-memento-mori-github.png" width="40%"></a>
</p>

This library works for
* [ArduinoCore-samd](https://github.com/arduino/ArduinoCore-samd): [`Arduino Zero`](https://store.arduino.cc/arduino-zero), [`MKR 1000`](https://store.arduino.cc/arduino-mkr1000-wifi), [`MKR WiFi 1010`](https://store.arduino.cc/arduino-mkr-wifi-1010), [`Nano 33 IoT`](https://store.arduino.cc/arduino-nano-33-iot), [`MKR GSM 1400`](https://store.arduino.cc/arduino-mkr-gsm-1400-1415), [`MKR NB 1500`](https://store.arduino.cc/arduino-mkr-nb-1500-1413), [`MKR WAN 1300/1310`](https://store.arduino.cc/mkr-wan-1310) :heavy_check_mark:
* [ArduinoCore-mbed](https://github.com/arduino/ArduinoCore-mbed): [`Portenta H7`](https://store.arduino.cc/portenta-h7), [`Nano 33 BLE`](https://store.arduino.cc/arduino-nano-33-ble), [`Nano RP2040 Connect`](https://store.arduino.cc/nano-rp2040-connect), [`Edge Control`](https://store.arduino.cc/edge-control) :heavy_check_mark:

## Example
```C++
#include <107-Arduino-AS504x.h>
/* ... */
ArduinoAS504x angle_pos_sensor([](){ SPI.beginTransaction(AS504x_SPI_SETTING); },
                               [](){ SPI.endTransaction(); },
                               [](){ digitalWrite(AS504x_CS_PIN, LOW); },
                               [](){ digitalWrite(AS504x_CS_PIN, HIGH); },
                               [](uint8_t const d) -> uint8_t { return SPI.transfer(d); },
                               delayMicroseconds);
/* ... */
void setup()
{
  SPI.begin();
  pinMode(AS504x_CS_PIN, OUTPUT);
  digitalWrite(AS504x_CS_PIN, LOW);
}

void loop()
{
  char msg[64] = {0};
  snprintf(msg, sizeof(msg), "Angle (Raw) = %d", angle_pos_sensor.angle_raw());
  Serial.println(msg);
  delay(100);
}
```

## Hardware
**Breakout/Development-Board**
* [Nano RP2040 Connect](https://store.arduino.cc/nano-rp2040-connect)
* [AS5048A-TS_EK_AB](https://ams.com/as5048aadapterboard/)
* [RMH05-DK-XX](https://ams.com/rmh05-dk-xx)

<p align="center">
  <img src="extras/img/Arduino-Nano-RP2040-Connect-AS5048A.jpg" width="60%">
</p>

| **Colour** | **Nano RP2040 Pin** | **AS5048A-TS_EK_AB Pin** |
|:----------:|:-------------------:|:------------------------:|
| Red        | 3.3V                | 3.3V                     |
| Black      | GND                 | GND                      |
| Green (1)  | CIPO                | MISO                     |
| Yellow     | COPI                | MOSI                     |
| Blue       | SCK                 | SCK                      |
| Green (2)  | D2                  | CSn                      |
