/**
 * @brief Basic example demonstrating usage of 107-Arduino-AS504x library.
 */

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <Arduino.h>

#include <SPI.h>

#include <107-Arduino-AS504x.h>

/**************************************************************************************
 * CONSTANTS
 **************************************************************************************/

static int         const AS504x_CS_PIN = 2;
static SPISettings const AS504x_SPI_SETTING{1000000, MSBFIRST, SPI_MODE1};

/**************************************************************************************
 * GLOBAL VARIABLES
 **************************************************************************************/

AS504x::AS504x_Io angle_pos_sensor([](){ SPI.beginTransaction(AS504x_SPI_SETTING); },
                                   [](){ SPI.endTransaction(); },
                                   [](){ digitalWrite(AS504x_CS_PIN, LOW); },
                                   [](){ digitalWrite(AS504x_CS_PIN, HIGH); },
                                   [](uint8_t const d) -> uint8_t { return SPI.transfer(d); },
                                   delayMicroseconds);

/**************************************************************************************
 * SETUP/LOOP
 **************************************************************************************/

void setup()
{
  Serial.begin(115200);
  while (!Serial) { }

  SPI.begin();
  pinMode(AS504x_CS_PIN, OUTPUT);
  digitalWrite(AS504x_CS_PIN, LOW);
}

void loop()
{
  uint16_t const raw_angle = angle_pos_sensor.read(AS504x::Register::AS5048A_Angle);

  char msg[64] = {0};
  snprintf(msg, sizeof(msg), "Angle (Raw) = %d", raw_angle);
  Serial.println(msg);

  delay(100);
}
