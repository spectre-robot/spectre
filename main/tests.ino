void test() {
  LCD.clear(); LCD.home() ;
  LCD.setCursor(0, 0); LCD.print("Left Wheel");
  moveLeftWheel(100);
  delay(1000);
  stopMotors();
  LCD.clear(); LCD.home() ;
  LCD.setCursor(0, 0); LCD.print("Right Wheel");
  moveRightWheel(100);
  delay(1000);
  stopMotors();

  LCD.clear(); LCD.home() ;
  LCD.setCursor(0, 0); LCD.print("QRD Test");
}
