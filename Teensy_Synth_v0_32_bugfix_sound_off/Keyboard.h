#include "core_pins.h"
#include "iferror.h"

#define MAX_VOICE 4

class KeyboardHandler {
private:
  IntegrityChecker a;

  int voiceNote_[MAX_VOICE];
  int voiceVelocity_[MAX_VOICE];
  long lastVoiceTimeStamp_[MAX_VOICE];

  int nbVoices_;

  IntegrityChecker b;

public:

  KeyboardHandler()
    : a("KeyboardHandler Start"), b("KeyboardHandler End") {
    nbVoices_ = 0;

    long m = millis();
    for (int i = 0; i < MAX_VOICE; i++) {
      voiceNote_[i] = -1;
      lastVoiceTimeStamp_[i] = m;
    }
  }

  /*
  int isVoiceRinging(int voice)
  {
    return (voiceNote_[voice] >= 0);
  }*/


  int getCurrentNoteForVoice(int voice) {
    return voiceNote_[voice];
  }

  /*
  int getCurrentVelocityForVoice(int voice)
  {
    return voiceVelocity_[voice];
  }*/


  int getNbVoices() {
    return nbVoices_;
  }


  int computeVoiceForNewNote(int note, int velocity) {
    a.failIfCorrupt();
    b.failIfCorrupt();
    IFERROR(note < 0 || note > 127, "computeVoiceForNewNote note outside 0-127 range")
    IFERROR(nbVoices_ < 0, "computeVoiceForNewNote nbVoices_ negative")
    IFERROR(nbVoices_ > MAX_VOICE, "computeVoiceForNewNote nbVoices_ too high")

    if (nbVoices_ == MAX_VOICE)  // is the max number of voices reached?
    {                            // note rejection : choose the oldest note to sacrifice
      int voice = getOldestStillRingingVoice();

      // overwrite the playing note in this voice (sacrificed note)
      voiceNote_[voice] = note;
      lastVoiceTimeStamp_[voice] = millis();  // set time stamp this voice was triggered
      voiceVelocity_[voice] = velocity;

      return voice;
    }

    // search for already ringing voice with that note --> if found return that voice
    for (int i = 0; i < MAX_VOICE; i++)
      if (voiceNote_[i] == note) {
        lastVoiceTimeStamp_[i] = millis();  // reset the time this voice was triggered
        return i;
      }

    for (int i = 0; i < MAX_VOICE; i++)
      if (voiceNote_[i] == -1)  // search for empty voice
      {
        voiceNote_[i] = note;
        lastVoiceTimeStamp_[i] = millis();  // set time stamp this voice was triggered
        voiceVelocity_[i] = velocity;

        nbVoices_++;

        return i;  // return the new voice number
      }

    IFERROR(true, "computeVoiceForNewNote could not find suiting voice")
  }


  int computeVoiceForKilledNote(int note) {
    if (nbVoices_ <= 0) return -1;

    if (note < 0 || note > 127) return -1;

    for (int i = 0; i < MAX_VOICE; i++)
      if (voiceNote_[i] == note) {
        voiceNote_[i] = -1;  // empty the voice
        nbVoices_--;
        return i;
      }

    return -1;  //error code
  }


  int getOldestStillRingingVoice() {
    int searchVoice = -1;
    long oldestTimestamp = millis();

    for (int i = 0; i < MAX_VOICE; i++)
      if (voiceNote_[i] >= 0) {
        if (lastVoiceTimeStamp_[i] <= oldestTimestamp)  // warning do not use "<" as all notes may be struck in same millis
        {
          oldestTimestamp = lastVoiceTimeStamp_[i];
          searchVoice = i;
        }
      }

    //IFERROR(searchVoice == -1, "getlastStillRingingVoice found no note")

    return searchVoice;
  }



  int getLastStillRingingVoice() {
    int searchVoice = -1;
    long youngestTimestamp = 0;

    for (int i = 0; i < MAX_VOICE; i++)
      if (voiceNote_[i] >= 0) {
        if (lastVoiceTimeStamp_[i] >= youngestTimestamp) {
          youngestTimestamp = lastVoiceTimeStamp_[i];
          searchVoice = i;
        }
      }

    //IFERROR(searchVoice == -1, "getlastStillRingingVoice found no note")

    return searchVoice;
  }
};