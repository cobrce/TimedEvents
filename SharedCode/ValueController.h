#ifndef VALUE_CONTROLLER_H_
#define VALUE_CONTROLLER_H_
#include <stdint.h>
#include "ValueControllerIO.h"

template<typename T>
class ValueController : IoInterface<T>
{
private:
    IoItem<T> *item;
    unsigned long lastChange;
    unsigned long lastRead;
    uint8_t changed;

public:
    ValueController(IoItem<T> &item);
    T Read();
    void Write(T value);
    uint8_t Changed();
    unsigned long ChangedAt();
    void ResetChange();
    uint8_t TimeReached(unsigned long time);
    void Toggle();

    unsigned long Debounce; // in milliseconds
};

template<typename T>
ValueController<T>::ValueController(IoItem<T> &item)
{
    this->item = &item;
}

template<typename T>
uint8_t ValueController<T>::Changed()
{
    return changed;
}

template<typename T>
unsigned long ValueController<T>::ChangedAt()
{
    return lastChange;
}

template<typename T>
void ValueController<T>::ResetChange()
{
    changed = 0;
}

template<typename T>
void ValueController<T>::Write(T value)
{
    if (value != item->Value())
    {
        changed = true;
        lastChange = millis();
    }
    item->Write(value);
}

template<typename T>
T ValueController<T>::Read()
{
    unsigned long now = millis();
    auto prevVal = item->Value();
    // either debounce is disabled, or never read, or read long ago 
    if (!Debounce || lastRead == 0 || (now - lastRead) >= Debounce)
    {
        lastRead = now;
        auto value = item->Read();
        if (prevVal != value)
        {
            changed = true;
            lastChange = now;
        }
        return value;
    }
    else
    {
        changed = false;
        return prevVal;
    }
}

template<typename T>
uint8_t ValueController<T>::TimeReached(unsigned long time)
{
    return ((millis() - lastChange) >= time);
}

template<typename T>
void ValueController<T>::Toggle()
{
    changed = true;
    lastChange = millis();
    item->Toggle();
}

#endif