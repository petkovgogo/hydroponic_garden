#include "Relay.h"

#include <iostream>
#include <unistd.h>

int relayTest()
{
    constexpr uint32_t CHANNEL_COUNT = 3;

    GPIO ch1(17);
    GPIO ch2(27);
    GPIO ch3(22);

    ch1.setDirection(OUTPUT);
    ch2.setDirection(OUTPUT);
    ch3.setDirection(OUTPUT);

    GPIO *channels[CHANNEL_COUNT] = {&ch1, &ch2, &ch3};

    Relay rel(channels, CHANNEL_COUNT);

    rel.setState(1, HIGH);
    sleep (7);
    rel.setState(2, HIGH);
    sleep (7);
    rel.toggleState(3);
    sleep (7);
    rel.toggleState(2);
    sleep (7);
    
    std::cout << rel.getState(3) << std::endl;
    std::cout << rel.getState(2) << std::endl;

    // Error conditions
    rel.setState(42, HIGH);
    rel.toggleState(76);
    std::cout << rel.getState(64) << std::endl;

    return 0;
}
