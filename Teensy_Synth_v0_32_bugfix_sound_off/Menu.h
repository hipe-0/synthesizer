const int NB_MENU_ITEMS = 4;

const char* MENU_TEXTS[NB_MENU_ITEMS] = { "0 Back", "1 Delay mix", "2 Delay time", "3 AudioMem used" };

#include "Encoder.h"
Encoder encoder;
#define ENCODER_CLOCK_PIN1 11
#define ENCODER_CLOCK_PIN2 10
#define ENCODER_DATA_PIN 12
void ISR_encoderRise() {
  encoder.rise();
}
void ISR_encoderFall() {
  encoder.fall();
}

#include <ezButton.h>
#define DEBOUNCE_MS 25
#define SWITCH_PINOUT 28

class LCDMenu {
private:
  ezButton switch_;

  float mix_;
  float time_;

  bool isEditing_;
  int lastEncoderValue;
  int selection_;


public:
  LCDMenu(float time, float mix)
    : switch_(ezButton(SWITCH_PINOUT)) {
    time_ = time;
    mix_ = mix;
    isEditing_ = false;
    encoder.setup(ENCODER_CLOCK_PIN1, ENCODER_CLOCK_PIN2, ENCODER_DATA_PIN, ISR_encoderRise, ISR_encoderFall);
    switch_.setDebounceTime(DEBOUNCE_MS);
  }


  void loop() {
    switch_.loop();

    if (switch_.isPressed()) {
      if (!isEditing_) {
        switch (selection_) {
          case 1: lcd.loadTxt("Delay Mix", mix_); break;
          case 2: lcd.loadTxt("Delay Time", time_); break;
        };

        isEditing_ = true;
      } else {
        lcd.loadTxt(MENU_TEXTS[selection_]);
        isEditing_ = false;
      }

      lcd.displayLoaded();
    }

    int rot = encoder.getValue();
    if (rot != lastEncoderValue)  // has rotated
    {
      int delta = rot - lastEncoderValue;

      if (!isEditing_) {
        selection_ += delta;
        if (selection_ >= NB_MENU_ITEMS) selection_ = NB_MENU_ITEMS - 1;
        if (selection_ < 0) selection_ = 0;


        DEBUGVAL("selection_", selection_)
        if (selection_ == 3)
          lcd.loadTxt(MENU_TEXTS[selection_], AudioMemoryUsageMax());
        else
          lcd.loadTxt(MENU_TEXTS[selection_]);

        lcd.displayLoaded();
      } else {
        switch (selection_) {
          case 1:
            mix_ += delta * 0.1;
            if (mix_ < 0) mix_ = 0;
            lcd.loadTxt("Delay Mix", mix_);
            break;
          case 2:
            time_ += delta * 0.1;
            if (time_ < 0) time_ = 0;
            lcd.loadTxt("Delay Time", time_);
            break;
        };
        lcd.displayLoaded();
      }
    }
    lastEncoderValue = rot;
  }



  float getMixValue() {
    //DEBUGVAL("mix_",mix_)
    return mix_;
  }


  float getTimeValue() {
    //DEBUGVAL("time_",time_)
    return time_;
  }

};