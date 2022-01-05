/*
 * I2CDevice.h
 *
 *  Created on: Jan 4, 2022
 *      Author: pi
 */

#ifndef I2CDEVICE_H_
#define I2CDEVICE_H_

#include <cstdint>

class I2CDevice
{
public:
    I2CDevice(uint8_t bus, uint8_t address);
    ~I2CDevice();

    uint8_t write(uint8_t regAddress, const uint8_t value);
    uint8_t write(uint8_t regAddress, const uint8_t values[], uint32_t len);
    uint8_t read(uint8_t regAddress);
    uint8_t read(uint8_t regAddress, uint8_t outValues[], uint32_t len);

private:
    int m_fd;
    uint8_t m_bus;
    uint8_t m_address;

    uint8_t open();
    uint8_t close();
};

#endif /* I2CDEVICE_H_ */
