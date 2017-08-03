unsigned long last_stop = 0;

void grabAgent() {
  RCServo1.write(60); //Hand Servo (Initial Position)
  RCServo0.write(125); //Shoulder Servo
  delay(1000);
  RCServo1.write(5); //Hand Servo
  delay(1000);
  RCServo0.write(0); //Shoulder Servo
  delay(1000);
  RCServo1.write(60); //Hand Servo
  //RCServo0.write(0);
  //RCServo1.write(0);
}

void nextAgent(bool longFollow) {
  int p = 0, d = 0;
  int prev_error = 0, kp = 18, kd = 9;
  if (!longFollow) {kp = 35;}
  int gain = 1;

  // dat logic tho. ok so if we wanna actually find the next agent, then either tapefollow until intersection or if it had just stopped.
  // if we just wanna move forward to align the arm, then move forward for 0.2 seconds.
  while((longFollow && (!isOnIntersection() || (millis() - last_stop) < 200)) || (!longFollow && (millis() - last_stop) < 200)) {
    int left = readLeftSensor();
    int right = readRightSensor();
    int error;

    if ((left > qrd_threshold) && (right > qrd_threshold)) error = 0;
    if ((left > qrd_threshold) && (right < qrd_threshold)) error = -1; // right is off the path. need to turn left. right wheel goes faster
    if ((left < qrd_threshold) && (right > qrd_threshold)) error = 1; // left is off the path. need to turn right. left wheel goes faster
    if ((left < qrd_threshold) && (right < qrd_threshold)) {
      if (prev_error > 0) error = 2;
      if (prev_error <= 0) error = -5;
    }

    p = kp * error;
    d = kd * (error - prev_error);

    int control = gain * (p + d);
    moveLeftWheel(base_rescue_speed + control);
    moveRightWheel(base_rescue_speed - control);
    prev_error = error;
  }
}

void rescue() {
  driveStraight(6000, 100);
  delay(100);
  while(readLeftSensor() < qrd_threshold || readRightSensor() < qrd_threshold) {
    moveLeftWheel(100);
    moveRightWheel(-100);
  }
  stopMotors();
  delay(100);
  
  int agents_rescued = 0;

  // save agents until we've saved them all or the rest already drowned
  while(/*millis() - start_time < 60000 + 5000 * agents_rescued && agents_rescued < 6*/true) {
    LCD.clear(); LCD.home() ;
    LCD.setCursor(0, 0); LCD.print("Move");
    last_stop = millis();
    nextAgent(true);
    stopMotors();
    LCD.clear(); LCD.home() ;
    LCD.setCursor(0, 0); LCD.print("Leap");
    last_stop = millis();
    nextAgent(false);
    stopMotors();
    LCD.clear(); LCD.home() ;
    LCD.setCursor(0, 0); LCD.print("Grab");
    grabAgent();
    agents_rescued++;
  }

  while(agents_rescued % 6 != 3) {
    last_stop = millis();
    nextAgent(true);
    agents_rescued++;
  }
}

