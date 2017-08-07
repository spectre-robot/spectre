// ROBOT SENSORS

int readFarLeftSensor() {
  return analogRead(0);
}

int readLeftSensor() {
  return analogRead(1);
}

int readRightSensor() {
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

bool stopSignal() {
  return (read1kSensor() >= 4 && read10kSensor() >= 4  && 2 * read1kSensor() < read10kSensor());
}

bool isOnIntersection() {
  return (readFarLeftSensor() > qrd_threshold || readFarRightSensor() > qrd_threshold);
}

bool foundHoldingTank() {
  if (surface == 0) {
    return readFarRightSensor() > qrd_threshold && ((left_rotations + right_rotations) > 3 * gate_location[surface]);
  } else {
    return readFarLeftSensor() > qrd_threshold && ((left_rotations + right_rotations) > 3 * gate_location[surface]);
  }
}


// ROBOT MOVEMENTS
// tinah pin table: https://docs.google.com/document/d/19ENoCmjqfHotwhIWKtm5PPhOPvGOI2TGFGEHJ5CG0m8/edit#heading=h.gjatae8iah5i

void stopMotors() {
  motor.speed(0, 0);
  motor.speed(1, 0);
}

void moveLeftWheel(int speed) {
  motor.speed(1, speed);
}

void moveRightWheel(int speed) {
  motor.speed(0, speed);
}

void moveLift(int speed) {
  motor.speed(2, speed);
}

void stopLift() {
  motor.speed(2, 0);
}

// Drive perfectly straight using encoders. 
// 7.5% accuracy. 50000 = 20 inches
void driveStraight(unsigned long distance, int speed) {
  left_rotations = 0;
  right_rotations = 0;
  int prev_control = 0;

  while(left_rotations + right_rotations < distance) {
    LCD.clear(); LCD.home() ;
    LCD.setCursor(0, 0); LCD.print(left_rotations);
    LCD.setCursor(0, 1); LCD.print(right_rotations);
    int control = 0;
    if (left_rotations > right_rotations + 20) {
      control = 45;
    } else if (left_rotations < right_rotations - 20) {
      control = -45; 
    }
    if (control * prev_control > 0) {
      control = control + prev_control;
    }
    moveLeftWheel(speed - control);
    moveRightWheel(speed + control);
    if (control > 0) {
      prev_control = 45;
    } else if (control < 0) {
      prev_control = -45;
    } else {
      prev_control = 0;
    }
  }

  stopMotors();
}

// Same as above but backwards. Control values are different because the wheels are mounted in the back so its more sensitive.
// 20% accuracy. Lets try not to use it...
void driveBackwards(unsigned long distance, int speed) {
  left_rotations = 0;
  right_rotations = 0;
  int prev_control = 0;

  while(left_rotations + right_rotations < distance) {
    int control = 0;
    if (left_rotations > right_rotations + 20) {
      control = 45;
    } else if (left_rotations < right_rotations - 20) {
      control = -45; 
    }
    if (control * prev_control > 0) {
      control = control + prev_control;
    }
    moveLeftWheel(speed + control);
    moveRightWheel(speed - control);
    if (control > 0) {
      prev_control = 45;
    } else if (control < 0) {
      prev_control = -45;
    } else {
      prev_control = 0;
    }
  }
  
  stopMotors();
}

int rotate(int angle) {
  left_rotations = 0;
  right_rotations = 0;

  while (left_rotations + right_rotations < angle * 40) {
    moveLeftWheel(100);
    moveRightWheel(-100);
  }
  
  stopMotors();
}

int realign() {
  left_rotations = 0;
  right_rotations = 0;

  if (readFarLeftSensor() < qrd_threshold && readFarRightSensor() < qrd_threshold) {
    driveBackwards(1000, -100);
    realign();
  } else if (readFarLeftSensor() < qrd_threshold || readFarRightSensor() < qrd_threshold) {
    while ((readFarLeftSensor() < qrd_threshold || readFarRightSensor() < qrd_threshold) && left_rotations + right_rotations < 3000) {
      moveLeftWheel(100);
      moveRightWheel(-100);
    }
    left_rotations = 0;
    right_rotations = 0;
    while ((readFarLeftSensor() < qrd_threshold || readFarRightSensor() < qrd_threshold) && left_rotations + right_rotations < 3000) {
      moveLeftWheel(-100);
      moveRightWheel(100);
    }
  }
}
