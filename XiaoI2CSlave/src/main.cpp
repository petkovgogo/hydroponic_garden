#include <Arduino.h>
#include <Wire.h>
#include <cstdio>

constexpr uint8_t LED_Y_PIN = PIN_LED;
constexpr uint8_t SENSOR_PIN = PIN_A2;
constexpr uint8_t I2C_ADDR = 0x2A;
int command = 0;

void slaveReceive(int);
void slaveRespond();

void setup()
{
    pinMode(LED_Y_PIN, OUTPUT);
    pinMode(SENSOR_PIN, INPUT);

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
    command = Wire.read();
}

void slaveRespond()
{
    uint16_t data = command;
    uint8_t buff[2];
    buff[0] = (data >> 8) & 0xFF;
    buff[1] = data & 0xFF;

    Wire.write(buff, 2);
}
