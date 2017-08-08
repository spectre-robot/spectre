#include <phys253.h>          
#include <LiquidCrystal.h>     


  ////////////////////////////////////////////////
// TINAH Demo Program - UBC Engineering Physics 253
// (nakane, 2015 May 7) -  Update for IDE 1.6.4   
// (nakane, 2015 Jan 2)  - Updated for use in Arduino IDE (1.0.6)
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
    variable = map(knob(6), 0, 1023, 0, 180) ; // Arduino function that maps 0 - 1023 to 0 - 180 and returns the mapped value of knob(6).
    RCServo0.write(variable); // Sets the angle of the motor to variable.
    LCD.clear();  LCD.home() ;
    LCD.setCursor(0,0); LCD.print("Servos " ); LCD.print(variable) ;
    LCD.setCursor(0,1); LCD.print("knobs + <start>");
    delay(10) ;
  }

    

  LCD.clear();  LCD.home() ;
  while ( !(stopbutton()) ) ;

}

