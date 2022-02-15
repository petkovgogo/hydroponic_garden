#include "Relay.h"

#include <iostream>
#include <string>
#include <cgicc/Cgicc.h>

int main()
{
    constexpr uint32_t CHANNEL_COUNT = 3;

    cgicc::Cgicc cgi;

    GPIO ch1(17);
    GPIO ch2(27);
    GPIO ch3(22);
    GPIO *channels[CHANNEL_COUNT] = {&ch1, &ch2, &ch3};

    Relay relay(channels, CHANNEL_COUNT);

    cgicc::form_iterator it_CH1 = cgi.getElement("ch1");
    cgicc::form_iterator it_CH2 = cgi.getElement("ch2");
    cgicc::form_iterator it_CH3 = cgi.getElement("ch3");

    if (it_CH1 != cgi.getElements().end())
    {
        relay.setState(1, stoi(**it_CH1) ? GPIO_STATE::HIGH : GPIO_STATE::LOW);
    }

    if (it_CH2 != cgi.getElements().end())
    {
        relay.setState(2, stoi(**it_CH2) ? GPIO_STATE::HIGH : GPIO_STATE::LOW);
    }

    if (it_CH3 != cgi.getElements().end())
    {
        relay.setState(3, stoi(**it_CH3) ? GPIO_STATE::HIGH : GPIO_STATE::LOW);
    }

    std::cout << "Content-Type: application/json\n\n";
    std::cout << "{\n";
    std::cout << "    \"ch1:\" \"" << relay.getState(1) << "\"\n";
    std::cout << "    \"ch2:\" \"" << relay.getState(2) << "\"\n";
    std::cout << "    \"ch3:\" \"" << relay.getState(3) << "\"\n";
    std::cout << "}" << std::endl;

    return 0;
}
