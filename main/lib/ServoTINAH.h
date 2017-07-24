#ifndef ServoTINAH_H
#define ServoTINAH_H

#include <avr/interrupt.h>
#include <Arduino.h>

#define MAX_SERVO_CHANNELS    (8U)   /* don't change! */
#define MAX_SERVO_ANGLE       (180U)

typedef struct
{
    bool enabled;
    uint8_t pin;
    volatile uint8_t* outputRegister;
    uint16_t angle;
    uint8_t compareValue;
    uint16_t overflowBeforeToggle;
} servo_t;

class ServoTINAH
{
public:
    ServoTINAH();
    uint8_t attach(uint8_t);
    void detach(void);
    bool attached(void);
    void write(uint16_t);
    uint16_t read(void);
private:
    uint8_t channel = 0;
    static uint8_t timerRunning;
    static uint8_t channelsUsed;
};

#endif