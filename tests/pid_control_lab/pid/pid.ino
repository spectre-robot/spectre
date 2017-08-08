#include <phys253.h>          
#include <LiquidCrystal.h>     


  ////////////////////////////////////////////////
// TINAH Demo Program - UBC Engineering Physics 253
// (nakane, 2015 May 7) -  Update for IDE 1.6.4   
// (nakane, 2015 Jan 2)  - Updated for use in Arduino IDE (1.0.6)
/////////////////////////////////////////////////

int p = 0, d = 0;
int thresh = 100, prev_error = 0, kp = 10, kd = 10;
int base_speed = 175;
int gain = 1;

void setup()
{  
  #include <phys253setup.txt>
  Serial.begin(9600) ;
}

void loop()
{
  kp = knob(6)/4;
  kd = knob(7)/4;
  LCD.clear();  LCD.home() ;
  LCD.setCursor(0,0); LCD.print("kp: "); LCD.print(kp);
  LCD.setCursor(0,1); LCD.print("kd: "); LCD.print(kd);
  
  int right = analogRead(0);
  int left = analogRead(2);
  //LCD.setCursor(0,0); LCD.print("left: "); LCD.print(left);
  //LCD.setCursor(0,2); LCD.print("right: "); LCD.print(right);
  int error;

  if ((left > thresh) && (right > thresh)) error = 0;
  if ((left > thresh) && (right < thresh)) error = -1; // turn left. right wheel goes faster
  if ((left < thresh) && (right > thresh)) error = 1; // turn right. right wheel slower
  if ((left < thresh) && (right < thresh)) {
     if (prev_error > 0) error = 5;
     if (prev_error <= 0) error = -5;
  }

  p = kp*error;
  d = kd*(error - prev_error);

  int control = gain * (p + d);
  motor.speed(0, base_speed - control);
  motor.speed(2, base_speed + control);
  prev_error = error;
}
