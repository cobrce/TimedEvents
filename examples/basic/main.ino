#include <TimedEvents.h>
#include <ArduinoPins.h>
#include <ControlledVariables.h>


// controlled variables
ControlledArduinoPin led(LED_BUILTIN,OUTPUT);
ControlledArduinoPin btn(2,INPUT_PULLUP);
ControlledVar<int> counter;

// controllers
ValueController<uint8_t> ledController(led);
ValueController<int> counterController(counter);
ValueController<uint8_t> btnController(btn);

void setup()
{
    Serial.begin(9600);
    btnController.Debounce = 50; // ignore changes after 50ms from the last one
    delay(10); // to avoid the case where millis() == 0
}

void loop()
{

    // example of accessing IO, blink without delay 
    if (ledController.TimeReached(500)) // toggles LED every 500ms
        ledController.Toggle();
    
    // example of accessing variable, time counter without delay
    if(counterController.TimeReached(1000)) // writes a message every 1 second
    {
        counterController.Write(counter.Value()+1);
        Serial.print(counter.Value());
        Serial.println(" seconds since started");
    }

    // example of IO changed detection with software debounce 
    btnController.Read();
    if (btnController.Changed())
    {
        Serial.print("Value state ");
        Serial.println(btn.Value() ? "ON" : "OFF");
    }
}