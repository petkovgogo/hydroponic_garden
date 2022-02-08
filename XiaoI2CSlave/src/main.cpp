#include <Arduino.h>
#include <Wire.h>
#include <cstdio>
#include "AnalogSensor.h"
#include "CompensationFuncs.h"

constexpr uint8_t LED_Y_PIN = PIN_LED;
constexpr uint8_t TDS_SENSOR_PIN = PIN_A2;
constexpr uint8_t PH_SENSOR_PIN = PIN_A3;
constexpr uint8_t I2C_ADDR = 0x2A;

enum SlaveCommand
{
    READ_TDS = 0x00,
    READ_PH = 0x01,
    UNDEF
} command;

void slaveReceive(int);
void slaveRespond();

AnalogSensor tds(TDS_SENSOR_PIN, CompensationFuncs::compensateTDSData);
AnalogSensor ph(PH_SENSOR_PIN, CompensationFuncs::compensatePHData);

void setup()
{
    pinMode(LED_Y_PIN, OUTPUT);

    digitalWrite(LED_Y_PIN, LOW);
    delay(250);
    digitalWrite(LED_Y_PIN, HIGH);

    Wire.begin(I2C_ADDR);
    Wire.onReceive(slaveReceive);
    Wire.onRequest(slaveRespond);
}

void loop()
{
    delay(1000);
}

void slaveReceive(int)
{
    switch (Wire.read())
    {
    case SlaveCommand::READ_TDS:
        command = READ_TDS;
        break;

    case SlaveCommand::READ_PH:
        command = READ_PH;
        break;

    default:
        command = UNDEF;
        break;
    }
}

void slaveRespond()
{
    uint16_t data = 0;

    switch (command)
    {
    case READ_TDS:
        data = tds.getMeasurement(); // implicit casting - float value not needed, data is in range 0 to 1000ppm
        break;

    case READ_PH:
        data = ph.getMeasurement(); // implicit casting - float value not needed, data is in range 0 to 14
        break;

    default:
        data = 0xFFFF; // uint16_t max value to indicate a command error
        break;
    }

    uint8_t buff[2];
    buff[0] = (data >> 8) & 0xFF;
    buff[1] = data & 0xFF;

    Wire.write(buff, 2);
}
