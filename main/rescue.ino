unsigned long last_stop = 0;

void grabAgent() {

  RCServo1.write(45); //Hand Servo (Initial Position)
  RCServo0.write(125); //Shoulder Servo
  delay(1000);
  RCServo1.write(5); //Hand Servo
  delay(1000);
  RCServo0.write(0); //Shoulder Servo
  delay(1000);
  RCServo1.write(45); //Hand Servo
  
  //RCServo0.write(0);
  //RCServo1.write(0);
}

void nextAgent() {
  int p = 0, d = 0;
  int prev_error = 0, kp = 12, kd = 9;
  int gain = 1;
  
  while(!isOnIntersection() || millis() - last_stop < 500) {
    //kp = knob(6)/4;
    //kd = knob(7)/4;
    //LCD.clear(); LCD.home() ;
    //LCD.setCursor(0, 0); LCD.print("kp: "); LCD.print(kp);
    //LCD.setCursor(0, 1); LCD.print("kd: "); LCD.print(kd);
    
    int left = readLeftSensor();
    int right = readRightSensor();
    int error;

    if ((left > qrd_threshold) && (right > qrd_threshold)) error = 0;
    if ((left > qrd_threshold) && (right < qrd_threshold)) error = -1; // right is off the path. need to turn left. right wheel goes faster
    if ((left < qrd_threshold) && (right > qrd_threshold)) error = 2; // left is off the path. need to turn right. left wheel goes faster
    if ((left < qrd_threshold) && (right < qrd_threshold)) {
     // if (prev_error >= 0) error = 2;
      //if (prev_error < 0) error = -2;
      error = 5;
    }

    p = kp * error;
    d = kd * (error - prev_error);

    int control = gain * (p + d);
    moveLeftWheel(base_tapefollow_speed + control);
    moveRightWheel(base_tapefollow_speed - control);
    prev_error = error;
  }
}

void rescue() {
  int agents_rescued = 0;

  // save agents until we've saved them all or the rest already drowned
  while(/*millis() - start_time < 60000 + 5000 * agents_rescued && agents_rescued < 6*/true) {
    last_stop = millis();
    nextAgent();
    stopMotors();
    grabAgent();
    agents_rescued++;
  }

  while(agents_rescued % 6 != 3) {
    nextAgent();
    agents_rescued++;
  }
}

