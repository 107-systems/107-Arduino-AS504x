/**
 * This software is distributed under the terms of the MIT License.
 * Copyright (c) 2022 LXRobotics.
 * Author: Alexander Entinger <alexander.entinger@lxrobotics.com>
 * Contributors: https://github.com/107-systems/107-Arduino-AS504x/graphs/contributors.
 */

#ifndef ARDUINO_AS504x_AS504x_CONST_H_
#define ARDUINO_AS504x_AS504x_CONST_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <stdint.h>

#include <type_traits>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace AS504x
{

/**************************************************************************************
 * TYPEDEF
 **************************************************************************************/

enum class Register : uint16_t
{
  AS5048A_ClearErrorFlag                   = 0x0001,
  AS5048A_ProgrammingControl               = 0x0003,
  AS5048A_OTP_RegisterZeroPosition_HIGH    = 0x0016,
  AS5048A_OTP_RegisterZeroPosition_LOW     = 0x0017,
  AS5048A_Diagnostics_AutomaticGainControl = 0x3FFD,
  AS5048A_Magnitude                        = 0x3FFE,
  AS5048A_Angle                            = 0x3FFF,
};

union CommandFrame
{
  struct __attribute__((packed))
  {
    uint16_t address    : 14;
    uint16_t read_write :  1;
    uint16_t parity     :  1;
  } field;
  uint16_t all;
  static_assert(sizeof(all) == 2, "Error, sizeof(AS504x::CommandFrame) should be 2 bytes.");
};

union ReadFrame
{
  struct __attribute__((packed))
  {
    uint16_t data       : 14;
    uint16_t error_flag :  1;
    uint16_t parity     :  1;
  } field;
  uint16_t all;
  static_assert(sizeof(all) == 2, "Error, sizeof(AS504x::ReadFrame) should be 2 bytes.");
};

union WriteFrame
{
  struct __attribute__((packed))
  {
    uint16_t data     : 14;
    uint16_t reserved :  1;
    uint16_t parity   :  1;
  } field;
  uint16_t all;
  static_assert(sizeof(all) == 2, "Error, sizeof(AS504x::WriteFrame) should be 2 bytes.");
};

/**************************************************************************************
 * CONVERSION FUNCTIONS
 **************************************************************************************/

template <typename Enumeration>
constexpr auto to_integer(Enumeration const value) -> typename std::underlying_type<Enumeration>::type
{
  return static_cast<typename std::underlying_type<Enumeration>::type>(value);
}

template <typename Enumeration>
constexpr auto bp(Enumeration const value) -> typename std::underlying_type<Enumeration>::type
{
  return to_integer(value);
}

template <typename Enumeration>
constexpr auto bm(Enumeration const value) -> typename std::underlying_type<Enumeration>::type
{
  return (1 << to_integer(value));
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* AS504x */

#endif /* ARDUINO_AS504x_AS504x_CONST_H_ */
