#include "Relay.h"

#include <iostream>

int main()
{
    constexpr uint32_t CHANNEL_COUNT = 3;

    GPIO ch1(17);
    GPIO ch2(27);
    GPIO ch3(22);
    GPIO *channels[CHANNEL_COUNT] = {&ch1, &ch2, &ch3};

    Relay relay(channels, CHANNEL_COUNT);

    std::cout << "Content-Type: application/json\n\n";
    std::cout << "{\n";
    std::cout << "    \"ch1:\" \"" << relay.getState(1) << "\"\n";
    std::cout << "    \"ch2:\" \"" << relay.getState(2) << "\"\n";
    std::cout << "    \"ch3:\" \"" << relay.getState(3) << "\"\n";
    std::cout << "}" << std::endl;

    return 0;
}
