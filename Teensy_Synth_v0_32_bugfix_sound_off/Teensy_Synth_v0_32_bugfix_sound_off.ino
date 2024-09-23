// Hippo usb host synth test with multiple voices
#define WELCOME "Synth 0.32 by Hippo"
#define AUDIO_MEMORY 100
//#define NODEBUG

#include "iferror.h"

#include "LED_Effect.h"
LED_Effect myLEDs;

IntegrityChecker a("Start of audioLibrary");
#include "AudioImport.h"
IntegrityChecker b("End of audioLibrary");

#include "Constants.h"

IntegrityChecker c("start of USBhost");
#include "USBHost_t36.h"
USBHost usbHost;
MIDIDevice midiUSBHost(usbHost);
IntegrityChecker d("start of MidiIn");

#include "MidiIN.h"
MidiIn midiUSBIn;
IntegrityChecker e("End of MidiIn");

/// Hardware :
#include "BuiltInLed.h"

#include "Keyboard.h"
KeyboardHandler keys;

#include "Voices.h"
VoiceManager voices;

#include "Pots.h"
Potentiometers pots;

#include "MuxPots.h"
MuxPotentiometers mux1(38, 37, 36, 35, 34);  // the pins are connected to pinout SIG, S0, S1, S2, S3
MuxPotentiometers mux2(39, 37, 36, 35, 34);  // the pins are connected to pinout SIG, S0, S1, S2, S3

#include "LCD.h"
LCD_Display lcd;

#include "ezButtons.h"

ezButton ezSwitches[BUTTON_NUM] = {
  ezButton(32),
  ezButton(31),
  ezButton(30),
  ezButton(29),
  ezButton(0),
  ezButton(2),
  ezButton(3),
};

ezButtonManager switches(ezSwitches, BUTTON_NUM);

#include "Params.h"
#include "NoteHandler.h"

IntegrityChecker z("End of program memory");

