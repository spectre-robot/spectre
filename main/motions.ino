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
  int turnSpeed, turnTime;

  while(!startbutton()) {
    turnSpeed = knob(6)/4;
    turnTime = knob(7);
    LCD.clear(); LCD.home() ;
    LCD.setCursor(0, 0); LCD.print("speed: "); LCD.print(turnSpeed);
    LCD.setCursor(0, 1); LCD.print("time: "); LCD.print(turnTime);
  }
  
  for(int i = 0; i < turnTime; i++) {
    moveLeftWheel(-turnSpeed);
    moveRightWheel(turnSpeed);
  }
/*
  do {
    moveLeftWheel(-turnSpeed);
    moveRightWheel(turnSpeed);
  } while(analogRead(0) > qrd_threshold && analogRead(1) > qrd_threshold);
  */
  
  stopMotors();
}

void sharpRightTurn() {
  int turnSpeed, turnTime;

  while(!startbutton()) {
    turnSpeed = knob(6)/4;
    turnTime = knob(7);
    LCD.clear(); LCD.home() ;
    LCD.setCursor(0, 0); LCD.print("speed: "); LCD.print(turnSpeed);
    LCD.setCursor(0, 1); LCD.print("time: "); LCD.print(turnTime);
  }
  
  for(int i = 0; i < turnTime; i++) {
    moveLeftWheel(turnSpeed);
    moveRightWheel(-turnSpeed);
  }

  /*
  do {
    moveLeftWheel(-turnSpeed);
    moveRightWheel(turnSpeed);
  } while(analogRead(0) > qrd_threshold && analogRead(1) > qrd_threshold);
  */
  
  stopMotors();
}

// ROBOT SENSORS

int readLeftSensor() {
  return analogRead(0);
}

int readRightSensor() {
  return analogRead(1);
}

int readFarLeftSensor() {
  return analogRead(2);
}

int readFarRightSensor() {
  return analogRead(3);
}
