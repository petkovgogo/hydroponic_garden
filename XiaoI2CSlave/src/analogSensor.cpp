#include "TDSSensor.h"

#include <Arduino.h>
#include <cstring>

AnalogSensor::AnalogSensor(uint8_t dataPin, comp_func_t compensationFunc) : m_dataPin(dataPin), m_compensate(compensationFunc)
{
    pinMode(m_dataPin, INPUT);
    memset(m_samplesBuffer, 0, SAMPLE_BUFFER_SIZE);
}

void AnalogSensor::refresh()
{
    static uint32_t sampleIndex = 0;

    m_bufferSum -= m_samplesBuffer[sampleIndex];
    m_samplesBuffer[sampleIndex] = analogRead(m_dataPin);
    m_bufferSum += m_samplesBuffer[sampleIndex++];
    
    sampleIndex %= SAMPLE_BUFFER_SIZE; // reset the index if the buffer is full
}

float AnalogSensor::getMeasurement()
{
    m_recentSample = m_bufferSum / SAMPLE_BUFFER_SIZE;

    return m_compensate(m_recentSample);
}
