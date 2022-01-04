/*
 * I2CTest.cpp
 *
 *  Created on: Jan 4, 2022
 *      Author: pi
 */

#include "I2CDevice.h"

#include <iostream>

int i2cTest ()
{
    I2CDevice bme280 (1, 0x76);

    bme280.write (0xF2, 0x01);
    bme280.write (0xF4, 0x27);

    std::cout << std::hex
              << static_cast <int> (bme280.read (0xF4))
              << std::endl;

    return 0;
}
