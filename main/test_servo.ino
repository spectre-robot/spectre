
void servoTest() {
  int kp;
  int kd;
  
  while (true) {
    kp = knob(6);
    kd = knob(7);
    LCD.clear(); LCD.home() ;
    LCD.setCursor(0, 0); LCD.print("kp is "); LCD.print(kp);
    LCD.setCursor(0, 1); LCD.print("kd is "); LCD.print(kd);

    RCServo0.write(kp);  
    RCServo1.write(kd);
  }
}

