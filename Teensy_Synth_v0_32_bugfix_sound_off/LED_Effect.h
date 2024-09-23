/// @file    DemoReel100.ino
/// @brief   FastLED "100 lines of code" demo reel, showing off some effects
/// @example DemoReel100.ino

#include <FastLED.h>

FASTLED_USING_NAMESPACE

#define DATA_PIN 1
#define LED_TYPE WS2812B
#define COLOR_ORDER GRB
#define NUM_LEDS 7
#define BRIGHTNESS 96
#define FRAMES_PER_SECOND 120
#define LED_DEMO_RESTART_TIME 5000

class LED_Effect {

  CRGB leds[NUM_LEDS];
  uint8_t gCurrentPatternNumber = 0;  // Index number of which pattern is current
  uint8_t gHue = 0;                   // rotating "base color" used by many of the patterns
  long lastUserInteractionTime_ = 0;

  void addGlitter_(fract8 chanceOfGlitter) {
    if (random8() < chanceOfGlitter) {
      leds[random16(NUM_LEDS)] += CRGB::White;
    }
  }

  void rainbow_() {
    // FastLED's built-in rainbow generator
    fill_rainbow(leds, NUM_LEDS, gHue, 7);
  }

  void rainbowWithGlitter_() {
    // built-in FastLED rainbow, plus some random sparkly glitter
    rainbow_();
    addGlitter_(80);
  }

  void confetti_() {
    // random colored speckles that blink in and fade smoothly
    fadeToBlackBy(leds, NUM_LEDS, 10);
    int pos = random16(NUM_LEDS);
    leds[pos] += CHSV(gHue + random8(64), 200, 255);
  }

  void sinelon_() {
    // a colored dot sweeping back and forth, with fading trails
    fadeToBlackBy(leds, NUM_LEDS, 20);
    int pos = beatsin16(13, 0, NUM_LEDS - 1);
    leds[pos] += CHSV(gHue, 255, 192);
  }

  void bpm_() {
    // colored stripes pulsing at a defined Beats-Per-Minute (BPM)
    uint8_t BeatsPerMinute = 62;
    CRGBPalette16 palette = PartyColors_p;
    uint8_t beat = beatsin8(BeatsPerMinute, 64, 255);
    for (int i = 0; i < NUM_LEDS; i++) {  //9948
      leds[i] = ColorFromPalette(palette, gHue + (i * 2), beat - gHue + (i * 10));
    }
  }

  void juggle_() {
    // eight colored dots, weaving in and out of sync with each other
    fadeToBlackBy(leds, NUM_LEDS, 20);
    uint8_t dothue = 0;
    for (int i = 0; i < 8; i++) {
      leds[beatsin16(i + 7, 0, NUM_LEDS - 1)] |= CHSV(dothue, 200, 255);
      dothue += 32;
    }
  }

#define NB_LED_PATTERNS 6
  void applyPattern_() {
    switch (gCurrentPatternNumber) {
      case 0: rainbow_(); break;
      case 1: rainbowWithGlitter_(); break;
      case 2: confetti_(); break;
      case 3: sinelon_(); break;
      case 4: juggle_(); break;
      case 5: bpm_(); break;
    };
  }

  void nextPattern_() {
    // add one to the current pattern number, and wrap around at the end
    gCurrentPatternNumber = (gCurrentPatternNumber + 1) % NB_LED_PATTERNS;
  }

public:
  void init() {
    FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
    FastLED.setBrightness(BRIGHTNESS);
  }

  void ledloop() {
    if (millis() - lastUserInteractionTime_ > LED_DEMO_RESTART_TIME) {
      // Call the current pattern function once, updating the 'leds' array
      applyPattern_();

      // send the 'leds' array out to the actual LED strip
      FastLED.show();
      // insert a delay to keep the framerate modest
      //FastLED.delay(1000/FRAMES_PER_SECOND);

      // do some periodic updates
      EVERY_N_MILLISECONDS(20) {
        gHue++;
      }  // slowly cycle the "base color" through the rainbow
      EVERY_N_SECONDS(10) {
        nextPattern_();
      }  // change patterns periodically

    } else {
      fadeToBlackBy(leds, NUM_LEDS, 20);

      // send the 'leds' array out to the actual LED strip
      FastLED.show();
      // insert a delay to keep the framerate modest
      //FastLED.delay(1000 / FRAMES_PER_SECOND);
    }
  }

  void lightLed(int number, const CRGB& c) {
    leds[number] = c;
  }

  void userIsInteracting() {
    lastUserInteractionTime_ = millis();
  }
};
