#ifndef VALUE_CONTROLLER_IO_H_
#define VALUE_CONTROLLER_IO_H_

#include <stdint.h>

template<typename T>
class IoInterface
{
public:
    virtual T Read() = 0;
    virtual void Write(T value) = 0;
    virtual void Toggle() = 0;
};

template<typename T>
class IoItem : public IoInterface<T>
{
protected:
    T currentValue;

public:
    virtual void SetOutput() = 0;
    virtual void SetInput(bool pullup = false) = 0;
    virtual T Read() = 0;
    virtual void Write(T value) = 0;
    virtual T Value() { return currentValue; };
    virtual void Toggle() { Write(currentValue == 0); }
};

#endif