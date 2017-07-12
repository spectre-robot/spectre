void menu() {
  LCD.clear(); LCD.home() ;
  LCD.setCursor(0, 0); LCD.print("start l stop r");
  while(true) {
    if(startbutton()) {
      direction = 1;
      break;
    }
    if(stopbutton()) {
      direction = -1;
      break;
    }
  }
}
