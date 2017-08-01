void goToZipline() {
  while(true) {
    while(!(stopbutton())) {
      int lol = knob(6);
      zipline_distance = 1000*lol;
      LCD.clear(); LCD.home() ;
      LCD.setCursor(0, 0); LCD.print("dist: "); LCD.print(lol);
    }
    LCD.clear(); LCD.home() ;
    LCD.setCursor(0, 0); LCD.print("covfefe");
    left_rotations = 0;
    right_rotations = 0;
  
    while(left_rotations + right_rotations < zipline_distance) {
      moveLeftWheel(100);
      moveRightWheel(100);
    }
    stopMotors();
  }
}

void liftBasket() {
  moveLift(50);
  delay(2000);
  stopLift();
}

void lowerBasket() {
  moveLift(-50);
  delay(2000);
  stopLift();
}

void zipline() {
  //liftBasket();
  goToZipline();
  //lowerBasket();
  //moveLeftWheel(-20);
  //moveRightWheel(-20);
  //delay(1000);
  //stopMotors();
}