void setup() {
  led.turnOn();
  Serial.begin(115200);

  // Audio library init
  AudioMemory(AUDIO_MEMORY);
  sgtl5000_1.enable();
  sgtl5000_1.volume(0.3);
  ampLeft.gain(1.0);
  ampRight.gain(1.0);

  // Synth parameters init
  noise1.amplitude(1.0);
  voices.init();
  CutoffFrequency.amplitude(1.0);
  FilterContour.amplitude(0.0);
  ladder1.octaveControl(5.0);
  ladder2.octaveControl(5.0);
  ladder3.octaveControl(5.0);
  ladder4.octaveControl(5.0);
  voice1.gain(3, 0.0);
  voice2.gain(3, 0.0);
  voice3.gain(3, 0.0);
  voice4.gain(3, 0.0);
  feedback.gain(0.0);  // please no feedback to avoid harsh noise at start of synth

  delay1.delay(0, 0);        // no delay
  effectmixer.gain(1, 0.0);  // no gain of delay
  effectmixer.gain(0, 1.0);  // gain of signal
  PitchMod.gain(0.0);        // set to zero to avoid huge noise
  CutoffMod.gain(0.0);       // set to zero to avoid huge noise


  // pots initialisation
  pots.definePot(POT_VOLUME_FEEDBACK, A10, 5, 511, 1018, 0.0, 0.5, 1.0);
  pots.definePot(POT_VOLUME1, A12, 5, 511, 1018, 0.0, 0.5, 1.0);
  pots.definePot(POT_VOLUME2, A13, 5, 511, 1018, 0.0, 0.5, 1.0);
  pots.definePot(POT_VOLUME3, A17, 5, 511, 1018, 0.0, 0.5, 1.0);
  pots.definePot(POT_VOLUME_NOISE, A16, 5, 511, 1018, 0.0, 0.5, 1.0);

  mux1.definePot(MUX_ATTACK, 5, 497, 1018, 0.0, 1000.0, 5000.0);
  mux1.definePot(MUX_DECAY, 5, 427, 1018, 0.0, 1000.0, 5000.0);
  mux1.definePot(MUX_SUSTAIN, 5, 405, 1018, 0.0, 0.5, 1.0);
  mux1.definePot(MUX_FILTER_ATTACK, 5, 470, 1018, 0.0, 1000.0, 5000.0);
  mux1.definePot(MUX_FILTER_DECAY, 5, 438, 1018, 0.0, 1000.0, 5000.0);
  mux1.definePot(MUX_FILTER_SUSTAIN, 5, 456, 1018, 0.0, 0.5, 1.0);
  mux1.definePot(MUX_CUTOFF_FREQUENCY, 5, 388, 1018, -0.5, 0.25, 1.0);
  mux1.definePot(MUX_RESONANCE, 5, 500, 1018, 0.0, 1.0, 2.0);
  mux1.definePot(MUX_CONTOUR, 5, 456, 1018, -1.0, 0.0, 1.0);
  mux1.definePot(MUX_MASTER_VOLUME, 5, 402, 1018, 0.0, 1.0, 2.0);
  mux2.definePot(MUX2_TUNE2, 5, 409, 1018, -5.0, 0.0, 5.0, 0.05);
  mux2.definePot(MUX2_TUNE3, 5, 394, 1018, -5.0, 0.0, 5.0, 0.05);
  mux2.definePot(MUX2_OCTAVE, 5, 557, 1018, 0.0, 5.0, 11.0, 1.0);
  mux2.definePot(MUX2_WAVEFORM1, 5, 555, 1018, 0.0, 6.0, 11.0, 0.3);
  mux2.definePot(MUX2_WAVEFORM2, 5, 651, 1018, 0.0, 6.0, 11.0, 0.3);
  mux2.definePot(MUX2_WAVEFORM3, 5, 614, 1018, 0.0, 6.0, 11.0, 0.3);
  mux2.definePot(MUX2_GLIDETIME, 5, 541, 1018, 0.0, 0.5, 2.0);
  mux2.definePot(MUX2_MIX, 5, 478, 1018, 0.0, 0.5, 1.0);
  mux2.definePot(MUX2_PULSE_WIDTH, 5, 456, 1018, -1.0, 0.0, 1.0);

  //const int FUZZ_LENGTH = 9;
  //float fuzz[FUZZ_LENGTH]= { -1.0, -0.6, -0.4, -0.2, 0.0, 0.2, 0.4, 0.6, 1.0 };
  const float wave_shape_chebyshev_3rd[257] = {
    -1.0, -0.9375, -0.8671875, -0.796875, -0.734375, -0.671875, -0.609375, -0.546875, -0.484375, -0.4296875, -0.375, -0.3203125,
    -0.265625, -0.2109375, -0.15625, -0.109375, -0.0546875, -0.0078125, 0.0390625, 0.078125, 0.125, 0.1640625, 0.2109375, 0.25,
    0.2890625, 0.328125, 0.359375, 0.3984375, 0.4296875, 0.46875, 0.5, 0.53125, 0.5546875, 0.5859375, 0.6171875, 0.640625, 0.6640625,
    0.6953125, 0.71875, 0.734375, 0.7578125, 0.78125, 0.796875, 0.8203125, 0.8359375, 0.8515625, 0.8671875, 0.8828125, 0.890625,
    0.90625, 0.921875, 0.9296875, 0.9375, 0.953125, 0.9609375, 0.96875, 0.96875, 0.9765625, 0.984375, 0.984375, 0.9921875, 0.9921875,
    0.9921875, 0.9921875, 0.9921875, 0.9921875, 0.9921875, 0.9921875, 0.9921875, 0.984375, 0.984375, 0.9765625, 0.9765625, 0.96875,
    0.9609375, 0.953125, 0.9453125, 0.9375, 0.9296875, 0.921875, 0.90625, 0.8984375, 0.890625, 0.875, 0.8671875, 0.8515625, 0.8359375,
    0.828125, 0.8125, 0.796875, 0.78125, 0.765625, 0.75, 0.734375, 0.71875, 0.703125, 0.6796875, 0.6640625, 0.6484375, 0.6328125, 0.609375,
    0.59375, 0.5703125, 0.5546875, 0.53125, 0.515625, 0.4921875, 0.46875, 0.453125, 0.4296875, 0.40625, 0.3828125, 0.359375, 0.34375, 0.3203125,
    0.296875, 0.2734375, 0.25, 0.2265625, 0.203125, 0.1796875, 0.15625, 0.1328125, 0.109375, 0.0859375, 0.0625, 0.0390625, 0.015625, 0,
    -0.0234375, -0.046875, -0.0703125, -0.09375, -0.1171875, -0.140625, -0.1640625, -0.1875, -0.2109375, -0.234375, -0.2578125, -0.28125,
    -0.3046875, -0.328125, -0.3515625, -0.3671875, -0.390625, -0.4140625, -0.4375, -0.4609375, -0.4765625, -0.5, -0.5234375, -0.5390625,
    -0.5625, -0.578125, -0.6015625, -0.6171875, -0.640625, -0.65625, -0.671875, -0.6875, -0.7109375, -0.7265625, -0.7421875, -0.7578125,
    -0.7734375, -0.7890625, -0.8046875, -0.8203125, -0.8359375, -0.84375, -0.859375, -0.875, -0.8828125, -0.8984375, -0.90625, -0.9140625,
    -0.9296875, -0.9375, -0.9453125, -0.953125, -0.9609375, -0.96875, -0.9765625, -0.984375, -0.984375, -0.9921875, -0.9921875, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -0.9921875, -0.9921875, -0.984375, -0.9765625, -0.9765625, -0.96875, -0.9609375, -0.9453125, -0.9375, -0.9296875, -0.9140625,
    -0.8984375, -0.890625, -0.875, -0.859375, -0.84375, -0.828125, -0.8046875, -0.7890625, -0.765625, -0.7421875, -0.7265625, -0.703125,
    -0.671875, -0.6484375, -0.625, -0.59375, -0.5625, -0.5390625, -0.5078125, -0.4765625, -0.4375, -0.40625, -0.3671875, -0.3359375, -0.296875,
    -0.2578125, -0.21875, -0.171875, -0.1328125, -0.0859375, -0.046875, 0, 0.046875, 0.1015625, 0.1484375, 0.203125, 0.2578125, 0.3125, 0.3671875,
    0.421875, 0.4765625, 0.5390625, 0.6015625, 0.6640625, 0.7265625, 0.7890625, 0.859375, 0.9296875, 0.9996875
  };
  waveshape1.shape(wave_shape_chebyshev_3rd, 257);
  FeedBackMixer.gain(0, 0.5);
  FeedBackMixer.gain(1, 0.5);

  // midi initialisation
  midiUSBHost.setHandleNoteOn(NoteOnHandler);
  midiUSBHost.setHandleNoteOff(NoteOffHandler);
  midiUSBHost.setHandleControlChange(ControlChangeHandler);
  midiUSBHost.setHandlePitchChange(PitchChangeHandler);

  midiUSBIn.setHandleNoteOn(NoteOnHandler);
  midiUSBIn.setHandleNoteOff(NoteOffHandler);
  midiUSBIn.setHandleKillAllNotes(killAllNotes);

  usbHost.begin();

  // interface initialisation
  lcd.init();
  lcd.clear();
  lcd.print(WELCOME);

  myLEDs.init();

  Serial.println("INFO: Synth Setup complete");
  Serial.println(WELCOME);

  playWelcomeNotes();
}


