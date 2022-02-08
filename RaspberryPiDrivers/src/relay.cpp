#include "Relay.h"

#include <iostream>
#include <cstring>

#define VALID_CH(CH, CNT, RET_VAL)                                   \
    if (CH == 0 || CH > Relay::CNT)                         \
    {                                                                \
        std::cerr << "Invalid channel! Must be in the interval [1; " \
                  << CNT << "]" << std::endl;                        \
                                                                     \
        return RET_VAL;                                              \
    }

Relay::Relay(GPIO *channelPins[], uint32_t channelCount) : m_channelCount(channelCount)
{
    memset(m_channelPins, 0, MAX_CH_COUNT * sizeof(GPIO *));

    for (size_t i = 0; i < m_channelCount; i++)
    {
        m_channelPins[i] = channelPins[i];
    }
}

int Relay::setState(uint32_t channel, GPIO_STATE state)
{
    VALID_CH(channel, m_channelCount, 2);

    return m_channelPins[channel - 1]->setState(state);
}

int Relay::toggleState(uint32_t channel)
{
    VALID_CH(channel, m_channelCount, 2);

    return m_channelPins[channel - 1]->toggleState();
}

GPIO_STATE Relay::getState(uint32_t channel)
{
    VALID_CH(channel, m_channelCount, GPIO_STATE::UNDEF);

    return m_channelPins[channel - 1]->getState();
}
