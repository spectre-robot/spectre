unsigned long last_stop = 0;

void grabAgent() {
  /*while (true) {
    RCServo0.write(knob(6)/8); //Shoulder Servo
    RCServo1.write(knob(7)/8); //Hand Servo
  }*/
  delay(3000);
}

void nextAgent() {
  int p = 0, d = 0;
  int prev_error = 0, kp = 10, kd = 5;
  int gain = 1;
  int far_left = 1000, far_right = 1000, left = 0, right = 0;
  int tape_count;
  
  do {
    left = readLeftSensor();
    right = readRightSensor();
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
    
    moveLeftWheel(base_rescue_speed + control);
    moveRightWheel(base_rescue_speed - control);
    
    far_left = readFarLeftSensor();
    far_right = readFarRightSensor();
    left = readLeftSensor();
    right = readRightSensor();

    tape_count = 0;
    if(far_left > qrd_threshold) tape_count++;
    if(far_right > qrd_threshold) tape_count++;
    if(left > qrd_threshold) tape_count++;
    if(right > qrd_threshold) tape_count++;
  } while (tape_count < 3 || millis() - last_stop < 500);
}

void rescue() {
  //sharpLeftTurn();
  int agents_rescued = 0;
  
  while(millis() - start_time < 60000 + 5000 * agents_rescued && agents_rescued < 6) {
    last_stop = millis();
    nextAgent();
    stopMotors();
    //sharpRightTurn();
    grabAgent();
    //sharpLeftTurn();
    agents_rescued++;
  }

  while(agents_rescued % 6 != 3) {
    nextAgent();
    agents_rescued++;
  }
}
