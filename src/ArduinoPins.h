#ifndef ARDUINO_PINS_H_
#define ARDUINO_PINS_H_

#include <stdint.h>
#include "../SharedCode/ValueController.h"

class ControlledArduinoPin : public IoItem<uint8_t>
{
    private:
    uint8_t pinNumber;
    public:
    ControlledArduinoPin(uint8_t pinNumber);
    ControlledArduinoPin(uint8_t pinNumber,uint8_t mode);
    void SetOutput();
    void SetInput(bool pullup = false);
    uint8_t Read();
    void Write(uint8_t value);
};


ControlledArduinoPin::ControlledArduinoPin(uint8_t pinNumber)
{
    this->pinNumber =pinNumber;
}

ControlledArduinoPin::ControlledArduinoPin(uint8_t pinNumber,uint8_t mode)
{
    this->pinNumber = pinNumber;
    pinMode(pinNumber,mode);
}
void ControlledArduinoPin::SetOutput()
{
    pinMode(pinNumber,OUTPUT);
}
void ControlledArduinoPin::SetInput(bool pullup)
{
    pinMode(pinNumber,pullup ? INPUT_PULLUP :  INPUT);
}

uint8_t ControlledArduinoPin::Read()
{
    currentValue =  digitalRead(pinNumber);
    return currentValue;
}

void ControlledArduinoPin::Write(uint8_t value)
{
    currentValue = value;
    digitalWrite(pinNumber,value);
}


#endif