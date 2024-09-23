/* Class definition for a rotary encoder controlled by 2 pins CLK and DT 
by Hippolyte Mounier


*/

#include "iferror.h"

#define DEBOUNCE_TIME 1

void ISR_encoderRise();
void ISR_encoderFall();

class Encoder {
private:
  volatile int counter_ = 0;
  volatile unsigned long last_time_;  // for debouncing
  volatile bool lastWasFall_;
  int prev_counter_;
  int dataPin_;
  int clockPin1_;
  int clockPin2_;

public:

  void setup(int clockpin1, int clockpin2, int datapin, void(risehandler)(), void(fallhandler)()) {
    dataPin_ = datapin;
    clockPin1_ = clockpin1;
    clockPin2_ = clockpin2;

    // configure encoder pins
    pinMode(clockPin1_, INPUT);
    pinMode(clockPin2_, INPUT);
    pinMode(dataPin_, INPUT);

    // use interrupt for CLK pin is enough
    // call ISR_encoderChange() when CLK pin changes from LOW to HIGH
    attachInterrupt(digitalPinToInterrupt(clockPin1_), risehandler, RISING);
    attachInterrupt(digitalPinToInterrupt(clockPin2_), fallhandler, FALLING);
  }


  void rise() {
    int delta = millis() - last_time_;
    if (delta < DEBOUNCE_TIME) {
      //DEBUGTXT("bypassed rise")
      return;
    }
    last_time_ = millis();

    if (!lastWasFall_) return;

    bool b = digitalRead(dataPin_) == HIGH;
    if (b) counter_--;
    else counter_++;

    //DEBUGVAL2("rise dt", digitalRead(dataPin_), "delta", delta)

    lastWasFall_ = false;
  }


  void fall() {
    int delta = millis() - last_time_;
    if (delta < DEBOUNCE_TIME) {
      //DEBUGTXT("bypassed fall")
      return;
    }
    last_time_ = millis();

    if (lastWasFall_) return;

    bool b = digitalRead(dataPin_) == HIGH;
    if (b) counter_++;
    else counter_--;

    //DEBUGVAL2("    fall dt", digitalRead(dataPin_), "delta", delta)

    lastWasFall_ = true;
  }


  int getValue() {
    return counter_;
  }
};
