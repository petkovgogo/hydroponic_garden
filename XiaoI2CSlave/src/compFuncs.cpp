#include "CompensationFuncs.h"

#include <cmath>

static constexpr float VREF = 3.3;                // analog reference voltage(Volt) of the ADC
static constexpr float ADC_RES = 4095.0;          // 12bit resolution
static constexpr float ADC_COEF = VREF / ADC_RES; // mapping coefficient

float CompensationFuncs::compensateTDSData(uint16_t rawValue)
{
    float temperature = 25; // TODO get actual reading from BME280

    float averageVoltage = rawValue * ADC_COEF;                           // read the analog value more stable by the median filtering algorithm, and convert to voltage value
    float compensationCoefficient = 1.0 + 0.02 * (temperature - 25.0);    // temperature compensation formula: fFinalResult(25^C) = fFinalResult(current)/(1.0+0.02*(fTP-25.0));
    float compensationVolatge = averageVoltage / compensationCoefficient; // temperature compensation

    return (133.42 * pow(compensationVolatge, 3) -
            255.86 * pow(compensationVolatge, 2) +
            857.39 * compensationVolatge) *
           0.5; // convert voltage value to tds value
}

float CompensationFuncs::compensatePHData(uint16_t rawValue)
{
    constexpr float OFFSET = 0.12;
    constexpr float PH_COEF = 14.0 / VREF;

    float averageVoltage = rawValue * ADC_COEF;

    return (VREF - averageVoltage) * PH_COEF + OFFSET;
}
