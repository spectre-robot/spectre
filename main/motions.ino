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

void moveLift(int speed) {
  motor.speed(2, speed);
}

void stopLift() {
  motor.speed(2, 0);
}
/*
void driveStraight(unsigned long distance, int speed) {
  left_rotations = 0;
  right_rotations = 0;
  
  while(left_rotations + right_rotations < distance) {
    int left_control = ;
    int right_control = 0;
    moveLeftWheel(speed + left_control);
    moveRightWheel(speed + right_control);
  }
}
*/
// ROBOT SENSORS

int readLeftSensor() {
  return analogRead(4);
}

int readRightSensor() {
  return analogRead(3);
}

int readFarLeftSensor() {
  return analogRead(5);
}

int readFarRightSensor() {
  return analogRead(2);
}

int read1kSensor() {
  return analogRead(0);
}

int read10kSensor() {
  return analogRead(1);
}

bool stopSignal() {
  return (read1kSensor() >= 2 && read10kSensor() >= 2  && 2 * read1kSensor() < read10kSensor());
  //return (read10kSensor() > ir_threshold);
  //return true;
}

bool isOnIntersection() {
  return (readFarLeftSensor() > qrd_threshold || readFarRightSensor() > qrd_threshold);
}

bool foundHoldingTank() {
  return readFarLeftSensor() > qrd_threshold;
}

