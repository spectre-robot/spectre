#include <avr/interrupt.h>       
#include "lib/phys253.h"
#include <LiquidCrystal.h>

// GLOBAL VARIABLES
int direction = 1; // 1 for left surface, -1 for right. dont worry abt this for now.
int qrd_threshold = 200;
int ir_threshold = 30;
int base_tapefollow_speed = 100; // fyi the motor takes in values from -255 to 255. so dont make this too high!
int base_rescue_speed = 50;
unsigned long start_time = 0;

// MAP
int gate_min_location = 100000;
int gate_max_location = 200000;
int zipline_distance = 10000;
int zipline;

volatile int left_rotations = 0;
volatile int right_rotations = 0;
/*
ISR(INT0_vect) {left_rotations++;}
ISR(INT1_vect) {right_rotations++;}
*/
void enableExternalInterrupt(unsigned int INTX, unsigned int mode) {
  if (INTX > 3 || mode > 3 || mode == 1) return;
  cli();
  /* Allow pin to trigger interrupts        */
  EIMSK |= (1 << INTX);
  /* Clear the interrupt configuration bits */
  EICRA &= ~(1 << (INTX*2+0));
  EICRA &= ~(1 << (INTX*2+1));
  /* Set new interrupt configuration bits   */
  EICRA |= mode << (INTX*2);
  sei();
}

void setup() {	
	portMode(0, INPUT) ;      //   ***** from 253 template file
  portMode(1, INPUT) ;      //   ***** from 253 template file
  
  LCD.begin(16,2) ;
    
  RCServo0.attach(RCServo0Output) ;    // attaching the digital inputs to the RC servo pins on the board.  
  RCServo1.attach(RCServo1Output) ;
  RCServo2.attach(RCServo2Output) ;
  
	Serial.begin(9600);
  //enableExternalInterrupt(INT0, RISING);
  //enableExternalInterrupt(INT1, RISING);
}

void loop() {
  menu();
  start_time = millis();
  tapefollow();
  rescue();
}

