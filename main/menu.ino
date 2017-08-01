void menu() {
  LCD.clear(); LCD.home() ;
  LCD.setCursor(0, 0); LCD.print("start l stop r");
  while(true) {
    //gate_min_location = knob(6) * 1000;
    //LCD.clear(); LCD.home();
    //LCD.setCursor(0, 1);LCD.print(gate_min_location);
    
    //base_rescue_speed = knob(6)/4;
    //LCD.clear(); LCD.home() ;
    //LCD.setCursor(0, 0); LCD.print("start l stop r");
   // LCD.setCursor(0, 1); LCD.print("speed: "); LCD.print(base_rescue_speed);
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

