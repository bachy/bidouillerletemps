
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
  Serial.println("triggClock");
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

  int frame_hz = 100; // in milliseconds
  unsigned long cur_frame = 0;
  float nextFrameTime = frame_hz;
  float easingLoopDuration = 600; // in frame (meaning 10 frame per second)
  // float easingLoopStartFrame = 0; // in frame (meaning 10 frame per second)
  // float easingLoopEndFrame = easingLoopDuration; // in frame (meaning 10 frame per second)

  Serial.print("nextFrameTime : ");
  Serial.println(nextFrameTime);

  Serial.print("easingLoopDuration : ");
  Serial.println(easingLoopDuration);

  // Serial.print("easingLoopStartFrame : ");
  // Serial.println(easingLoopStartFrame);

  // Serial.print("easingLoopEndFrame : ");
  // Serial.println(easingLoopEndFrame);

  // float nextClockFrame = 1000;
  float nextClockFrame;// = easeInOutQuint(nextFrameTime, easingLoopStartFrame, easingLoopEndFrame, easingLoopDuration);

  Serial.print("nextClockFrame : ");
  Serial.println(nextClockFrame);

  // Pretend to be a regular clock, and tick once a second.
  while (true)
  {
    // Serial.print("nextFrameTime : ");
    // Serial.println(nextFrameTime);

    // Wait until a fps has passed.  Note that this will do ugly things when millis()
    // runs over, so we only have about 9 hours before this version will stop working.
    while (nextFrameTime - millis() > 0) {}

    // reset the loop values at the end of the real time loop
    if( easingLoopDuration - cur_frame <= 0){
      Serial.println("| | | | | | | | | | reset loop values | | | | | | | | | |");

      Serial.print("easingLoopDuration : ");
      Serial.println(easingLoopDuration);

      // easingLoopStartFrame = cur_frame; // starting point of the loop (now)
      // easingLoopEndFrame = cur_frame+easingLoopDuration; // ending point of the loop (now + loop duration)

      // Serial.print("easingLoopStartFrame : ");
      // Serial.println(easingLoopStartFrame);

      // Serial.print("easingLoopEndFrame : ");
      // Serial.println(easingLoopEndFrame);

      cur_frame = 0;
    }

    // trigg clock on altered time
    // generate next altered time value with easing regarding the real time and reali time loop values
    if( nextClockFrame - cur_frame <= 0){
      Serial.println("| | | nextClockFrame over");

      // nextClockFrame += 1000;
      // current time, stat_value, change in value, duration
      nextClockFrame = noEase(cur_frame, 0, 600, easingLoopDuration);
      // nextClockFrame = easeInOutQuint(nextFrameTime - easingLoopStartFrame, easingLoopStartFrame, easingLoopEndFrame, easingLoopDuration);
      nextClockFrame *= 100;

      Serial.print("nextClockFrame : ");
      Serial.println(nextClockFrame);

      triggClock();
    }

    nextFrameTime += frame_hz;
    cur_frame ++;
  }
}

float noEase(float t, float b, float c, float d) {
  return c*t/d + b;
};

float easeInOutQuint(float t, float b, float c, float d) {
  // t: current time
  // b: start value
  // c: change in value
  // d: duration
  // (t and d can be frames ou secondes/milliseconds)

  Serial.println("// // EASE");

  Serial.print("current frame = ");
  Serial.println(t);

  Serial.print("start value = ");
  Serial.println(b);

  Serial.print("change in value = ");
  Serial.println(c);

  Serial.print("duration = ");
  Serial.println(d);

  // Serial.print("t = ");
  // Serial.println(t);

  // t /= d/2;
  t = t/(d/2);

  Serial.print("t = ");
  Serial.println(t);

  float ret;

  if (t < 1){
    ret = c/2*t*t*t*t*t + b;
  }else{
    t -= 2;
    ret = c/2*(t*t*t*t*t + 2) + b;
  }

  return ret;
}



