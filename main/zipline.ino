// move back 46 in, turn 10 deg
void zipline() {
  driveStraight(60000, 100);
  stopMotors();
  delay(1000);
  rotate(90);
  delay(1000);
  stopMotors();
  // lift
}
