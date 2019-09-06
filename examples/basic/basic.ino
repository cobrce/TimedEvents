#include <TimedEvents.h>


// controlled variables
ControlledArduinoPin led(LED_BUILTIN,OUTPUT);
ControlledArduinoPin btn(2,INPUT_PULLUP);
ControlledVar<int> counter;

// controllers
ValueController<uint8_t> ledController(led);
ValueController<int> counterController(counter);
ValueController<uint8_t> btnController(btn);

Timer tmr(750);
Timer tmr2(1100);
Timer tmr3(1000);

void setup()
{
    Serial.begin(9600);
    btnController.Debounce = 50; // ignore changes after 50ms from the last one
    delay(10); // to avoid the case where millis() == 0
    tmr.Start();
    tmr2.Start();
}

void loop()
{

    // example of accessing IO, blink without delay 
    if (ledController.TimeReached(500)) // toggles LED every 500ms
        ledController.Toggle();

    // example of separating the Timer from the ControlledArduinoPin
    // this way we can compare to multiple times
     // ps : we could also use multiple Controllers instead    
    if ((tmr.Reached(false) || tmr2.Reached(false)))
            led.Toggle(); // write directly to the ControlledArduinoPin
                          // instead of the Controller to not interfere with
                          // its time counting
    
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

    if (Serial.available())
    {
        Serial.read();
        tmr3.Start(true); // start timer with force restart, so it starts counting when the last characeter of the message is received
    }

    if (tmr3.Reached()) // checking a timer will reset or restart it, so in order to use this information further it should be saved
        Serial.println("1 second since message received");
}