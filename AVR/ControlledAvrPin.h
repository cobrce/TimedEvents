#ifndef CONTROLLED_AVR_PIN_H_
#define CONTROLLED_AVR_PIN_H_

#include <avr/io.h>
#include <stdint.h>
#include "../src/TimedEventsIO.h"

#include "AvrConsts.h"

class ControlledAvrPin : public IoItem<uint8_t>
{
private:
    uint8_t _pinNumber;
    volatile uint8_t *_port;
    volatile uint8_t *_ddr;
    volatile uint8_t *_pin;

public:
    ControlledAvrPin(PORTS::Port port, uint8_t pinNumber, uint8_t isOutput = false);
    // ControlledAvrPin(volatile uint8_t *port, volatile uint8_t *pin, volatile uint8_t *ddr, uint8_t pinNumber);
    // ControlledAvrPin(volatile uint8_t *port, volatile uint8_t *pin, volatile uint8_t *ddr, uint8_t pinNumber, uint8_t isOutput);
    void SetOutput();
    void SetInput(bool pullup = false);
    uint8_t Read();
    void Write(uint8_t value);
};

ControlledAvrPin::ControlledAvrPin(PORTS::Port port, uint8_t pinNumber, uint8_t isOutput)
{
    auto regs = GetPortRegisters(port);
    if (regs)
    {
        _port = regs[0];
        _pin = regs[1];
        _ddr = regs[2];
        _pinNumber = pinNumber;
        if (isOutput)
            SetOutput();
        else
            SetInput();
    }
}

void ControlledAvrPin::SetOutput()
{
    setBool(*_ddr, _pinNumber, 1);
}
void ControlledAvrPin::SetInput(bool pullup)
{
    setBool(*_ddr, _pinNumber, 0);
    setBool(*_port, _pinNumber, pullup);
}

uint8_t ControlledAvrPin::Read()
{
    currentValue = (*_pin >> _pinNumber) & 1;
    return currentValue;
}

void ControlledAvrPin::Write(uint8_t value)
{
    currentValue = (value != 0);
    setBool(*_port, _pinNumber, value);
}

#endif