#ifndef ANALOG_SENSOR_H_
#define ANALOG_SENSOR_H_

#include <cstdint>

class AnalogSensor
{
public:
    typedef float (*comp_func_t)(uint16_t rawValue);

    AnalogSensor(uint8_t dataPin, comp_func_t compensationFunc);
    ~AnalogSensor() = default;

    void refresh();
    float getMeasurement();

private:
    static constexpr uint32_t SAMPLE_BUFFER_SIZE = 50;

    uint32_t m_bufferSum;
    uint16_t m_samplesBuffer[SAMPLE_BUFFER_SIZE];
    uint16_t m_recentSample;
    uint8_t m_dataPin;
    comp_func_t m_compensate;
};

#endif // ANALOG_SENSOR_H_