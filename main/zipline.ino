void goToZipline() {
  driveStraight(100000 ,100);
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

// move back 46 in, turn 10 deg
void zipline() {
  //liftBasket();
  goToZipline();
  //lowerBasket();
  //moveLeftWheel(-20);
  //moveRightWheel(-20);
  //delay(1000);
  //stopMotors();
}
