#include "TimedEvents.h"

ArduinoPin led(LED_BUILTIN,OUTPUT);
TimedEvent ledController(led);

void setup()
{
    
}

void loop()
{
    if (ledController.TimeReached(500))
        ledController.Toggle();
}