/*
 * bme280Test.cpp
 *
 *  Created on: Jan 5, 2022
 *      Author: pi
 */

#include "bme280_interface.h"

#include <iostream>

int bme280Test()
{
    BME280 bme280;

    bme280.setSensorMode(BME280_FORCED_MODE);

    bme280.refresh();

    std::cout << "Temp: " << bme280.getTemperature() << "\n"
              << "Press: " << bme280.getPressure() << "\n"
              << "Hum: " << bme280.getHumidity() << "\n"
              << std::endl;

    bme280.setTempOversampling(BME280_OVERSAMPLING_8X);
    bme280.setPressOversampling(BME280_OVERSAMPLING_2X);
    bme280.setHumOversampling(BME280_OVERSAMPLING_4X);
    bme280.setFilter(BME280_FILTER_COEFF_16);
    bme280.updateSettings();

    bme280.setSensorMode(BME280_FORCED_MODE);

    bme280.refresh();

    std::cout << "Temp: " << bme280.getTemperature() << "\n"
              << "Press: " << bme280.getPressure() << "\n"
              << "Hum: " << bme280.getHumidity() << "\n"
              << std::endl;

    return 0;
}
