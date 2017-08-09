void grabAgent() {
  RCServo1.write(40); //Hand Servo (Initial Position)
  delay(500);
  RCServo0.write(135); //Shoulder Servo
  delay(500);
  RCServo1.write(5); //Hand Servo
  delay(1000);
  RCServo0.write(0); //Shoulder Servo
  delay(1000);
  RCServo1.write(60); //Hand Servo
}

void leap() {
  int p = 0, d = 0;
  int prev_error = 0, kp = 10, kd = 2;
  int gain = 1;

  // tapefollow until intersection or if it had just stopped.
  while((millis() - last_stop) < 120) {
    int left = readLeftSensor();
    int right = readRightSensor();
    int error;

    if ((left > qrd_threshold) && (right > qrd_threshold)) error = 0;
    if ((left > qrd_threshold) && (right < qrd_threshold)) error = -1; // right is off the path. need to turn left. right wheel goes faster
    if ((left < qrd_threshold) && (right > qrd_threshold)) error = 1; // left is off the path. need to turn right. left wheel goes faster
    if ((left < qrd_threshold) && (right < qrd_threshold)) {
      if (prev_error > 0) error = 2;
      if (prev_error <= 0) error = -2;
    }

    p = kp * error;
    d = kd * (error - prev_error);

    int control = gain * (p + d);
    moveLeftWheel(45 + control);
    moveRightWheel(45 - control);
    prev_error = error;
  }
  stopMotors();
  if (readRightSensor() < qrd_threshold && readLeftSensor() > qrd_threshold) {
    unsigned long start_spin = millis();
    while ((millis() - start_spin) < 600 && readRightSensor() < qrd_threshold && readLeftSensor() > qrd_threshold) {
      moveRightWheel(75);
      moveLeftWheel(-75);
    }
  } else {
    unsigned long start_spin = millis();
    while ((millis() - start_spin) < 750 && readLeftSensor() < qrd_threshold || readRightSensor() < qrd_threshold) {
      moveRightWheel(-75);
      moveLeftWheel(75);
    }
  }

  stopMotors();
}

void nextAgent() {
  int p = 0, d = 0;
  int prev_error = 0, kp = 18, kd = 9;
  int gain = 1;

  while(!isOnIntersection() || (millis() - last_stop) < 200) {
    int left = readLeftSensor();
    int right = readRightSensor();
    int error;

    if ((left > qrd_threshold) && (right > qrd_threshold)) error = 0;
    if ((left > qrd_threshold) && (right < qrd_threshold)) error = -1; // right is off the path. need to turn left. right wheel goes faster
    if ((left < qrd_threshold) && (right > qrd_threshold)) error = 1; // left is off the path. need to turn right. left wheel goes faster
    if ((left < qrd_threshold) && (right < qrd_threshold)) {
      if (prev_error >= 0) error = 5;
      if (prev_error < 0) error = -2;
    }

    p = kp * error;
    d = kd * (error - prev_error);

    int control = gain * (p + d);
    moveLeftWheel(base_rescue_speed + control);
    moveRightWheel(base_rescue_speed - control);
    prev_error = error;
  }
  stopMotors();
}

void rescue() {
  if (surface == 0) {
    driveStraight(6000, 100);
    delay(100);
    while(readRightSensor() < qrd_threshold) {
      moveRightWheel(100);
      moveLeftWheel(-100);
    }
    stopMotors();
    delay(100);
  } else {
    driveStraight(6000, 100);
    while(readRightSensor() < qrd_threshold) {
      moveRightWheel(100);
      moveLeftWheel(-100);
    }
    stopMotors();
    delay(100);
  }
  
  int agents_rescued = 0;

  // save agents until we've saved them all or the rest already drowned
  while(/*millis() - start_time < 60000 + 5000 * agents_rescued && */agents_rescued < 6) {
    LCD.clear(); LCD.home() ;
    LCD.setCursor(0, 0); LCD.print("Move");
    last_stop = millis();
    nextAgent();
    LCD.clear(); LCD.home() ;
    LCD.setCursor(0, 0); LCD.print("Leap");
    LCD.setCursor(0, 1); LCD.print(readFarLeftSensor()); LCD.print(" "); LCD.print(readFarRightSensor());
    last_stop = millis();
    leap();
    LCD.clear(); LCD.home() ;
    LCD.setCursor(0, 0); LCD.print("Grab");
    grabAgent();
    agents_rescued++;
  }

  if (surface == 0) {
    while(agents_rescued % 7 != 4) {
      last_stop = millis();
      if (agents_rescued == 7) {
        driveStraight(6000, 100);
      }
      nextAgent();
      agents_rescued++;
    }
    rotate(180, -1);
  } else {
    while(agents_rescued % 7 != 3) {
      last_stop = millis();
      if (agents_rescued == 7) {
        driveStraight(6000, 100);
      }
      nextAgent();
      agents_rescued++;
    }
    leap();
  }
  stopMotors();
  RCServo0.write(135);
}

