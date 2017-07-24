#ifndef phys253_h
#define phys253_h


// include all of the h-file headers used in general Phys 253 programs
// added by Jon Nakane, 2009 March 23
// edit 2010 May 3 - removed WConstants.h from here and motor.h for Wiring-0026.

#include <Arduino.h>
#include "phys253pins.h"
#include <LiquidCrystal.h>
#include "motor.h"
#include "phys253pins.h"
//#include <Tone.cpp>
#include "ServoTINAH.h"



/* Displays an error when TINAH is not selected as the board */
// #if !defined(__AVR_ATmega128__) 
// 	#error Oops!  Make sure you have 'TINAH Board - UBC Engineering Physics 253' selected from the 'Tools -> Boards' menu.
// #endif;


//setup the variables and classes used throughout phys 253.

LiquidCrystal LCD(26,27,28,16, 17, 18, 19,20,21,22,23);


motorClass motor ;

ServoTINAH RCServo0;    // declare variables for up to eight servos.   Replaced old Servo253 implementation 2015Jan2
ServoTINAH RCServo1; 
ServoTINAH RCServo2;


int knob(int value) ;	//	{ return analogRead(knobInput[value]) ;}
void buzzer	(int value) ;//{ return pulseOut(buzzerOutput, value*2) ;}
void buzzerOff () 	    ;//{ return pulseStop(buzzerOutput ) ;}
int startbutton() 	;	//{ return !digitalRead(startInput) ;}
int stopbutton() 	;	//{ return !digitalRead(stopInput) ;}
void portMode(int portval, int value) ;
void portWrite(int portval, int value) ;
int portRead(int portval) ;



/*
#ifdef __cplusplus            // added 2009 May 18th - required to disable analogWrite on PWM lines.
extern "C" {
#endif
void timer1PWMAOff(void);
void timer1PWMBOff(void);
void timer1PWMCOff(void);
void timer3PWMAOff(void);
void timer3PWMBOff(void);
void timer3PWMCOff(void);
#ifdef __cplusplus
}
#endif


void analogWriteReset(int PWMPin)   // added 2009 May 18th - required to disable analogWrite on PWM lines
{
    switch(PWMPin) {
		 case 5:
		 case 29:
		    timer1PWMAOff();
		    break ;
		 case 4:
		 case 30:
		    timer1PWMBOff();
		    break ;
		 case 3:
		 case 31:
		    timer1PWMCOff();
		    break ;
		 case 2:
		 case 35:
		    timer3PWMAOff();
		    break ;
		 case 1:
		 case 36:
		    timer3PWMBOff();
		    break ;
		 case 0:
		 case 37:
		    timer3PWMCOff();
		    break ;
	}
}

*/



#endif
