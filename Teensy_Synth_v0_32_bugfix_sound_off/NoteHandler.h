#include "iferror.h"

#define VELOCITY_BOOST 0.5  // added contour

void NoteOnHandler(uint8_t channel, uint8_t pitch, uint8_t velo) {
  bool isMono = switches.getState(SWITCH_POLYPHONY) == 1;
  bool isVelocityBoost = switches.getState(SWITCH_VELOCITY) == 0;

  int initialNbVoices = keys.getNbVoices();
  DEBUGVAL("initialNbVoices", initialNbVoices)
  if (isMono)
    if (initialNbVoices >= 1) {
      int voiceToKill = keys.getLastStillRingingVoice();
      int pitch = keys.getCurrentNoteForVoice(voiceToKill);
    }

  if (isVelocityBoost)
    synth.setAddedContour(((float)velo) * VELOCITY_BOOST / 127.0);

  int voice = keys.computeVoiceForNewNote(pitch, velo);  // performs a voice stealing algorithm if the max voice is reached
  if (isMono) {
    if (initialNbVoices == 0)
      voices.soundVoice(0, pitch, velo, true, false);  // trigger with no glide
    else
      voices.soundVoice(0, pitch, velo, false, true);  // legato effect only if previous voice existed, no trigger and glide
  } else
    voices.soundVoice(voice, pitch, velo, true, false);  // no glide in polyphony, always trigger in polyphony


  lcd.clear();
  lcd.print("Note: ");

  int notevalue = ((int)pitch) % 12;
  const char* notesTxt[] = { "C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B" };
  const char* notesTxt2[] = { "do", "do#", "re", "re#", "mi", "fa", "fa#", "sol", "sol#", "la", "la#", "si" };
  lcd.print(notesTxt[notevalue]);
  lcd.print(" ");
  lcd.print(notesTxt2[notevalue]);

  myLEDs.lightLed(0, CHSV(95, 255, 255));  //green
  myLEDs.userIsInteracting();

  DEBUGVAL2("Note On, pitch", pitch, " voice", voice)

  led.turnOn();
}


void NoteOffHandler(uint8_t channel, uint8_t pitch, uint8_t velo) {
  DEBUGVAL("NoteOffHandler pitch", pitch)

  int nbkeys = keys.getNbVoices();
  int voiceKilled = keys.computeVoiceForKilledNote(pitch);

  bool isMono = switches.getState(SWITCH_POLYPHONY) == 1;

  if (voiceKilled >= 0) {
    if (isMono) {
      if (nbkeys == 1)
        voices.killVoice(0, false);
    } else
      voices.killVoice(voiceKilled, false);
  }

  if (nbkeys == 1) {
    led.turnOff();
    lcd.clear();
  } else if (isMono) {
    int voiceToRevive = keys.getLastStillRingingVoice();
    int pitchToRevive = keys.getCurrentNoteForVoice(voiceToRevive);
    voices.soundVoice(0, pitchToRevive, velo, false, true);
  }

  DEBUGVAL("computeVoiceForKilledNote", voiceKilled);
}


void ControlChangeHandler(uint8_t channel, uint8_t status, uint8_t value) {
  //DEBUGVAL3("ControlChangeHandler A", channel, "B", status, "C", value)

  if (status == 1)  // mod wheel 0 - 127
    synth.setModWheel((float)value / 127.0);

  if (status == 2)  // breath controler 0 - 127
    synth.setBreathControlervolume((float)value / 127.0);
}


void PitchChangeHandler(uint8_t channel, int value) {
  //DEBUGVAL2("PitchChange channel", channel, "value", value)

  if (value != 0) {
    float valuef = ((float)value) / (8192.0 / 2.0);
    voices.setGlobalTune(valuef);
  }
}


void killAllNotes() {
  voices.killAllVoices();
}


void playWelcomeNotes() {
  Serial.println("Emitting Notes");

  NoteOnHandler(0, 48, 50);
  delay(60);
  NoteOffHandler(0, 48, 50);

  NoteOnHandler(0, 52, 60);
  delay(60);
  NoteOffHandler(0, 52, 100);

  NoteOnHandler(0, 55, 70);
  delay(60);
  NoteOffHandler(0, 55, 100);

  NoteOnHandler(0, 60, 80);
  delay(60);
  NoteOffHandler(0, 60, 100);
}
