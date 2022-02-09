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
    BME280(uint8_t bus = 1, uint8_t i2cAddress = BME280_I2C_ADDR_PRIM);
    ~BME280();

    int8_t refresh();
    int8_t updateSettings();

    double getTemperature();
    double getPressure();
    double getHumidity();

    int8_t setSensorMode(uint8_t mode);
    void setTempOversampling(uint8_t oversampling);
    void setPressOversampling(uint8_t oversampling);
    void setHumOversampling(uint8_t oversampling);
    void setFilter(uint8_t coefficient);

private:
    I2CDevice m_i2c;
    struct bme280_dev m_bme280;
    double m_temperature;
    double m_pressure;
    double m_humidity;
};

#endif /* BME280_INTERFACE_H_ */
