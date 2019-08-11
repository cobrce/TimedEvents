#ifndef TIMEd_EVENTS_H_
#define TIMEd_EVENTS_H_
#include <stdint.h>
#include "TimedEventsIO.h"

class TimedEvent : IoInterface
{
private:
    IoItem *item;
    unsigned long lastChange;
    unsigned long lastRead;
    uint8_t changed;

public:
    TimedEvent(IoItem &item);
    uint8_t Read();
    void Write(uint8_t value);
    uint8_t Changed();
    unsigned long ChangedAt();
    void ResetChange();
    uint8_t TimeReached(unsigned long time);
    void Toggle();

    unsigned long Debounce; // in milliseconds
};

TimedEvent::TimedEvent(IoItem &item)
{
    this->item = &item;
}

uint8_t TimedEvent::Changed()
{
    return changed;
}

unsigned long TimedEvent::ChangedAt()
{
    return lastChange;
}

void TimedEvent::ResetChange()
{
    changed = 0;
}

void TimedEvent::Write(uint8_t value)
{
    if (value != item->Value())
    {
        changed = true;
        lastChange = millis();
    }
    item->Write(value);
}

uint8_t TimedEvent::Read()
{
    unsigned long now = millis();
    auto prevVal = item->Value();
    if (Debounce && lastRead != 0 && (now - lastRead) >= Debounce)
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

uint8_t TimedEvent::TimeReached(unsigned long time)
{
    return ((millis() - lastChange) >= time);
}

void TimedEvent::Toggle()
{
    changed = true;
    lastChange = millis();
    item->Toggle();
}

#endif