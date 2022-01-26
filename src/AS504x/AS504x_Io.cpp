/**
 * This software is distributed under the terms of the MIT License.
 * Copyright (c) 2022 LXRobotics.
 * Author: Alexander Entinger <alexander.entinger@lxrobotics.com>
 * Contributors: https://github.com/107-systems/107-Arduino-AS504x/graphs/contributors.
 */

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include "AS504x_Io.h"

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace AS504x
{

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

AS504x_Io::AS504x_Io(SpiBeginFunc    begin,
                     SpiEndFunc      end,
                     SpiSelectFunc   select,
                     SpiDeselectFunc deselect,
                     SpiTransferFunc transfer,
                     DelayFunc       delay_us)
: _begin{begin}
, _end{end}
, _select{select}
, _deselect{deselect}
, _transfer{transfer}
, _delay_us{delay_us}
{

}

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

uint16_t AS504x_Io::read(Register const reg)
{
  _begin();
  send_command_READ(reg);
  _delay_us(50);
  ReadFrame const frame = send_command_NOP();
  _end();
  return frame.field.data;
}

bool AS504x_Io::write(Register const reg, uint16_t const val)
{
  _begin();
  send_command_WRITE(reg);
  _delay_us(50);
  send_write_frame(val & 0x3FFF);
  _delay_us(50);
  ReadFrame const frame = send_command_NOP();
  _end();
  return (frame.field.data == (val & 0x3FFF));
}

/**************************************************************************************
 * PRIVATE MEMBER FUNCTIONS
 **************************************************************************************/

void AS504x_Io::send_command_READ(Register const reg)
{
  CommandFrame cmd_frame;

  cmd_frame.field.read_write = 1;
  cmd_frame.field.address    = to_integer(reg);

  cmd_frame.all = command_set_even_parity(cmd_frame.all);

  _select();
  _transfer(high_byte(cmd_frame.all));
  _transfer(low_byte (cmd_frame.all));
  _deselect();
}

void AS504x_Io::send_command_WRITE(Register const reg)
{
  CommandFrame cmd_frame;

  cmd_frame.field.read_write = 0;
  cmd_frame.field.address    = to_integer(reg);

  cmd_frame.all = command_set_even_parity(cmd_frame.all);

  _select();
  _transfer(high_byte(cmd_frame.all));
  _transfer(low_byte (cmd_frame.all));
  _deselect();
}

ReadFrame AS504x_Io::send_command_NOP()
{
  ReadFrame read_frame;

  _select();
  read_frame.all  = static_cast<uint16_t>(_transfer(0)) << 8;
  read_frame.all |= static_cast<uint16_t>(_transfer(0)) << 0;
  _deselect();

  return read_frame;
}

void AS504x_Io::send_write_frame(uint16_t const val)
{
  WriteFrame write_frame;

  write_frame.field.reserved = 0;
  write_frame.field.data     = val;

  write_frame.all = write_set_even_parity(write_frame.all);

  _select();
  _transfer(high_byte(write_frame.all));
  _transfer(low_byte (write_frame.all));
  _deselect();
}

uint16_t AS504x_Io::command_set_even_parity(uint16_t const cmd)
{
  size_t bit_set_cnt = 0;

  for(size_t bit = 0; bit < 16; bit++)
  {
    auto isBitSet = [](uint16_t const byte, size_t const bit)->bool { return ((byte & (1<<bit)) == (1<<bit)); };
    if (isBitSet(cmd, bit))
      bit_set_cnt++;
  }

  bool is_bit_set_cnt_even = (is_bit_set_cnt_even % 2) == 0;

  if (is_bit_set_cnt_even)
    return (cmd | 0x8000); /* Set the parity bit. */
  else
    return (cmd & 0x7FFF); /* Clean the parity bit. */
}

uint16_t AS504x_Io::write_set_even_parity(uint16_t const write)
{
  return command_set_even_parity(write);
}

uint8_t AS504x_Io::high_byte(uint16_t const word)
{
  return static_cast<uint8_t>((word & 0xFF00) >> 8);
}

uint8_t AS504x_Io::low_byte(uint16_t const word)
{
  return static_cast<uint8_t>((word & 0x00FF) >> 0);
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* AS504x */
