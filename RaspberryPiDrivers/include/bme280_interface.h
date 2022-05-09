/*
 * BME280.h
 *
 *  Created on: Jan 5, 2022
 *      Author: pi
 */

#ifndef BME280_INTERFACE_H_
#define BME280_INTERFACE_H_

#include "bme280_defs.h"
#include "I2CDevice.h"

class BME280
{
public:
    /**
     * @brief Initialize the sensor and infrastructure
     *
     * @param[in] bus        : The I2C bus to use for communication; defaults to 1
     * @param[in] i2cAddress : The address BME280 will use; defaults to 0x76
     */
    BME280(uint8_t bus = 1, uint8_t i2cAddress = BME280_I2C_ADDR_PRIM);

    /**
     * @brief Soft reset the sensor, before destroying the object
     */
    ~BME280();

    /**
     * @brief Refresh the sensor values
     *
     * @return Result of execution status
     *
     * @retval   0 -> Success.
     * @retval > 0 -> Warning.
     * @retval < 0 -> Fail.
     */
    int8_t refresh();

    /**
     * @brief Send the updated settings to the sensor
     *
     * @return Result of execution status
     *
     * @retval   0 -> Success.
     * @retval > 0 -> Warning.
     * @retval < 0 -> Fail.
     */
    int8_t updateSettings();

    /**
     * @brief Change the mode of the sensor
     *
     * @param[in] mode : Accepts one of three modes from the Bosch API
     *
     * @note The three macros are as follows:
     * BME280_SLEEP_MODE  for no samples
     * BME280_FORCED_MODE for a single sample
     * BME280_NORMAL_MODE for continious sampling
     */
    int8_t setSensorMode(uint8_t mode);

    /**
     * @brief Get the temperature value from the last refresh
     *
     * @note The value is ONLY changed after calling refresh()
     *
     * @return Temperature value in degrees Celsius
     */
    double getTemperature();

    /**
     * @brief Get the pressure value from the last refresh
     *
     * @note The value is ONLY changed after calling refresh()
     *
     * @return Pressure value in Pa
     */
    double getPressure();

    /**
     * @brief Get the humidity value from the last refresh
     *
     * @note The value is ONLY changed after calling refresh()
     *
     * @return Humidity value in per cent
     */
    double getHumidity();

    /**
     * @brief Set the oversampling of temperature measurements
     *
     * @param[in] oversampling : Accepts one of the oversampling modes from the Bosch API
     *
     * @note ONLY sets the setting. To apply, call updateSettings()
     * @note The possible macros are as follows:
     * BME280_NO_OVERSAMPLING
     * BME280_OVERSAMPLING_1X
     * BME280_OVERSAMPLING_2X
     * BME280_OVERSAMPLING_4X
     * BME280_OVERSAMPLING_8X
     * BME280_OVERSAMPLING_16X
     */
    void setTempOversampling(uint8_t oversampling);

    /**
     * @brief Set the oversampling of pressure measurements
     *
     * @param[in] oversampling : Accepts one of the oversampling modes from the Bosch API
     *
     * @note ONLY sets the setting. To apply, call updateSettings()
     * @note The possible macros are as follows:
     * BME280_NO_OVERSAMPLING
     * BME280_OVERSAMPLING_1X
     * BME280_OVERSAMPLING_2X
     * BME280_OVERSAMPLING_4X
     * BME280_OVERSAMPLING_8X
     * BME280_OVERSAMPLING_16X
     */
    void setPressOversampling(uint8_t oversampling);

    /**
     * @brief Set the oversampling of humidity measurements
     *
     * @param[in] oversampling : Accepts one of the oversampling modes from the Bosch API
     *
     * @note ONLY sets the setting. To apply, call updateSettings()
     * @note The possible macros are as follows:
     * BME280_NO_OVERSAMPLING
     * BME280_OVERSAMPLING_1X
     * BME280_OVERSAMPLING_2X
     * BME280_OVERSAMPLING_4X
     * BME280_OVERSAMPLING_8X
     * BME280_OVERSAMPLING_16X
     */
    void setHumOversampling(uint8_t oversampling);

    /**
     * @brief Set the coefficient of the IIR filter
     *
     * @param[in] coefficient : Accepts one of the coefficient modes from the Bosch API
     *
     * @note ONLY sets the setting. To apply, call updateSettings()
     * @note The possible macros are as follows:
     * BME280_FILTER_COEFF_OFF
     * BME280_FILTER_COEFF_2
     * BME280_FILTER_COEFF_4
     * BME280_FILTER_COEFF_8
     * BME280_FILTER_COEFF_16
     */
    void setFilter(uint8_t coefficient);

private:
    I2CDevice m_i2c;
    struct bme280_dev m_bme280;
    double m_temperature;
    double m_pressure;
    double m_humidity;
};

#endif /* BME280_INTERFACE_H_ */
