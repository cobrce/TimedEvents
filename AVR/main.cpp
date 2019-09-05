#define F_CPU 8000000

#include <avr/io.h>
#include <util/delay.h>

#include "millis.h"

#include "../src/TimedEvents.h"
#include "../src/ControlledVariables.h"
#include "AvrPins.h"

ControlledAvrPort B(PORTS::B);           // PORTB is used as binary counters
ControlledAvrPin btn(PORTS::C, 0);       // input
ControlledAvrPin led(PORTS::C, 1, true); // output

ValueController<uint8_t> BController(B);
ValueController<uint8_t> BtnController(btn);
ValueController<uint8_t> LedController(led);

int main()
{
    // should initialize millis manually because not arduino
    millis_init();

     // avoid millis() returns 0
    _delay_ms(10);

    BtnController.Debounce = 50;
    LedController.Write(0); // init with 0 to start timer counting
    BController.Write(0); // same

    uint8_t stopBlinking = false;

    while (1)
    {
        // example of accessing IO, blink without delay
        if (!stopBlinking && LedController.TimeReached(500)) // toggles LED every 500ms
            LedController.Toggle();

        // example of accessing PORT, time counter without delay
        if (BController.TimeReached(1000)) // increment counter every 1ms
            BController.Write(B.Value() + 1);

        // example of IO changed detection with software debounce
        BtnController.Read();
        if (BtnController.Changed())
            stopBlinking = !stopBlinking;
    }
}