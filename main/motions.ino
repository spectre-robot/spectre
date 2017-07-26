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
  /*
  int turn_count;
  //int start_rotations = left_rotations;

  while(true) {
    turn_count = knob(6);
    //LCD.clear(); LCD.home() ;
    //LCD.setCursor(0, 0); LCD.print("count: "); LCD.print(turnSpeed);
    delay(100);
    if(stopbutton()) {
      delay(100);
      if(stopbutton()) {
        delay(100);
        break;
      }
    }
  }

  while(left_rotations - start_rotations < turn_count) {
    moveLeftWheel(-255);
    moveRightWheel(255);
  }

  stopMotors();
  
  moveLeftWheel(-255);
  moveRightWheel(255);

  delay(255);
  stopMotors();
  */
}

void sharpRightTurn() {
  moveLeftWheel(255);
  moveRightWheel(-255);
  delay(255);
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
  return analogRead(4);
}

int readFarRightSensor() {
  return analogRead(5);
}

int read1kSensor() {
  return analogRead(4);
}

int read10kSensor() {
  return analogRead(5);
}
