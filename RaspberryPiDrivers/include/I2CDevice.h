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
    /**
     * @brief Initialize a new instance and open a connection
     * 
     * @param[in] bus     : The I2C bus to use for communication
     * @param[in] address : The I2C address of the device
     */
    I2CDevice(uint8_t bus, uint8_t address);

    /** @brief Closes the connection safely, then destroys the instance */
    ~I2CDevice();

    /**
     * @brief Writes a single value to a given register
     * 
     * @param[in] regAddress : Register address to access
     * @param[in] value      : Byte to send
     * 
     * @return Result of execution status
     * 
     * @retval 0 -> Success
     * @retval 1 -> Error
     */
    uint8_t write(uint8_t regAddress, const uint8_t value);

    /**
     * @brief Writes multiple values to a given register
     * 
     * @param[in] regAddress : Register address to access
     * @param[in] values     : An array of bytes to send
     * @param[in] len        : The quantity of values
     * 
     * @return Result of execution status
     * 
     * @retval 0 -> Success
     * @retval 1 -> Error
     */
    uint8_t write(uint8_t regAddress, const uint8_t values[], uint32_t len);

    /**
     * @brief Reads a single value from a given register
     * 
     * @param[in] regAddress : Register address to access
     * 
     * @return Result of execution status
     * 
     * @retval 0 -> Success
     * @retval 1 -> Error
     */
    uint8_t read(uint8_t regAddress);

    /**
     * @brief Reads multiple values from a given register
     * 
     * @param[in]  regAddress : Register address to access
     * @param[out] outValues  : The byte array to store the read values
     * 
     * @return Result of execution status
     * 
     * @retval 0 -> Success
     * @retval 1 -> Error
     */
    uint8_t read(uint8_t regAddress, uint8_t outValues[], uint32_t len);

private:
    int m_fd;
    uint8_t m_bus;
    uint8_t m_address;

    uint8_t open();
    uint8_t close();
};

#endif /* I2CDEVICE_H_ */
