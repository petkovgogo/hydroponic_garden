#include <Arduino.h>
#include <Wire.h>
#include <cstdio>
#include "AnalogSensor.h"
#include "CompensationFuncs.h"
#include "XiaoDefs.h"

constexpr uint8_t LED_Y_PIN = PIN_LED;
constexpr uint8_t TDS_SENSOR_PIN = PIN_A1;
constexpr uint8_t PH_SENSOR_PIN = PIN_A2;

Xiao_SlaveCmd command;

#ifdef DEBUG

int cnt = 1;

#endif

void slaveReceive(int);
void slaveRespond();

AnalogSensor tds(TDS_SENSOR_PIN, CompensationFuncs::compensateTDSData);
AnalogSensor ph(PH_SENSOR_PIN, CompensationFuncs::compensatePHData);

void setup()
{
    analogReadResolution(12);
    pinMode(LED_Y_PIN, OUTPUT);

    digitalWrite(LED_Y_PIN, LOW);
    delay(250);
    digitalWrite(LED_Y_PIN, HIGH);

    Wire.begin(XIAO_I2C_ADDR);
    Wire.onReceive(slaveReceive);
    Wire.onRequest(slaveRespond);

#ifdef DEBUG

    Serial.begin(9600);

#endif
}

void loop()
{
    delay(3950);
    ph.refresh();
    tds.refresh();

#ifdef DEBUG

    Serial.print(cnt++);
    Serial.print(": ");
    Serial.println(ph.getMeasurement());

    if (cnt > 15)
    {
        cnt = 0;
        Serial.println();
    }

#endif
}

void slaveReceive(int)
{
    switch (Wire.read())
    {
    case Xiao_SlaveCmd::READ_TDS:
        command = READ_TDS;
        break;

    case Xiao_SlaveCmd::READ_PH:
        command = READ_PH;
        break;

    default:
        command = UNDEF;
        break;
    }
}

void slaveRespond()
{
    float meas = 0.0;
    uint16_t data = 0;

    switch (command)
    {
    case READ_TDS:
        data = tds.getMeasurement(); // implicit casting - float value not needed, data is in range 0 to 1000ppm
        break;

    case READ_PH:
        meas = ph.getMeasurement();
        data = meas * 100;
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
