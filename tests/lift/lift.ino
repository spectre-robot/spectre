#include <phys253.h>          
#include <LiquidCrystal.h>     


  ////////////////////////////////////////////////
// Lift Motor Testing Code
// (esther, 2015 May 7)  
/////////////////////////////////////////////////

void setup()
{  
  #include <phys253setup.txt>
  Serial.begin(9600) ;
  
}




void loop()
{
  
   int variable = LOW ;                // setting up a few temporary variables 
   int value, value2, i, pinNumber ;
   int portCounter = 0 ;
   int motorSpeed = 0 ;
  
/////////////////////////////////////////////////
// DC MOTOR TEST
/////////////////////////////////////////////////

while ( !(stopbutton()) ) {
  motorSpeed = knob(6) - 512 ; // THe knob ranges from 0 - 1023, so by doing this our motor speed will range from -512 - 511
  LCD.clear();  LCD.home() ;
  LCD.setCursor(0,0); LCD.print("DC Motor: ");  LCD.print(motorSpeed) ;
  LCD.setCursor(0,1); LCD.print("<stop>");
  motor.speed(0, motorSpeed) ;
  if (stopbutton()) {break;} ;
  delay(10) ; 
}
motor.stop_all() ;

/////////////////////////////////////////////////
// SERVO MOTOR TEST
/////////////////////////////////////////////////

  while ( !(startbutton()) ) {
    LCD.clear();  LCD.home() ;
    LCD.setCursor(0,0); LCD.print("DC Motor: " ); LCD.print(motorSpeed) ;
    LCD.setCursor(0,1); LCD.print("Paused - <start>");
    delay(10) ;
  }

  LCD.clear();  LCD.home() ;

}

