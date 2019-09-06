#ifndef VALUE_CONTROLLER_H_
#define VALUE_CONTROLLER_H_
#include <stdint.h>
#include "ValueControllerIO.h"

template <typename T>
class TimeController : public IoInterface<T>
{
protected:
    unsigned long lastChange;
    uint8_t changed;

    void SetChangedNow();

public:
    TimeController(){}
    virtual T Read() = 0;
    virtual void Write(T value) = 0;
    virtual void Toggle() = 0;

    uint8_t Changed();
    unsigned long ChangedAt();
    void ResetChange();
    uint8_t TimeReached(unsigned long time);
};

template <typename T>
uint8_t TimeController<T>::Changed()
{
    return changed;
}

template <typename T>
unsigned long TimeController<T>::ChangedAt()
{
    return lastChange;
}

template <typename T>
void TimeController<T>::ResetChange()
{
    changed = 0;
}

template <typename T>
void TimeController<T>::SetChangedNow()
{
    this->changed = true;
    this->lastChange = millis();
}

template <typename T>
uint8_t TimeController<T>::TimeReached(unsigned long time)
{
    return ((millis() - lastChange) >= time);
}

template <typename T>
class ValueController : public TimeController<T>
{
private:
    IoItem<T> *item;
    unsigned long lastRead;

public:
    ValueController(IoItem<T> &item);
    T Read();
    void Write(T value);
    void Toggle();

    unsigned long Debounce; // in milliseconds
};

template <typename T>
ValueController<T>::ValueController(IoItem<T> &item)
{
    this->item = &item;
}

template <typename T>
void ValueController<T>::Write(T value)
{
    if (value != item->Value())
        this->SetChangedNow();
    item->Write(value);
}

template <typename T>
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
            this->SetChangedNow();
        return value;
    }
    else
    {
        this->changed = false;
        return prevVal;
    }
}

template <typename T>
void ValueController<T>::Toggle()
{
    this->SetChangedNow();
    item->Toggle();
}

#endif