/**
 * This software is distributed under the terms of the MIT License.
 * Copyright (c) 2022 LXRobotics.
 * Author: Alexander Entinger <alexander.entinger@lxrobotics.com>
 * Contributors: https://github.com/107-systems/107-Arduino-AS504x/graphs/contributors.
 */

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include "107-Arduino-AS504x.h"

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

using namespace AS504x;

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

ArduinoAS504x::ArduinoAS504x(SpiBeginFunc    begin,
                             SpiEndFunc      end,
                             SpiSelectFunc   select,
                             SpiDeselectFunc deselect,
                             SpiTransferFunc transfer,
                             DelayFunc       delay_us)
: _io{begin, end, select, deselect, transfer, delay_us}
{

}

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

uint16_t ArduinoAS504x::angle_raw()
{
  return _io.read(AS504x::Register::AS5048A_Angle);
}
