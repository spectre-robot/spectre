#include <phys253.h>
#include <LiquidCrystal.h>


  ////////////////////////////////////////////////
// TINAH Demo Program - UBC Engineering Physics 253
// (nakane, 2015 May 7) -  Update for IDE 1.6.4
// (nakane, 2015 Jan 2)  - Updated for use in Arduino IDE (1.0.6)
/////////////////////////////////////////////////

int p = 0, i = 0, d = 0;
int thresh = 600, prev_error = 0, kp = 10, ki = 10, kd = 10;
int max_i = 0, min_i = 0;
int base_speed = 200;

void setup()
{
  #include <phys253setup.txt>
  Serial.begin(9600) ;
}

void loop()
{
  // Read in value from the qrd1114 sensors
  int left = analogRead(0);
  int right = analogRead(1);
  int error;

  // Truth table for steering
  if ((left > thresh) && (right > thresh)) error = 0;
  if ((left > thresh) && (right < thresh)) error = -1;
  if ((left < thresh) && (right > thresh)) error = 1;
  if ((left < thresh) && (right < thresh)) {
     if (prev_error > 0) error = 5;
     if (prev_error <= 0) error = -5;
  }

  // Gains
  p = kp*error; // proportional
  d = kd*(error - prev_error); // derivative
  i = ki*error + i; // integral
  if (i > max_i) {
    i = max_i;
  }
  if (i < min_i) {
    i = min_i;
  }

  int control = p + i + d;
  LCD.clear();  LCD.home() ;
  LCD.setCursor(0,0); LCD.print("TRIAL 5");
  motor.speed(0, base_speed + control);
  motor.speed(2, base_speed - control);
  prev_error = error;
}