#define DEFAULT_DELAY 0.2
#define DEFAULT_DELAY_MIX 0.2
#include "Menu.h"
LCDMenu myMenu(DEFAULT_DELAY, DEFAULT_DELAY_MIX);

#define MAX_USB_EVENTS_AT_ONCE 10

void loop() {
  midiUSBIn.read();  // handlers will be called if data is available

  for (int i = 0; (i < MAX_USB_EVENTS_AT_ONCE) && midiUSBHost.read(); i++) {
    if (i==9)
      DEBUGTXT("warning MAX_USB_EVENTS_AT_ONCE exceeded")
  };  // handlers will be called if data is available

  synth.manageParameters();

  manageLed();

  myMenu.loop();
  delay1.delay(0, myMenu.getTimeValue() * 1000.0);
  effectmixer.gain(1, myMenu.getMixValue());  // gain of Delay

  voices.repitchAllWav();
  //voices.printSerialLn();

  voices.driveLFO();

  // just verifying that all objects are valid
  a.failIfCorrupt();
  b.failIfCorrupt();
  c.failIfCorrupt();
  d.failIfCorrupt();
  e.failIfCorrupt();
  z.failIfCorrupt();
}



void manageLed() {
  myLEDs.ledloop();

  if (rms.available()) {
    float value = rms.read() * 255.0;
    bool isLFO = switches.getState(SWITCH_LFO) == 1;
    //DEBUGVAL("rms", value)

    if (value > 0) {

      float volume1 = pots.getPotValueMaped(POT_VOLUME1);
      float volume2 = pots.getPotValueMaped(POT_VOLUME2);
      float volume3 = pots.getPotValueMaped(POT_VOLUME3);
      float volumefb = pots.getPotValueMaped(POT_VOLUME_FEEDBACK);
      float volumeNoise = pots.getPotValueMaped(POT_VOLUME_NOISE);

      int wave1 = mux2.getPotValueMaped(MUX2_WAVEFORM1);
      int wave2 = mux2.getPotValueMaped(MUX2_WAVEFORM2);
      int wave3 = mux2.getPotValueMaped(MUX2_WAVEFORM3);

      myLEDs.lightLed(1, CHSV(0, 200, value * volumefb));
      myLEDs.lightLed(2, CHSV(30 + wave1 * 30, 255, value * volume1));
      myLEDs.lightLed(3, CHSV(30 + wave2 * 30, 255, value * volume2));
      if (!isLFO)
        myLEDs.lightLed(4, CHSV(30 + wave3 * 30, 255, value * volume3));
      myLEDs.lightLed(5, CHSV(0, 0, value * volumeNoise));

      float masterVolume = mux1.getPotValueMaped(MUX_MASTER_VOLUME);
      int hot = value * masterVolume;
      if (hot > 130)
        myLEDs.lightLed(6, CHSV(0, 255, hot));  //red
      else if (hot > 100)
        myLEDs.lightLed(6, CHSV(45, 255, (hot * 255) / 130));  // yellow
      else
        myLEDs.lightLed(6, CHSV(95, 255, (hot * 255) / 100));  // green

      myLEDs.userIsInteracting();
    }

    if (isLFO) {
      if (peakLFO.available()) {
        float lfoValue = peakLFO.read();
        //float volume3  = pots.getPotValueMaped(POT_VOLUME3);
        float modWheel = synth.getModWheel();

        //DEBUGVAL("peakLFO", lfoValue)

        myLEDs.lightLed(4, CHSV(0.0, modWheel * 255, lfoValue * 255.0));
      }
    }
  }
}
