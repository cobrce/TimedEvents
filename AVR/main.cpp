#define F_CPU 8000000

#include <avr/io.h>
#include <util/delay.h>

#include "millis.h"

#include "TimedEventsAvr.h"

ControlledAvrPort B(PORTS::B, 0xff);     // PORTB is used as binary counters
ControlledAvrPin btn(PORTS::C, 0);       // input
ControlledAvrPin led(PORTS::C, 1, true); // output

PortController BController(B);
PinController BtnController(btn);
PinController LedController(led);

Timer tmr(750);
Timer tmr2(1100);

int main()
{
    // should initialize millis manually because not arduino
    millis_init();
    sei();

    // avoid millis() returns 0 (not necessary anymore)
    // _delay_ms(10);

    BtnController.Debounce = 50;
    LedController.Write(0); // init with 0 to start timer counting
    BController.Write(0);   // same
    btn.Write(1);           // set pull-up, writing directly to ControlledAvrPin (not to ValueController) doesn't count time

    uint8_t stopBlinking = false;

    // don't forget to start the timers when needed
    tmr.Start();
    tmr2.Start();

    while (1)
    {
        // example of accessing IO, blink without delay
        if (!stopBlinking && LedController.TimeReached(500)) // toggles LED every 500ms
            LedController.Toggle();

        // example of separating the Timer from the ControlledAvrPin
        // this way we can compare to multiple times
        // ps : we could also use multiple Controllers instead
        if ((tmr.Reached(false) || tmr2.Reached(false)) && !stopBlinking)
            led.Toggle(); // write directly to the ControlledAvrPin
                          // instead of the Controller to not interfere with
                          // its time counting

        // example of accessing PORT, time counter without delay
        if (BController.TimeReached(1000)) // increment counter every 1 second
            BController.Write(B.Value() + 1);

        // example of IO changed detection with software debounce
        if (BtnController.Read() && BtnController.Changed())
            stopBlinking = !stopBlinking;
    }
}