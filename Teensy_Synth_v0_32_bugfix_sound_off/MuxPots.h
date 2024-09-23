// Potentiometers via Multiplexer
// by Hippolyte Mounier
// 2023-12-16
//
// Goal : handles a number of potentiometers,

#include <CD74HC4067.h>  // by Patrick Wasp
#include "iferror.h"

static inline int min(int x, int y) {
  return (x > y) ? y : x;
}
static inline int max(int x, int y) {
  return (x > y) ? x : y;
}

#define POT_UNDEFINED -1
#define FILTER_WEIGHT 0.3
#define VALUE_STABILIZER 4.0  // filters chaotic values


class MuxPotentiometers {
private:
  IntegrityChecker a;

  static const int NB_POTS_MAX = 16;
  int sig_;
  CD74HC4067 mux_;  // the pins are connected to pinout S0, S1, S2, S3

  int potMin_[NB_POTS_MAX];
  int potMid_[NB_POTS_MAX];
  int potMax_[NB_POTS_MAX];
  float calibMin_[NB_POTS_MAX];
  float calibMid_[NB_POTS_MAX];
  float calibMax_[NB_POTS_MAX];

  float precision_[NB_POTS_MAX];
  bool isActive_[NB_POTS_MAX];

  // dynamic values
  int rawPotValues_[NB_POTS_MAX];
  float filteredPotValues_[NB_POTS_MAX];
  float lastConsideredPotValues_[NB_POTS_MAX];

  float currentPotValuesMaped_[NB_POTS_MAX];
  float lastPotValuesMaped_[NB_POTS_MAX];

  IntegrityChecker b;

public:
  MuxPotentiometers(int sig, int s0, int s1, int s2, int s3)
    : mux_(s0, s1, s2, s3), a("MuxPotentiometers"), b("MuxPotentiometers") {
    sig_ = sig;

    for (int i = 0; i < NB_POTS_MAX; i++) {
      isActive_[i] = false;
      precision_[i] = 0.01;
    }
  }


  void definePot(int id, int min, int mid, int max, float minvalue, float midvalue, float maxvalue, float precision = 0.01) {
    IFERROR(id < 0 || id >= NB_POTS_MAX, "defintPot has wrong id")

    isActive_[id] = true;
    potMin_[id] = min;
    potMid_[id] = mid;
    potMax_[id] = max;
    calibMin_[id] = minvalue;
    calibMid_[id] = midvalue;
    calibMax_[id] = maxvalue;
    precision_[id] = precision;
  }


  void readPotentiometers() {
    for (int i = 0; i < NB_POTS_MAX; i++)
      if (isActive_[i]) {
        lastPotValuesMaped_[i] = currentPotValuesMaped_[i];

        mux_.channel(i);  // change mux channel

        int raw = analogRead(sig_);
        rawPotValues_[i] = raw;

        filteredPotValues_[i] = filteredPotValues_[i] * (1.0 - FILTER_WEIGHT) + ((float)raw) * FILTER_WEIGHT;

        if (abs(filteredPotValues_[i] - lastConsideredPotValues_[i]) >= VALUE_STABILIZER) {
          lastConsideredPotValues_[i] = filteredPotValues_[i];
          float maped = mapPotentiometer_(filteredPotValues_[i], potMin_[i], potMid_[i], potMax_[i], calibMin_[i], calibMid_[i], calibMax_[i]);
          if (precision_[i] > 0.01)
            maped = round(maped / precision_[i]) * precision_[i];

          currentPotValuesMaped_[i] = maped;
        }
      }

    a.failIfCorrupt();
    b.failIfCorrupt();
  }


  float getPotValueMaped(int number) {
    if (!isActive_[number])
      return 0.0;

    IFERROR(number >= NB_POTS_MAX || number < 0, "getPotValueMaped has wrong input number")

    return currentPotValuesMaped_[number];
  }


  float hasChanged(int number) {
    if (!isActive_[number])
      return 0;

    IFERROR(number >= NB_POTS_MAX || number < 0, "hasChanged has wrong input number")

    return (currentPotValuesMaped_[number] != lastPotValuesMaped_[number]);
  }



  int getRawPotValue(int number) {
    IFERROR(number >= NB_POTS_MAX || number < 0, "getRawPotValue has wrong input number")

    return rawPotValues_[number];
  }


  void serialPrintAllPotentiometers() {
    readPotentiometers();

    for (int i = 0; i < 16; i++) {
      Serial.print(getRawPotValue(i) / 1023.0);
      Serial.print(" ");
    }
  }

  void serialPrintAllPotentiometersln() {
    serialPrintAllPotentiometers();
    Serial.println();
  }


private:

  float mapPotentiometer_(int potValue, int potMin, int potMid, int potMax, float calibMin, float calibMid, float calibMax) {
    // Ensure potValue is within the valid range
    potValue = min(max(potValue, 0), 1023);

    // Map the potentiometer value to the calibrated range
    float mappedValue;
    if (potValue <= potMid)
      // Map to the lower half
      mappedValue = calibMid - (calibMid - calibMin) * ((potMid - static_cast<float>(potValue)) / (potMid - potMin));
    else
      // Map to the upper half
      mappedValue = calibMid + (calibMax - calibMid) * ((static_cast<float>(potValue) - potMid) / (potMax - potMid));

    if (mappedValue > calibMax) mappedValue = calibMax;
    if (mappedValue < calibMin) mappedValue = calibMin;
    return mappedValue;
  }
};
