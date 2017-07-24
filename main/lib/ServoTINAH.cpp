#include "ServoTINAH.h"
#include <Arduino.h>

/* These IO macros are about 30-60 times faster than digitalWrite */
#define WRITE_LOW(x) *(servo[x].outputRegister) &= ~servo[x].pin
#define WRITE_HIGH(x) *(servo[x].outputRegister) |= servo[x].pin

/* Converts an angle to timer comparison value */
const uint16_t ANGLE_TO_TIMER[] = {0, 3, 6, 8, 11, 14, 17, 20, 23, 25, 28, 31, 34, 37, 40, 42, 45, 48, 51, 54, 57, 59, 62, 65, 68, 71, 74, 76, 79, 82, 85, 88, 91, 93, 96, 99, 102, 105, 107, 110, 113, 116, 119, 122, 124, 127, 130, 133, 136, 139, 141, 144, 147, 150, 153, 156, 158, 161, 164, 167, 170, 173, 175, 178, 181, 184, 187, 190, 192, 195, 198, 201, 204, 206, 209, 212, 215, 218, 221, 223, 226, 229, 232, 235, 238, 240, 243, 246, 249, 252, 254, 257, 260, 263, 266, 269, 272, 274, 277, 280, 283, 286, 289, 291, 294, 297, 300, 303, 306, 308, 311, 314, 317, 320, 322, 325, 328, 331, 334, 337, 339, 342, 345, 348, 351, 354, 356, 359, 362, 365, 368, 371, 373, 376, 379, 382, 385, 388, 390, 393, 396, 399, 402, 405, 407, 410, 413, 416, 419, 421, 424, 427, 430, 433, 436, 438, 441, 444, 447, 450, 453, 455, 458, 461, 464, 467, 470, 472, 475, 478, 481, 484, 487, 489, 492, 495, 498, 501, 504, 506, 509, };

/* Initialize static class variables */
uint8_t ServoTINAH::timerRunning = 0;
uint8_t ServoTINAH::channelsUsed = 0;

static volatile servo_t servo[MAX_SERVO_CHANNELS];
static volatile uint8_t currentChannel = 0;
static volatile uint8_t overflows = 2;

ISR (TIMER2_OVF_vect)
{
    overflows = overflows >= 2 ? 0 : overflows + 1;
    if (overflows == 0)
    {
        if (servo[currentChannel].enabled)
        {
            WRITE_LOW(currentChannel);
        }
        currentChannel = currentChannel >= (MAX_SERVO_CHANNELS - 1) ? 0 : currentChannel + 1;
        if (servo[currentChannel].enabled)
        {
            WRITE_HIGH(currentChannel);
        }
        OCR2 = servo[currentChannel].compareValue;
        TCNT2 = 128;
    }
}

ISR (TIMER2_COMP_vect)
{
    if (servo[currentChannel].enabled)
    {
        if (overflows == 1 && !servo[currentChannel].overflowBeforeToggle)
        {
            WRITE_LOW(currentChannel);
        }
        else if (overflows == 2 && servo[currentChannel].overflowBeforeToggle)
        {
            WRITE_LOW(currentChannel);
        }
    }
}

void initializeTimer2()
{
    cli();
    /* Reset timer and compare counters */
    TCNT2 = 0;
    OCR2 = 0xFF;
    /* Prescaler = 64 */
    TCCR2 = 0;
    TCCR2 |= (1 << CS21) | (1 << CS20);
    /* Fast PWM mode */
    TCCR2 |= (1 << WGM21) | (1 << WGM20);
    /* Enable output compare interrupt */
    TIMSK |= 1 << OCIE2;
    /* Enable timer overflow interrupt */
    TIMSK |= 1 << TOIE2;
    sei();
}

ServoTINAH::ServoTINAH()
{
    if (this->channelsUsed < MAX_SERVO_CHANNELS)
    {
        this->channel = this->channelsUsed;
        servo[this->channel].enabled = false;
        servo[this->channel].pin = 0;
        servo[this->channel].outputRegister = (volatile uint8_t*)0;
        servo[this->channel].compareValue = 0;
        servo[this->channel].overflowBeforeToggle = 0;
        channelsUsed++;
    }
}

uint8_t ServoTINAH::attach(uint8_t arduinoPin)
{
    uint8_t pin  = digitalPinToBitMask(arduinoPin);
    uint8_t port = digitalPinToPort(arduinoPin);
    if (port == NOT_A_PIN) return false;
    volatile uint8_t* outputRegister = portOutputRegister(port);
    pinMode(arduinoPin, OUTPUT);

    servo[this->channel].enabled = true;
    servo[this->channel].pin  = pin;
    servo[this->channel].outputRegister = outputRegister;
    servo[this->channel].angle = 0;

    if (!this->timerRunning)
    {
        this->timerRunning = true;
        initializeTimer2();
    }
    return true;
}

void ServoTINAH::detach()
{
    if (servo[this->channel].enabled)
    {
        WRITE_LOW(this->channel);
        servo[this->channel].angle = 0;
        servo[this->channel].enabled = false;
    }
}

bool ServoTINAH::attached(void)
{
    return servo[this->channel].enabled;
}

void ServoTINAH::write(uint16_t angle)
{
    servo[this->channel].angle                = angle > MAX_SERVO_ANGLE ? MAX_SERVO_ANGLE : angle;
    servo[this->channel].overflowBeforeToggle = ANGLE_TO_TIMER[servo[this->channel].angle] >= 0xFF;
    servo[this->channel].compareValue         = ANGLE_TO_TIMER[servo[this->channel].angle] % 0xFF;
}

uint16_t ServoTINAH::read(void)
{
    return servo[this->channel].angle;
}