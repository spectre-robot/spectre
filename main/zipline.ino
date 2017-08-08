// move back 46 in, turn 10 deg
void zipline() {
  // when the robot hits the zipline, it will do a wheelie because of torque from the normal force from the zipline
  while (!wheelie()) {
    moveLeftWheel(50);
    moveRightWheel(50);
  }

  undoWheelie();

  // align the robot to be perpendicular to the zipline.
  while (!wheelie) {
    moveLeftWheel(50);
  }

  undoWheelie();

  while (!wheelie) {
    moveRightWheel(50);
  }

  undoWheelie();

  rotate(90, -1);
}
