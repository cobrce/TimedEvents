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
    Timer(unsigned long time = 0);
    void Start(uint8_t forceRestart = false);
    void SetDelay(unsigned long time);
    void Reset();
    uint8_t IsRunning() { return controller.Changed(); }
    uint8_t Reached(bool stop = true); // if this parameter is false the timer will restart
};

Timer::Timer(unsigned long time) : controller(ValueController<uint8_t>(_dummyVar))
{
    this->time = time;
}

void Timer::SetDelay(unsigned long time)
{
    this->time = time;
}

void Timer::Start(uint8_t forceRestart)
{
    if (!controller.Changed() || forceRestart) // either not running or forced to restart
    {
        auto oldSreg = SREG;
        cli();
        controller.Toggle();
        SREG = oldSreg;
    }
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
        if (stop) // either stop the timer or restart it
            controller.ResetChange();
        else
            Start(true);
    }
    return reached;
}

#endif
