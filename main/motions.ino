// ROBOT MOVEMENTS
// tinah pin table: https://docs.google.com/document/d/19ENoCmjqfHotwhIWKtm5PPhOPvGOI2TGFGEHJ5CG0m8/edit#heading=h.gjatae8iah5i

void moveLeftWheel(int speed) {
  motor.speed(0, speed);
}

void moveRightWheel(int speed) {
  motor.speed(1, speed);
}

void sharpLeftTurn() {
  moveLeftWheel(-255);
  moveRightWheel(255);
}

void sharpRightTurn() {
  moveLeftWheel(255);
  moveRightWheel(-255);
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
