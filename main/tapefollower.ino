void waitForGo() {
  while(read10kSensor() > ir_threshold) {
    delay(10);
  }
}

// TODO: Stop tape following when robot arrives to holding tank, implement inturrupt for alarmed gate
void tapefollow() {
  int p = 0, d = 0;
  int prev_error = 0, kp = 10, kd = 5;
  int gain = 1;

  while (true) {
    //kp = knob(6) / 8;
    //kd = knob(7) / 8;
    //LCD.clear(); LCD.home() ;
    //LCD.setCursor(0, 0); LCD.print("kp: "); LCD.print(kp);
    //LCD.setCursor(0, 1); LCD.print("kd: "); LCD.print(kd);

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

    LCD.clear(); LCD.home() ;
    LCD.setCursor(0, 0); LCD.print(read10kSensor());

    if((millis() - start_time) < 5000 && (millis() - start_time) > 2000 && read10kSensor() > ir_threshold) {
        stopMotors();
        waitForGo();
    }
    
    int far_right = readFarRightSensor();
    int far_left = readFarLeftSensor();
    if(far_right > qrd_threshold && far_left > qrd_threshold) {
      stopMotors();
      break;
    }
  }
}
