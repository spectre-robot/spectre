void waitForGo() {
  while(stopSignal()) {
    delay(10);
  }
}

void tapefollow() {
  int p = 0, d = 0;
  int prev_error = 0, kp = 11, kd = 3;
  int gain = 1;

  while (true) {
    LCD.clear(); LCD.home() ;
    LCD.setCursor(0, 0); LCD.print(read1kSensor()); LCD.print(" "); LCD.print(read10kSensor());
    int left = readLeftSensor();
    int right = readRightSensor();
    int error;

    if ((left > qrd_threshold) && (right > qrd_threshold)) error = 0;
    if ((left > qrd_threshold) && (right < qrd_threshold)) error = -1; // right is off the path. need to turn left. right wheel goes faster
    if ((left < qrd_threshold) && (right > qrd_threshold)) error = 1; // left is off the path. need to turn right. left wheel goes faster
    if ((left < qrd_threshold) && (right < qrd_threshold)) {
      if (prev_error > 0) error = 5;
      if (prev_error < 0) error = -5;
      if (prev_error = 0) error = 0;
    }

    p = kp * error;
    d = kd * (error - prev_error);

    int control = gain * (p + d);
    moveLeftWheel(base_tapefollow_speed + control);
    moveRightWheel(base_tapefollow_speed - control);
    prev_error = error;

    unsigned long distance = left_rotations + right_rotations;
    
   if (!seen_gate && distance > gate_location[surface]) {
        stopMotors();
        seen_gate = true;
        delay(1000);
        if (stopSignal()) {
          waitForGo();
        }
    }
    

    /*if (!seen_gate && distance > 50000 && distance <= gate_location[surface]) {
      delay(1000);
      LCD.setCursor(0, 1); LCD.print("BAKA");
      if (stopSignal()) {
        stopMotors();
        waitForGo();
        seen_gate = true;
      }
    }*/
    /*
    if (foundHoldingTank()) {
      stopMotors();
      break;
    }
   */ 
  }
}

