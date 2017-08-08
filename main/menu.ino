void menu() {
  LCD.clear(); LCD.home() ;
  LCD.setCursor(0, 0); LCD.print("START for CW");
  LCD.setCursor(0, 1); LCD.print("STOP for CCW");
  while(true) {
    if(startbutton()) {
      surface = 0;
      break;
    }
    if(stopbutton()) {
      surface = 1;
      break;
    }
  }
}

