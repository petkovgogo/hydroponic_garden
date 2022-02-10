#include "bme280_interface.h"

#include <iostream>

int main()
{
    BME280 bme280;

    bme280.setTempOversampling(BME280_OVERSAMPLING_1X);
    bme280.setHumOversampling(BME280_OVERSAMPLING_1X);
    bme280.setPressOversampling(BME280_OVERSAMPLING_1X);
    bme280.setFilter(BME280_FILTER_COEFF_OFF);
    bme280.updateSettings();

    bme280.setSensorMode(BME280_FORCED_MODE);
    bme280.refresh();

    std::cout << "Content-Type: application/json\n\n";
    std::cout << "{\n";
    std::cout << "    \"temperature:\" \"" << bme280.getTemperature() << "\"\n";
    std::cout << "    \"humidity:\" \"" << bme280.getHumidity() << "\"\n";
    std::cout << "    \"pressure:\" \"" << bme280.getPressure() << "\"\n";
    std::cout << "}" << std::endl;

    return 0;
}
