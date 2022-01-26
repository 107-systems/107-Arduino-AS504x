/**
 * This software is distributed under the terms of the MIT License.
 * Copyright (c) 2022 LXRobotics.
 * Author: Alexander Entinger <alexander.entinger@lxrobotics.com>
 * Contributors: https://github.com/107-systems/107-Arduino-AS504x/graphs/contributors.
 */

#ifndef ARDUINO_AS504x_AS504x_IO_H_
#define ARDUINO_AS504x_AS504x_IO_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#undef max
#undef min
#include <functional>

#include "AS504x_Const.h"

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace AS504x
{

/**************************************************************************************
 * TYPEDEF
 **************************************************************************************/

typedef std::function<void()>                    SpiBeginFunc;
typedef std::function<void()>                    SpiEndFunc;
typedef std::function<void()>                    SpiSelectFunc;
typedef std::function<void()>                    SpiDeselectFunc;
typedef std::function<uint8_t(uint8_t const)>    SpiTransferFunc;
typedef std::function<void(unsigned long const)> DelayFunc;

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class AS504x_Io
{
public:

  AS504x_Io(SpiBeginFunc    begin,
            SpiEndFunc      end,
            SpiSelectFunc   select,
            SpiDeselectFunc deselect,
            SpiTransferFunc transfer,
            DelayFunc       delay_us);


  uint16_t read  (Register const reg);
  bool     write (Register const reg, uint16_t const val);


private:

  SpiBeginFunc _begin;
  SpiEndFunc _end;
  SpiSelectFunc _select;
  SpiDeselectFunc _deselect;
  SpiTransferFunc _transfer;
  DelayFunc _delay_us;

  void      send_command_READ (Register const reg);
  void      send_command_WRITE(Register const reg);
  ReadFrame send_command_NOP  ();
  void      send_write_frame  (uint16_t const val);

  static uint16_t command_set_even_parity(uint16_t const cmd);
  static uint16_t write_set_even_parity  (uint16_t const write);
  static uint8_t  high_byte              (uint16_t const word);
  static uint8_t  low_byte               (uint16_t const word);

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* AS504x */

#endif /* ARDUINO_BMP388_BMP388_IO_H_ */
