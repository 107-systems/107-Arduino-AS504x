<a href="https://107-systems.org/"><img align="right" src="https://raw.githubusercontent.com/107-systems/.github/main/logo/107-systems.png" width="15%"></a>
`107-Arduino-AS504x`
====================

<p align="center">
  <a href="https://github.com/107-systems/107-Arduino-DroneCore"><img src="https://github.com/107-systems/.github/raw/main/logo/viper.jpg" width="40%"></a>
</p>

Arduino library for interfacing with various Austria Micro Systems angle position sensors.

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
