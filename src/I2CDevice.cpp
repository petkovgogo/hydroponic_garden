/*
 * I2CDevice.cpp
 *
 *  Created on: Jan 4, 2022
 *      Author: pi
 */

#include "I2CDevice.h"

#include <sys/ioctl.h>
#include<linux/i2c.h>
#include <linux/i2c-dev.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

I2CDevice::I2CDevice (uint8_t bus, uint8_t address) :
        m_fd (-1), m_bus (bus), m_address (address)
{
    open ();
}

I2CDevice::~I2CDevice ()
{
    close ();
}

uint8_t I2CDevice::open ()
{
    char device[20];
    sprintf (device, "/dev/i2c-%d", static_cast <int> (m_bus));

    if ((m_fd = ::open (device, O_RDWR)) < 0)
    {
        perror ("I2C: Failed to open the bus");
        return 1;
    }

    if (ioctl (m_fd, I2C_SLAVE, m_address) < 0)
    {
        perror ("I2C: Failed to connect to the device\n");
        return 1;
    }

    return 0;
}

uint8_t I2CDevice::close ()
{
    ::close (m_fd);
    m_fd = -1;

    return 0;
}

uint8_t I2CDevice::write (uint8_t registerAddress, uint8_t value)
{
    uint8_t buffer[] = { registerAddress, value };

    if (::write (m_fd, buffer, 2) != 2)
    {
        perror ("I2C: Failed write to the device\n");
        return 1;
    }

    return 0;
}

uint8_t I2CDevice::read (uint8_t registerAddress)
{
    uint8_t data[] = { registerAddress };

    if (::read (m_fd, data, 1) != 1)
    {
        perror ("I2C: Failed to read in the value.\n");
        return 1;
    }

    return *data;
}
