#ifndef AVR_CONSTS_H_
#define AVR_CONSTS_H_

#include <avr/io.h>

#define setBool(var, index, value) value ? (var |= _BV(index)) : (var &= ~(_BV(index)))

volatile uint8_t * PortsRegistersArray[][3] =
    {
#ifdef PORTA
        {&PORTA, &PINA, &DDRA},
#endif

#ifdef PORTB
        {&PORTB, &PINB, &DDRB},
#endif

#ifdef PORTC
        {&PORTC, &PINC, &DDRC},
#endif

#ifdef PORTD
        {&PORTD, &PIND, &DDRD},
#endif

#ifdef PORTE
        {&PORTE, &PINE, &DDRE},
#endif
};

namespace PORTS
{
    enum Port
    {
    #ifdef PORTA
        A,
    #endif

    #ifdef PORTB
        B,
    #endif

    #ifdef PORTC
        C,
    #endif

    #ifdef PORTD
        D,
    #endif

    #ifdef PORTE
        E,
    #endif
    };
}; // namespace PORTS

volatile uint8_t **GetPortRegisters(PORTS::Port port)
{
    return (volatile uint8_t **)&PortsRegistersArray[port];
}

#endif