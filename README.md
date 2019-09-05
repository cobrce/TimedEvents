# TimedEvents
An Arduino/non-arduino-AVR library to keep track of when events occured, like when an input changed, when an output/variable was written...etc.
The point of this library is that the time is counted with millis and not delay/_delay_ms, so several events can be timed **easily** without blocking each other


## How it works
The library is divided into 2 entities : 
### The IoItem :
 * is an encapsulation of variable, a pin or port (for non-arduino)
 * it offers an interface for functions to read/write/toggle/change IO direction/get current value (last read/written value)
 * it stores information of the real target in case of pin/port, and the current value (in memory)
 
### The Controller : 
 * is used to store the last time IoItem was changed either by read or write
 * has functions to read/write/toggle the IoItem
 * has functions to check for changes and how long ago the change was done
 * implements a software debounce (when an input changes, its value is not updated during the debounce time)
 
## How to use :
 * Create an instance of the IoItem you want to control
 * Create an instance of a controller for that IoItem
 * use the controller to read/write/toggle
 
 ``` C++
 #include <TimedEvents.h>
 
 // IoItems
 ControlledArduinoPin led(LED_BUILTIN,OUTPUT);
 ControlledArduinoPin btn(2,INPUT_PULLUP);
 
 // Controllers
 ValueController<uint8_t> ledController(led);
 ValueController<uint8_t> btnController(btn);
 
 void setup()
 {
    Serial.begin(9600);
    delay(5); // to avoid millis returning 0
    btnController.Debounce = 50; // set debounce
 }
 
 void loop()
 {
    if (ledController.TimeReached(500)) // toggles LED every 500ms
        ledController.Toggle();
        
    btnController.Read(); // should read periodically to detect change and save when happened
    
    if (btnController.Changed()) // detects all variations
                                 // in order to detect for example rising edge only include btnController.Read in the condition 
                                 // or check btn.Value()
    {
        Serial.print("Value state ");
        Serial.println(btn.Value() ? "ON" : "OFF");
    }
 } 
 ```
 
#### Notes:
 * In order to check for an input change it must be read periodically
 * Any read/write/toggle done directly to IoItem are ignored by the controller, so whether it changed and when it changed are both not updated
 * The non-arduino version needs to include an implementation of millis and initialize it (a [modified copy][millis] from the [Arduino repo][millis-repo] is provided)
 * Since the library detects that a changed occured by having its timestamp no null, it's advised to use a delay at the beginning of the program to avoid millis returning 0

[millis]: AVR/millis.h
[millis-repo]: https://github.com/zkemble/millis/blob/master/arduino/millis/millis.cpp
