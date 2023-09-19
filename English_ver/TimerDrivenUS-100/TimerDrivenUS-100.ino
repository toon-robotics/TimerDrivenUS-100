#include "US100.h"

///Assuming Arduino Leonardo

///Required to use timer
#define USE_TIMER_3 true

#include "TimerInterrupt_Generic.h"
#include "ISR_Timer_Generic.h"

ISR_Timer ISR_timer;///ISR Timer

static const unsigned long HARDWARE_TIMER_INTERVAL_MS = 5UL;

///US-100
US100* us100;

///Callback function for hardware timer to use ISR timer.
void timerHandler(){
  ISR_timer.run();
}

void setup() {

  Serial.begin(9600);///Start of serial communication for display on the serial monitor

  us100 = new US100(20,4500);///Create US-100. Arguments are minimum and maximum distance (default values will be set if not specified).
  us100->setup();///Set up the US-100

  ITimer3.init();///Initialize hardware timer

  // Set hardware timer for ISR timer execution (see TimerInterrupt_Generic sample code).
  if (ITimer3.attachInterruptInterval(HARDWARE_TIMER_INTERVAL_MS, timerHandler))
  {
    Serial.print(F("Starting ITimer3, millis() = ")); 
    Serial.println(millis());
  }
  else{
    Serial.println(F("Can't set ITimer3. Select another frequency or a timer."));
  }

  ///Set ISR timer execution interval and a callback function.
  ISR_timer.setInterval(US100::TIMER_INTERVAL_MS, US100::ISR_timerHandler, us100);

}


void loop() {

  int dist = us100->getDistance();
        
  Serial.print("Distance: ");
  Serial.print(dist);
  Serial.println("mm");

  delay(100);

}