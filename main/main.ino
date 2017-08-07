#include <avr/interrupt.h>       
#include "lib/phys253.h"
#include <LiquidCrystal.h>

// GLOBAL VARIABLES
int surface = 0; // 0 for clockwise surface, 1 for counter-clockwise
bool seen_gate = false; // sorry
int qrd_threshold = 100;
int ir_threshold = 75;
int base_tapefollow_speed = 125; // fyi the motor takes in values from -255 to 255. so dont make this too high!
int base_rescue_speed = 100;
unsigned long start_time = 0;

// MAP
unsigned long gate_location[2] = {150000, 150000};
unsigned long zipline_distance[2] = {20000, 20000};

unsigned long last_stop = 0;

volatile unsigned long left_rotations = 0;
volatile unsigned long right_rotations = 0;

ISR(INT0_vect) {left_rotations++;}
ISR(INT2_vect) {right_rotations++;}

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
  enableExternalInterrupt(INT0, RISING);
  enableExternalInterrupt(INT2, RISING);
}

void loop() {
  RCServo1.write(60);
  menu();
  left_rotations = 0;
  right_rotations = 0;
  seen_gate = false;
  start_time = millis();
  tapefollow();
  delay(1000);
  rescue();
  //grabAgent();
  zipline();
  stopMotors();
}


