void test() {
  // Wheel Test
  while(!(stopbutton())) {
    int left_speed = knob(6)/4;
    int right_speed = knob(7)/4;
    LCD.clear(); LCD.home() ;
    LCD.setCursor(0, 0); LCD.print("Left Wheel: "); LCD.print(left_speed);
    LCD.setCursor(0, 1); LCD.print("Right Wheel: "); LCD.print(right_speed);
    moveLeftWheel(left_speed) ;
    moveRightWheel(right_speed) ;
  }

  // Sensor Test
  while(!(stopbutton())) {
    LCD.clear(); LCD.home() ;
    LCD.setCursor(0, 0); LCD.print(readLeftSensor()); LCD.print(" "); LCD.print(readRightSensor()); LCD.print(" "); LCD.print(read1kSensor());
    LCD.setCursor(0, 1); LCD.print(readFarLeftSensor()); LCD.print(" "); LCD.print(readFarRightSensor()); LCD.print(" "); LCD.print(read10kSensor());
  }

  // Arm Test
 /* while(!(stopbutton()) {
    LCD.clear(); LCD.home() ;
    int shoulder_angle = map(knob(6), 0, 1023, 0, 180) ;
    int claw_angle = map(knob(7), 0, 1023, 0, 180) ;
    LCD.setCursor(0, 0); LCD.print("Shoulder Angle: "); LCD.print(shoulder_angle);
    LCD.setCursor(0, 1); LCD.print("Claw Angle: "); LCD.print(claw_angle);
  }*/
}

