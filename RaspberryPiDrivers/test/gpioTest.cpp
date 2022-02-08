/*
 * gpioTest.cpp
 *
 *  Created on: Dec 23, 2021
 *      Author: pi
 */

#include "GPIO.h"

#include <iostream>
#include <unistd.h>

int gpioTest()
{
    GPIO led(4);

    led.setDirection(GPIO_DIRECTION::OUTPUT);

    for(int i = 0; i < 10; ++i)
    {
        led.setState(GPIO_STATE::HIGH);
        std::cout << led.getState() << std::endl;
        sleep(2);

        led.setState(GPIO_STATE::LOW);
        std::cout << led.getState() << std::endl;
        sleep(2);
    }

    led.toggleState();
    sleep(5);
    led.toggleState();

    return 0;
}

