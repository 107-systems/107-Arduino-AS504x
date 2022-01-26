/**
 * This software is distributed under the terms of the MIT License.
 * Copyright (c) 2022 LXRobotics.
 * Author: Alexander Entinger <alexander.entinger@lxrobotics.com>
 * Contributors: https://github.com/107-systems/107-Arduino-AS504x/graphs/contributors.
 */

#ifndef _107_ARDUINO_AS504x_H_
#define _107_ARDUINO_AS504x_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include "AS504x/AS504x_Io.h"

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class ArduinoAS504x
{

public:

  ArduinoAS504x(AS504x::SpiBeginFunc    begin,
                AS504x::SpiEndFunc      end,
                AS504x::SpiSelectFunc   select,
                AS504x::SpiDeselectFunc deselect,
                AS504x::SpiTransferFunc transfer,
                AS504x::DelayFunc       delay_us);


  uint16_t angle_raw();

private:

  AS504x::AS504x_Io _io;

};

#endif /* _107_ARDUINO_AS504x_H_ */
