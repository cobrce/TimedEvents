#ifndef AVR_CONSTS_H_
#define AVR_CONSTS_H_


#include <avr/io.h>

#define setBool(var, index, value) value ? (var |= _BV(index)) : (var &= ~(_BV(index)))


#ifdef PORTA
volatile uint8_t *PORTA_REGISTERS[] = {&PORTA, &PINA, &DDRA};
#endif

#ifdef PORTB
volatile uint8_t *PORTB_REGISTERS[] = {&PORTB, &PINB, &DDRB};
#endif

#ifdef PORTC
volatile uint8_t *PORTC_REGISTERS[] = {&PORTC, &PINC, &DDRC};
#endif

#ifdef PORTD
volatile uint8_t *PORTD_REGISTERS[] = {&PORTD, &PIND, &DDRD};
#endif

#ifdef PORTE
volatile uint8_t ** PORTE_REGISTERS = {&PORTE, &PINE, &DDRE};
#endif

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
};

volatile uint8_t ** GetPortRegisters(PORTS::Port port)
{
     switch (port)
    {
#ifdef PORTA
    case PORTS::A:
        return (volatile uint8_t **) &PORTA_REGISTERS;
        break;
#endif

#ifdef PORTB
    case PORTS::B:
        return (volatile uint8_t **) &PORTB_REGISTERS;
        break;
#endif

#ifdef PORTC
    case PORTS::C:
        return (volatile uint8_t **) &PORTC_REGISTERS;
        break;
#endif

#ifdef PORTD
    case PORTS::D:
        return (volatile uint8_t **) &PORTD_REGISTERS;
        break;
#endif

#ifdef PORTE
    case PORTS::E:
        return &PORTE_REGISTERS;
        break;
#endif

    default:
        break;
    }
    return 0;
}

#endif