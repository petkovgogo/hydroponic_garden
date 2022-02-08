/*
 * I2CTest.cpp
 *
 *  Created on: Jan 4, 2022
 *      Author: pi
 */

#include "I2CDevice.h"

#include <iostream>

int i2cTest()
{
    I2CDevice bme280(1, 0x76);

    bme280.write(0xF2, 0x01);
    bme280.write(0xF4, 0x27);

    std::cout << std::hex << static_cast <int>(bme280.read(0xF4)) << std::endl;

    std::cout << "Attempting burst write" << std::endl;

    uint8_t wdata[] = { 0xB6, 0xF2, 0x01, 0xF4, 0x27 };

    bme280.write(0xE0, wdata, 5);

    std::cout << "Attempting burst read" << std::endl;

    uint8_t rdata[3] = { 0 };

    bme280.read(0xF2, rdata, 3);

    std::cout << std::hex
              << static_cast <int>(rdata[0])
              << "\n"
              << static_cast <int>(rdata[1])
              << "\n"
              << static_cast <int>(rdata[2])
              << std::endl;

    return 0;
}
