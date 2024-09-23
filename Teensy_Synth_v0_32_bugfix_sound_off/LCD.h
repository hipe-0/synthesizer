// LCD_Display.h
// by Hippolyte Mounier
// 2023-12-15
//
// wrapper class for piloting 16 x 2 "Eone" LCD display using I2C adress 0x3F
// plug the display to the I2C on Teensy 4.1
// pinout:
// "SDA" data signal pin 3 to pin18 on Teensy 4.1
// "SCL" clock signal pin 4 to pin19 on Teensy 4.1

#include <LiquidCrystal_I2C.h>  // ba Frank de Brabander
#include "iferror.h"

const long DISPLAY_DELAY_MS = 100;


class LCD_Display {
private:
  IntegrityChecker a;

  LiquidCrystal_I2C lcd_;
  char msg_[30];
  char msg2_[30];
  long lastDisplayTime_;

  IntegrityChecker b;

public:
  LCD_Display()
    : lcd_(0x3F, 16, 2), a("Start of LCD_Display"), b("End of LCD_Display")  // set the LCD address to 0x3F for a 16 chars and 2 line display
  {
    // warning do not call init in this constructor as it doesn't work. probably the I2C is not ready yet
    lastDisplayTime_ = 0;
  }

  void init() {
    lcd_.init();

    lcd_.backlight();

    setCursor(3, 0);
    print("LCD Test");
  }

  void print(const char* txt) {
    lcd_.print(txt);
  }
  void print(int val) {
    lcd_.print(val);
  }
  void print(float val) {
    lcd_.print(val);
  }
  void setCursor(int x, int y) {
    lcd_.setCursor(x, y);
  }
  void clear() {
    lcd_.clear();
  }

  void loadTxt(const char* txt, float val) {
    strcpy(msg_, txt);
    sprintf(msg2_, "%.2f", val);

    a.failIfCorrupt();
    b.failIfCorrupt();
  }

  void loadTxt(const char* txt) {
    strcpy(msg_, txt);
    strcpy(msg2_, "");

    a.failIfCorrupt();
    b.failIfCorrupt();
  }

  void displayLoaded() {
    if (millis() - lastDisplayTime_ > DISPLAY_DELAY_MS)
      if (strlen(msg_) > 0) {
        clear();
        print(msg_);
        setCursor(2, 1);
        print(msg2_);

        lastDisplayTime_ = millis();
        strcpy(msg_, "");  // clear message
      }
    a.failIfCorrupt();
    b.failIfCorrupt();
  }
};