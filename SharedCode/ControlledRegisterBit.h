#ifndef CONTROLLED_REGISTER_H_
#define CONTROLLED_REGISTER_H_
#include "ValueController.h"


class ControlledRegBit : public IoItem<uint8_t>
{
    private:
    uint8_t& _reg;
    uint8_t pin;
public:
    ControlledRegBit(uint8_t& reg,uint8_t pin) : _reg(reg)  {this->pin = pin;}
    virtual void SetOutput(){};
    virtual void SetInput(bool pullup = false){};
    virtual uint8_t Read() { return Value(); }
    virtual void Write(uint8_t value);
    virtual uint8_t Value() { return  (_reg >> pin) & 1; };
    virtual void Toggle() { Write(Read() == 0); }
};

void ControlledRegBit::Write(uint8_t value)
{
    value ? (_reg |= _BV(pin)) : (_reg) &= ~(_BV(pin));
}

#endif