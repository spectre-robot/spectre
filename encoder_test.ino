// Setting up the counter
int reading = 0;
int lowest = -12;
int highest = 12;
int changeamnt = 1;

// Timing for polling the encoder
unsigned long currentTime;
unsigned long lastTime;


// Pin definitions
const int pinA = 12;
const int pinB = 11;

// Storing the readings

boolean encA;
boolean encB;
boolean lastA = false;

void setup() {
  // set the two pins as inputs with internal pullups
  pinMode(pinA, INPUT_PULLUP);
  pinMode(pinB, INPUT_PULLUP);
  // Set up the timing of the polling
  currentTime = millis();
  lastTime = currentTime; 
  // Start the serial monitor for debugging
  Serial.begin(9600);
} 


void loop()
{
  // Read elapsed time
  currentTime = millis();
  
  // Check if it's time to read (wait 100 ms)
  if(currentTime >= (lastTime + 100))
  {
    // read the two pins
    encA = digitalRead(pinA);
    encB = digitalRead(pinB);

    // Printing out the encoder values A and B
    Serial.print(encA);
    Serial.print(",");
    Serial.println(encB);
    
    
    // check if A has gone from high to low
    if ((!encA) && (lastA))
    {
      // check if B is high 
      if (encB)
      {
        // clockwise
        if (reading + changeamnt <= highest)
        {
          reading = reading + changeamnt; 
        }
      }
      else
      {
        // anti-clockwise
        if (reading - changeamnt >= lowest)
        {
          reading = reading - changeamnt; 
        }
      }
      // Output reading for debugging
      //Serial.println(reading);
    }
    // store reading of A and millis for next loop
    lastA = encA;
    lastTime = currentTime;

  }

}
