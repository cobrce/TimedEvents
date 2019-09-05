#ifndef CONTROLLED_VARIABLES_H_
#define CONTROLLED_VARIABLES_H_
#include "ValueController.h"

template <typename T>
class ControlledVar : public IoItem<T>
{
    // private:
    // T var;
public:
    ControlledVar(){};
    ControlledVar(T &initialValue) { Write(initialValue); }
    ControlledVar(T initialValue) { Write(initialValue); }
    virtual void SetOutput(){};
    virtual void SetInput(bool pullup = false){};
    virtual T Read() { return Value(); }
    virtual void Write(T value);
    virtual T Value() { return this->currentValue; };
    virtual void Toggle() { Write(this->currentValue == 0); }
};

template <typename T>
void ControlledVar<T>::Write(T value)
{
    this->currentValue = value;
}

#endif