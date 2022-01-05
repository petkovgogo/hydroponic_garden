/*
 * bme280.cpp
 *
 *  Created on: Jan 5, 2022
 *      Author: pi
 */

#include "bme280_interface.h"
#include "bme280.h"

#include <unistd.h>

// User api declarations

int8_t bme280_userWrite(uint8_t reg_addr, const uint8_t *reg_data, uint32_t len,
                        void *intf_ptr);

int8_t bme280_userRead(uint8_t reg_addr, uint8_t *reg_data, uint32_t len,
                       void *intf_ptr);

void bme280_userDelay(uint32_t period, void *intf_ptr);

// Function definitions

BME280::BME280(uint8_t bus, uint8_t i2cAddress) :
        m_i2c(bus, i2cAddress), m_temperature(0), m_pressure(0), m_humidity(0)
{
    m_bme280.intf = BME280_I2C_INTF;
    m_bme280.intf_ptr = &m_i2c;
    m_bme280.write = bme280_userWrite;
    m_bme280.read = bme280_userRead;
    m_bme280.delay_us = bme280_userDelay;

    bme280_init(&m_bme280);
}

int8_t BME280::refresh()
{
    struct bme280_data comp_data;

    bme280_get_sensor_data(BME280_ALL, &comp_data, &m_bme280);

    m_temperature = comp_data.temperature;
    m_pressure = comp_data.pressure;
    m_humidity = comp_data.humidity;

    return BME280_OK;
}

int8_t BME280::updateSettings()
{
    uint8_t settingsSelect = BME280_OSR_PRESS_SEL | BME280_OSR_TEMP_SEL | BME280_OSR_HUM_SEL | BME280_FILTER_SEL;

    return bme280_set_sensor_settings(settingsSelect, &m_bme280);
}

double BME280::getTemperature()
{
    return m_temperature;
}

double BME280::getPressure()
{
    return m_pressure;
}

double BME280::getHumidity()
{
    return m_humidity;
}

int8_t BME280::setSensorMode(uint8_t mode)
{
    return bme280_set_sensor_mode(mode, &m_bme280);
}

void BME280::setTempOversampling(uint8_t oversampling)
{
    m_bme280.settings.osr_t = oversampling;
}

void BME280::setPressOversampling(uint8_t oversampling)
{
    m_bme280.settings.osr_p = oversampling;
}

void BME280::setHumOversampling(uint8_t oversampling)
{
    m_bme280.settings.osr_h = oversampling;
}

void BME280::setFilter(uint8_t coefficient)
{
    m_bme280.settings.filter = coefficient;
}

int8_t bme280_userWrite(uint8_t reg_addr, const uint8_t *reg_data, uint32_t len,
                        void *intf_ptr)
{
    reinterpret_cast <I2CDevice*>(intf_ptr)->write(reg_addr, reg_data, len);

    return BME280_OK;
}

int8_t bme280_userRead(uint8_t reg_addr, uint8_t *reg_data, uint32_t len,
                       void *intf_ptr)
{
    reinterpret_cast <I2CDevice*>(intf_ptr)->read(reg_addr, reg_data, len);

    return BME280_OK;
}

void bme280_userDelay(uint32_t period, void *intf_ptr)
{
    usleep(period);
}
