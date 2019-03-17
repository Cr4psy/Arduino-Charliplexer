
#ifndef LEDARRAY_H_
#define LEDARRAY_H_

#include "Arduino.h"


class LEDArray
{
    // LED_PATTERN gives the state of the pin of the 74HC595 in order to light the led 0-8 (0 being all led off)
    const byte LED_PATTERN[17] = {0b00001111,
                                0b10001110,0b01001110,0b00101110,0b00011110,
                                0b10001101,0b01001101,0b00101101,0b00011101,
                                0b10001011,0b01001011,0b00101011,0b00011011,
                                0b10000111,0b01000111,0b00100111,0b00010111};
    // Interrupt is called once a millisecond, to update the LEDs
    volatile int cycleCount = 0;
    volatile byte ledsState;
    volatile byte ledsStatePrev;

    int nbLEDs = 16;

    // 74HC595 Connections
    //ST_CP
    int latchPin = 7;
    //SH_CP
    int clockPin = 12;
    //DS
    int dataPin = 11;

  private:
    void writeByte(byte b);

  public:
    LEDArray();
    void ledCycle();
    void setLedsState(byte);
    void setNbLEDs(int nb);
};


#endif