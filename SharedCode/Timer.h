#ifndef TIMER_H_
#define TIMER_H_

#include "ValueController.h"
#include "ControlledVariables.h"

ControlledVar<uint8_t> _dummyVar;

class Timer
{
private:
    ValueController<uint8_t> controller;
    unsigned long time;

public:
    Timer(unsigned long time);
    void Start();
    void Reset();
    uint8_t Reached(bool stop = true); // if this variable is false the timer will restart
};

Timer::Timer(unsigned long time) : controller(ValueController<uint8_t>(_dummyVar))
{
    this->time = time;
}

void Timer::Start()
{
    auto oldSreg = SREG;
    cli();
    controller.Toggle();
    SREG = oldSreg;
}

void Timer::Reset()
{
    controller.ResetChange();
}

uint8_t Timer::Reached(bool stop)
{
    // since start will do toggle, which make controller.Changed() true
    // no other write/read/toggle are done to the controller so the "Changed" state is preserved
    // therefore we consider controller.Changed() the equivalent of "Is the timer running?"

    // Is the timer running and the time reached the value
    auto reached = controller.Changed() && controller.TimeReached(this->time);
    if (reached)
    {
        if (stop) // either stop the time or restart it
            controller.ResetChange();
        else
            Start();
    }
    return reached;
}

#endif