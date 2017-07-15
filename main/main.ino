#include <phys253.h>          
#include <LiquidCrystal.h>    

// GLOBAL VARIABLES
int direction = 1; // 1 for left surface, -1 for right. dont worry abt this for now.
int qrd_threshold = 100;
int ir_threshold = 300;
int base_tapefollow_speed = 150; // fyi the motor takes in values from -255 to 255. so dont make this too high!
int base_rescue_speed = 200;
int start_time = 0;

void setup() {	
	#include <phys253setup.txt>
	Serial.begin(9600) ;
}

void loop() {
  //menu();
  //start_time = millis();
	tapefollow();
  //grabAgent();
}

