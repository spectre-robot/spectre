// ROBOT MOVEMENTS
// tinah pin table: https://docs.google.com/document/d/19ENoCmjqfHotwhIWKtm5PPhOPvGOI2TGFGEHJ5CG0m8/edit#heading=h.gjatae8iah5i

void stopMotors() {
  motor.speed(0, 0);
  motor.speed(1, 0);
}

void moveLeftWheel(int speed) {
  motor.speed(0, speed);
}

void moveRightWheel(int speed) {
  motor.speed(1, speed);
}

void sharpLeftTurn() {
  int turnSpeed, turnTime;//254, 254

  while(true) {
    turnSpeed = knob(6)/4;
    turnTime = knob(7);
    LCD.clear(); LCD.home() ;
    LCD.setCursor(0, 0); LCD.print("speed: "); LCD.print(turnSpeed);
    LCD.setCursor(0, 1); LCD.print("time: "); LCD.print(turnTime);
    delay(100);
    if(stopbutton()) {
      delay(100);
      if(stopbutton()) {
        delay(100);
        break;
      }
    }
  }
    moveLeftWheel(-turnSpeed);
    moveRightWheel(turnSpeed);

  //stopMotors();
  delay(turnTime);
  stopMotors();
/*
  do {
    moveLeftWheel(-turnSpeed);
    moveRightWheel(turnSpeed);
  } while(analogRead(0) > qrd_threshold && analogRead(1) > qrd_threshold);
  */
}

void sharpRightTurn() {
  int turnSpeed, turnTime;//254, 254

  while(true) {
    turnSpeed = knob(6)/4;
    turnTime = knob(7);
    LCD.clear(); LCD.home() ;
    LCD.setCursor(0, 0); LCD.print("speed: "); LCD.print(turnSpeed);
    LCD.setCursor(0, 1); LCD.print("time: "); LCD.print(turnTime);
    delay(100);
    if(stopbutton()) {
      delay(100);
      if(stopbutton()) {
        delay(100);
        break;
      }
    }
  }
    moveLeftWheel(turnSpeed);
    moveRightWheel(-turnSpeed);

  //stopMotors();
  delay(turnTime);
  stopMotors();
}

// ROBOT SENSORS

int readLeftSensor() {
  return analogRead(1);
}

int readRightSensor() {
  return analogRead(2);
}

int readFarLeftSensor() {
  return analogRead(2);
}

int readFarRightSensor() {
  return analogRead(3);
}

int read1kSensor() {
  return analogRead(4);
}

int read10kSensor() {
  return analogRead(5);
}
