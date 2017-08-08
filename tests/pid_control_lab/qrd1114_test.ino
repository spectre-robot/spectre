/*
 * PID control
 * Lab 6
 */

#include <phys253.h>
#include <LiquidCrystal.h>

void setup()
{
    #include <phys253setup.txt>
    Serial.begin(9600);
}

void loop()
{

/*
 * Check Sensors Test
 */

// Set up LCD screen: 16 positions on LCD screen:   1234567890123456
  LCD.clear();  LCD.home() ;
  LCD.setCursor(0,0); LCD.print("Analog Inputs");
  LCD.setCursor(0,1); LCD.print("Press <start>");
  while ( !(startbutton()) ) ;

/* This loop outputs the values from the 8 analog inputs onto a single screen.
Note that the values are divided by 16.  This was done so that each 10-bit input (normally 2^10 = 1024) would only reach a maximum of 1024/16 = 64,
so that all 8 values could be written to the screen at the same time.
Also note that Analog inputs 7 and 6 are usually tied to the two knobs on the board.  The jumpers, both next to the knobs, can be moved in order to
maximize the # of analog inputs to 8, but normally leave the knobs as the analog inputs, if possible.
*/
  int A0 = 0;
  int A1 = 1;

  while( ! (startbutton()  ) )
  {
    A0 = analogRead(0);
    A1 = analogRead(1);
    LCD.clear();
    LCD.setCursor(0,0);
    LCD.print(A0) ;  LCD.print(" ") ;
    LCD.print(A1) ;  LCD.print(" ") ;
    Serial.println(A0, A1);
    delay(100) ;
  }


}
