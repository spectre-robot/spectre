// move back 46 in, turn 10 deg
void zipline() {
  driveStraight(60000, 100);
  moveLeftWheel(50);
  moveRightWheel(50);
  delay(2000);
  stopMotors();
  delay(500);
  rotate(90);
  stopMotors();
}
