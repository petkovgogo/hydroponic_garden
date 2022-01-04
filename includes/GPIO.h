/*
 * GPIO.h
 *
 *  Created on: Dec 22, 2021
 *      Author: georgip
 */

#ifndef GPIO_H_
#define GPIO_H_

#include <string>

enum GPIO_DIRECTION { INPUT = 0, OUTPUT = 1 };
enum GPIO_STATE { LOW = 0, HIGH = 1, UNDEF = 2 };

class GPIO
{
public:
    static const std::string GPIO_PATH;

    GPIO (uint8_t gpio);
    GPIO (GPIO &);
    ~GPIO ();

    int setDirection (GPIO_DIRECTION);
    int setState (GPIO_STATE);
    GPIO_STATE getState ();

private:

    std::string m_path;
    uint8_t m_number;
    GPIO_DIRECTION m_direction;

    int8_t exportGPIO ();
    int8_t unexportGPIO ();
    int8_t write (std::string path, std::string file, std::string value);
    std::string read (std::string path, std::string file);
};

#endif /* GPIO_H_ */
