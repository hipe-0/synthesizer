// switches using debounce
// by Hippolyte Mounier
// 2023-12-25

#include <ezButton.h>
#define DEBOUNCE_MS 25

class ezButtonManager {
private:
  ezButton* buttonArray_;
  int nbswitches_;


public:
  ezButtonManager(ezButton* switches, int nb) {
    buttonArray_ = switches;
    nbswitches_ = nb;

    for (byte i = 0; i < nbswitches_; i++)
      buttonArray_[i].setDebounceTime(DEBOUNCE_MS);
  }


  void update() {
    for (int i = 0; i < nbswitches_; i++)
      buttonArray_[i].loop();  // MUST call the loop() function first
  }


  bool getState(int number) {
    return buttonArray_[number].getState();
  }


  bool isChanged(int number) {
    return buttonArray_[number].isPressed() || buttonArray_[number].isReleased();
  }
};
