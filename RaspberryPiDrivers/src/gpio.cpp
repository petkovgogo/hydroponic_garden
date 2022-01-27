/*
 * gpio.cpp
 *
 *  Created on: Dec 22, 2021
 *      Author: pi
 */

#include "GPIO.h"

#include <iostream>
#include <fstream>
#include <unistd.h>

const std::string GPIO::GPIO_PATH = "/sys/class/gpio/";

GPIO::GPIO(uint8_t number) : m_number(number), m_direction(INPUT)
{
    m_path = std::string(
        GPIO_PATH + "gpio" + std::to_string(static_cast<int>(m_number)) + "/");

    exportGPIO();

    usleep(250000);
}

GPIO::~GPIO()
{
    unexportGPIO();
}

GPIO::GPIO(GPIO &gpio) : m_number(gpio.m_number), m_direction(gpio.m_direction)
{
}

int GPIO::setDirection(GPIO_DIRECTION direction)
{
    if (direction)
    {
        return write(m_path, "direction", "out");
    }

    return write(m_path, "direction", "in");
}

int GPIO::setState(GPIO_STATE state)
{
    return write(m_path, "value", std::to_string(state));
}

int GPIO::toggleState()
{
    switch (getState())
    {
    case GPIO_STATE::LOW:
        return setState(GPIO_STATE::HIGH);

    case GPIO_STATE::HIGH:
        return setState(GPIO_STATE::LOW);

    default:
        return GPIO_STATE::UNDEF;
    }
}

GPIO_STATE GPIO::getState()
{
    std::string result = read(m_path, "value");

    if (result == "0")
    {
        return GPIO_STATE::LOW;
    }

    if (result == "1")
    {
        return GPIO_STATE::HIGH;
    }

    std::cerr << "GPIO: There was a problem reading GPIO"
              << static_cast<int>(m_number)
              << std::endl;

    return GPIO_STATE::UNDEF;
}

int8_t GPIO::exportGPIO()
{
    return write(GPIO_PATH, "export", std::to_string(m_number));
}

int8_t GPIO::unexportGPIO()
{
    return write(GPIO_PATH, "unexport", std::to_string(m_number));
}

int8_t GPIO::write(std::string path, std::string file, std::string value)
{
    std::ofstream target(path + file);

    if (!target.is_open())
    {
        std::cerr << "GPIO: failed to open file " << std::endl;
        return -1;
    }

    target << value;
    target.close();

    return 0;
}

std::string GPIO::read(std::string path, std::string file)
{
    std::ifstream target(path + file);

    if (!target.is_open())
    {
        std::cerr << "GPIO: failed to open file " << std::endl;
        return "\0";
    }

    std::string value;
    getline(target, value);
    target.close();

    return value;
}
