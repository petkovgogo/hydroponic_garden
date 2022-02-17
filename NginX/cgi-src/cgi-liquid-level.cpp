#include "GPIO.h"

#include <iostream>

int main()
{
    constexpr uint8_t SENSOR_PIN = 4;

    GPIO liquidLevel(SENSOR_PIN);
    liquidLevel.setDirection(GPIO_DIRECTION::INPUT);

    std::cout << "Content-Type: application/json\n\n";
    std::cout << "{\n";
    std::cout << "    \"state\": \"" << liquidLevel.getState() << "\"\n";
    std::cout << "}" << std::endl;

    return 0;
}
