#include <LEDArray.h>

// Constructor
LEDArray::LEDArray() {
    pinMode(latchPin, OUTPUT);
    pinMode(clockPin, OUTPUT);
    pinMode(dataPin, OUTPUT);

    // Timer0 is already used for millis() - we'll just interrupt somewhere
    // in the middle and call the "Compare A" function below
    OCR0A = 0xAF;
    TIMSK0 |= _BV(OCIE0A);
}


void LEDArray::setLedsState(uint16_t on){
    ledsState = on;
}

void LEDArray::setNbLEDs(int nb){
    nbLEDs = nb;
}

void LEDArray::writeByte(byte b){
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin,clockPin, LSBFIRST, b);
  digitalWrite(latchPin,HIGH);
}

void LEDArray::ledCycle(){
    cycleCount = cycleCount+1;
    if(cycleCount == 1){
        ledsStatePrev = ledsState;
    }

    if (ledsStatePrev == 0){
        writeByte(LED_PATTERN[0]);
    } else if((ledsStatePrev & 0b01) == 0b01){
        writeByte(LED_PATTERN[cycleCount]);
    }

    ledsStatePrev = ledsStatePrev >> 1;
    if (cycleCount==nbLEDs) {
        cycleCount=0;
    }
}
