#ifndef CONTROLLED_POINTER_H_
#define CONTROLLED_POINTER_H_
#include "ValueController.h"

template <typename T>
class ControlledPtr : public IoItem<T>
{
    private:
    T * ptr;
public:
    ControlledPtr(T * ptr) { this->ptr = ptr; }
    virtual void SetOutput(){};
    virtual void SetInput(bool pullup = false){};
    virtual T Read() { return Value(); }
    virtual void Write(T value);
    virtual T Value() { return this->*ptr; };
    virtual void Toggle() { Write(this->*ptr == 0); }
};

template <typename T>
void ControlledPtr<T>::Write(T value)
{
    this->*ptr = value;
}

#endif