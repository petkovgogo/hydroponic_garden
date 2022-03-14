/*
 * GPIO.h
 *
 *  Created on: Dec 22, 2021
 *      Author: georgip
 */

#ifndef GPIO_H_
#define GPIO_H_

#include <string>

/** @name GPIO value defs */
enum GPIO_DIRECTION { INPUT = 0, OUTPUT = 1 };
enum GPIO_STATE { LOW = 0, HIGH = 1, UNDEF = 2 };

class GPIO
{
public:
    /** @name Path to gpio in sysfs */
    static const std::string GPIO_PATH;

    /**
     * @brief Initialize a new or refer to an already exported GPIO
     * 
     * @param[in] gpio : The GPIO pin number
     * 
     * @note This constructor accepts the GPIO bus number of the pin, not the physical one
     */
    GPIO(uint8_t gpio);

    /** @brief Copy-constructor */
    GPIO(GPIO &);

    /** @brief Unexport the pin, if exported by constructor, before destroying the object */
    ~GPIO();

    int setDirection(GPIO_DIRECTION);
    int setState(GPIO_STATE);
    int toggleState();
    GPIO_STATE getState();

private:

    std::string m_path;
    uint8_t m_number;
    uint8_t m_initFlag;

    int8_t exportGPIO();
    int8_t unexportGPIO();
    int8_t write(std::string path, std::string file, std::string value);
    std::string read(std::string path, std::string file);
};

#endif /* GPIO_H_ */
