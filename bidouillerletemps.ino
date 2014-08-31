// 2014-08-30
// arthackdays
// Bachir Soussi Chiadmi
// Julien Gargot


////// Board Setup /////////////////////////////////////////////////////////////////////////
extern float timer0_overflow_count;

int clockA = 2;          // Set these to the pin numbers you have attached the clock wires
int clockB = 3;          // to.  Order is not important.

int tickPin = clockA;    // This keeps track of which clock pin should be fired next.


// Initialize the IO ports
void setup()
{
  pinMode(clockA, OUTPUT);
  pinMode(clockB, OUTPUT);

  digitalWrite(clockA, LOW);
  digitalWrite(clockB, LOW);

  Serial.begin(9600);
}

// Move the second hand forward one position (one second on the clock face).
void triggClock() {
  // Serial.println("triggClock");
  // Energize the electromagnet in the correct direction.
  digitalWrite(tickPin, LOW);
  delay(10);
  digitalWrite(tickPin, HIGH);

  // Switch the direction so it will fire in the opposite way next time.
  if (tickPin == clockA)
  {
    tickPin = clockB;
  } else {
    tickPin = clockA;
  }
}


// Main loop
void loop()
{
  /*
  float startTime = millis();
  float temp;

  // Pretend to be a regular clock, and tick once a second.
  while (true)
  {
    startTime += 1000;
    Serial.println(startTime);
    // Wait until a second has passed.  Note that this will do ugly things when millis()
    // runs over, so we only have about 9 hours before this version will stop working.
    while (startTime - millis() > 0) {}

    doTick();
  }
  */

  int frame_hz = 100; // in milliseconds -> 100 = 10fps
  unsigned long cur_frame = 0;
  float nextFrameTime = frame_hz;
  float easingLoopDuration = 12000; // in frame
  float alpha;
  // int farfrommiddle = 0;

  // float nextClockFrame = 1000;
  float nextClockFrame = 10;// = easeInOutQuint(nextFrameTime, easingLoopStartFrame, easingLoopEndFrame, easingLoopDuration);

  // Serial.print("nextClockFrame : ");
  // Serial.println(nextClockFrame);

  // Pretend to be a regular clock, and tick once a second.
  while (true)
  {
    // Wait until a fps has passed.  Note that this will do ugly things when millis()
    // runs over, so we only have about 9 hours before this version will stop working.
    while (nextFrameTime - millis() > 0) {}

    // reset the loop values at the end of the real time loop
    if( easingLoopDuration - cur_frame <= 0){
      // Serial.println("| | | | | | | | | | reset loop values | | | | | | | | | |");

      cur_frame = 0;
      nextClockFrame = 10;
    }

    // trigg clock on altered time
    // generate next altered time value with easing regarding the real time and reali time loop values
    if( nextClockFrame - cur_frame <= 0){
      alpha = cur_frame / (easingLoopDuration/2);

      if(cur_frame <= easingLoopDuration/2){
        alpha += 0.5;
      }else{
        alpha = 2.5 - alpha;
      }

      // Serial.print("alpha = ");
      // Serial.println(alpha);

      nextClockFrame += 10*alpha;

      triggClock();
    }

    nextFrameTime += frame_hz;
    cur_frame ++;
  }
}
