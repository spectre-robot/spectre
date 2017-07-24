#include <Arduino.h>
#include "motor.h"



motorClass::motorClass()
{
	for (int i = 0 ; i < 4; i++) {
		pinMode(Motor_Direction[i], OUTPUT);
		pinMode(Motor_EnableDigital[i], OUTPUT);

		digitalWrite(Motor_Direction[i], HIGH);
	  	analogWrite(Motor_EnableDigital[i], 1);  //make the motor glitch, force it to be zero.
	  	analogWrite(Motor_Enable[i], 0);

      }
}


void motorClass::stop(int motorVal)
{
	analogWrite(Motor_EnableDigital[motorVal], 0);
//    digitalWrite(Motor_EnableDigital[motorVal], LOW) ;

}


void motorClass::stop_all()
{
	for (int i = 0 ; i < 4; i++) {
		analogWrite(Motor_EnableDigital[i],0);
//        digitalWrite(Motor_EnableDigital[i], LOW) ;
	}
}


void motorClass::speed(int motorVal, int speedvalue)
{
	if (speedvalue > 255)
	{
       speedvalue = 255 ;	
	}
	if (speedvalue < -255)
	{
	   speedvalue = -255 ;
	}
	
	
	if (speedvalue >= 0)
	{
		digitalWrite(Motor_Direction[motorVal], HIGH);
		analogWrite(Motor_EnableDigital[motorVal], abs(speedvalue));
//	    digitalWrite(Motor_EnableDigital[motorVal], HIGH) ;
	}

	if(speedvalue < 0)
	{
		digitalWrite(Motor_Direction[motorVal], LOW);
		analogWrite(Motor_EnableDigital[motorVal], abs(speedvalue));
//        digitalWrite(Motor_EnableDigital[motorVal], HIGH) ;

	}
}


