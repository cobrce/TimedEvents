#ifndef CONTROLLED_AVR_PORT_H_
#define CONTROLLED_AVR_PORT_H_

#include <avr/io.h>
#include <stdint.h>
#include "../../SharedCode/ValueController.h"

#include "AvrConsts.h"

class ControlledAvrPort : public IoItem<uint8_t>
{
private:
    volatile uint8_t *_port;
    volatile uint8_t *_ddr;
    volatile uint8_t *_pin;

public:
    ControlledAvrPort(PORTS::Port port, uint8_t mask = 0);
    void SetOutput(){};
    void SetInput(bool pullup = false){};
    uint8_t Read();
    void Write(uint8_t value);
};

ControlledAvrPort::ControlledAvrPort(PORTS::Port port, uint8_t mask)
{
    auto regs = GetPortRegisters(port);
    if (regs)
    {
        _port = regs[0];
        _pin = regs[1];
        _ddr = regs[2];
        *_ddr = mask;
    }
}

uint8_t ControlledAvrPort::Read()
{
    currentValue = *_pin;
    return currentValue;
}

void ControlledAvrPort::Write(uint8_t value)
{
    currentValue = value;
    *_port = value;
}

#endif