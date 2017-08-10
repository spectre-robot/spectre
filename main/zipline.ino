void findZipline() {
  // when the robot hits the zipline, it will do a wheelie because of torque from the normal force from the zipline
  while (!wheelie()) {
    moveLeftWheel(60);
    moveRightWheel(60);
  }
  stopMotors();
  delay(100);

  undoWheelie();

  stopMotors();
  delay(100);
  
  LCD.clear(); LCD.home() ;
  LCD.setCursor(0, 0); LCD.print("left");
  // align the robot to be perpendicular to the zipline.
  while (!wheelie) {
    moveLeftWheel(50);
  }
  
  stopMotors();
  delay(100);
  
  undoWheelie();

  stopMotors();
  delay(100);

  LCD.clear(); LCD.home() ;
  LCD.setCursor(0, 0); LCD.print("right");
  
  while (!wheelie) {
    moveRightWheel(50);
  }

  stopMotors();
  delay(100);

  undoWheelie();

  stopMotors(); 
  delay(100);

  rotate(90, -1);
}

void makeMyDreamsComeTrue() {
  motor.speed(2, 255);
}

void zipline() {
  findZipline();
  LCD.clear(); LCD.home() ;
  LCD.setCursor(0, 0); LCD.print("IM FLYING");
  makeMyDreamsComeTrue();
  while(!stopbutton()) {
    delay(10);
  }
  LCD.clear(); LCD.home() ;
  LCD.setCursor(0, 0); LCD.print("SAFE!!!!!");
  motor.speed(2, 0);
  while(!startbutton()) {
    delay(10);
  }
  LCD.clear(); LCD.home() ;
  LCD.setCursor(0, 0); LCD.print("unwind");
  motor.speed(2, -255);
}
