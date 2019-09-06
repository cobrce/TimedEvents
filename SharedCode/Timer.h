#ifndef TIMER_H_
#define TIMER_H_

#include "ValueController.h"
#include "ControlledVariables.h"

// ControlledVar<uint8_t> _dummyVar;

// class TimerBase : public TimeController<uint8_t>
// {
//     public:
//     TimerBase(){}
    
    
// };

class Timer : TimeController<uint8_t>
{
private:
    unsigned long time;

    uint8_t Read() {return 0;};
    void Write(uint8_t value) {};
    void Toggle() {SetChangedNow();};

public:
    Timer(unsigned long time = 0);
    void Start(uint8_t forceRestart = false);
    void SetDelay(unsigned long time);
    void Reset();
    uint8_t IsRunning() { return this->Changed();/* return controller.Changed();*/ }
    uint8_t Reached(bool stop = true); // if this parameter is false the timer will restart
};

Timer::Timer(unsigned long time)/* : controller(ValueController<uint8_t>(_dummyVar))*/
{
    this->time = time;
}

void Timer::SetDelay(unsigned long time)
{
    this->time = time;
}

void Timer::Start(uint8_t forceRestart)
{
    if (!this->Changed() || forceRestart) // either not running or forced to restart
        this->SetChangedNow();
}

void Timer::Reset()
{
    this->ResetChange();
}

uint8_t Timer::Reached(bool stop)
{
    // since start will do SetChangedNow, which makes the function this->Changed() returns true
    // no other SetChangedNow() and ResetChange() are called, so the "Changed" state is preserved
    // therefore we consider this->Changed() as the equivalent of "Is the timer running?"

    // Is the timer running? and did the time reached the value?
    auto reached = this->Changed() && this->TimeReached(this->time);
    if (reached)
    {
        if (stop) // either stop the timer or restart it
            this->ResetChange();
        else
            Start(true);
    }
    return reached;
}

#endif
