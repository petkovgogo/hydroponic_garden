#ifndef RELAY_H_
#define RELAY_H_

#include "GPIO.h"
#include <stdint.h>

class Relay
{
public:
    static constexpr uint32_t MAX_CH_COUNT = 16;

    Relay(GPIO *channelPins[], uint32_t channelCount);
    ~Relay() = default;

    int setState(uint32_t channel, GPIO_STATE);
    int toggleState(uint32_t channel);
    GPIO_STATE getState(uint32_t channel);

private:
    GPIO *m_channelPins[MAX_CH_COUNT];
    uint32_t m_channelCount;
};

#endif // RELAY_H_