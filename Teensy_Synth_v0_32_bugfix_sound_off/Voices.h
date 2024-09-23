#include "synth_waveform.h"
// VoiceManager.h
// by Hippolyte Mounier
// 2023-12-15
#include "iferror.h"

#define MAX_VOICES 4
#define WAV_PER_VOICE 3
#define LFO_VOICE 3
#define LFO_WAV 2

class VoiceManager {
  IntegrityChecker a;

  AudioSynthWaveformModulated* waveform1_[MAX_VOICES];
  AudioSynthWaveformModulated* waveform2_[MAX_VOICES];
  AudioSynthWaveformModulated* waveform3_[MAX_VOICES];
  AudioSynthWaveformModulated* waveform4_[MAX_VOICES];
  AudioEffectEnvelope* envelopes_[MAX_VOICES];
  AudioEffectEnvelope* filterEnvelopes_[MAX_VOICES];
  AudioAmplifier* noiseAmplifiers_[MAX_VOICES];
  int octavesPerWav_[WAV_PER_VOICE];
  float tunePerWav_[WAV_PER_VOICE];
  float tune_;
  int targetVoicePitch_[MAX_VOICES];
  float currentglidePitch_[MAX_VOICES];
  float glideTime_;
  long lastUpdateTime_;
  bool isLFO_;
  float freqLFO_;

  IntegrityChecker b;

public:
  VoiceManager()
    : a("VoiceManager start"), b("VoiceManager end") {}

  void init() {
    waveform1_[0] = &waveform1_voice1;
    waveform1_[1] = &waveform1_voice2;
    waveform1_[2] = &waveform1_voice3;
    waveform1_[3] = &waveform1_voice4;

    waveform2_[0] = &waveform2_voice1;
    waveform2_[1] = &waveform2_voice2;
    waveform2_[2] = &waveform2_voice3;
    waveform2_[3] = &waveform2_voice4;

    waveform3_[0] = &waveform3_voice1;
    waveform3_[1] = &waveform3_voice2;
    waveform3_[2] = &waveform3_voice3;
    waveform3_[3] = &waveform3_voice4;

    noiseAmplifiers_[0] = &noiseamp1;
    noiseAmplifiers_[1] = &noiseamp2;
    noiseAmplifiers_[2] = &noiseamp3;
    noiseAmplifiers_[3] = &noiseamp4;

    envelopes_[0] = &envelope1;
    envelopes_[1] = &envelope2;
    envelopes_[2] = &envelope3;
    envelopes_[3] = &envelope4;

    filterEnvelopes_[0] = &FilterEnvelope1;
    filterEnvelopes_[1] = &FilterEnvelope2;
    filterEnvelopes_[2] = &FilterEnvelope3;
    filterEnvelopes_[3] = &FilterEnvelope4;

    for (int i = 0; i < MAX_VOICES; i++) {
      envelopes_[i]->delay(0);
      envelopes_[i]->attack(10);
      envelopes_[i]->decay(50);
      envelopes_[i]->sustain(0.1);
      envelopes_[i]->release(300);

      filterEnvelopes_[i]->delay(0);
      filterEnvelopes_[i]->attack(10);
      filterEnvelopes_[i]->decay(50);
      filterEnvelopes_[i]->sustain(1.0);
      filterEnvelopes_[i]->release(300);

      waveform1_[i]->begin(WAVEFORM_SQUARE);
      waveform2_[i]->begin(WAVEFORM_TRIANGLE);
      waveform3_[i]->begin(WAVEFORM_SAWTOOTH);

      waveform1_[i]->frequencyModulation(2.0);
      waveform2_[i]->frequencyModulation(2.0);
      waveform3_[i]->frequencyModulation(2.0);

      noiseAmplifiers_[i]->gain(0.0);
    }

    for (int i = 0; i < WAV_PER_VOICE; i++) {
      octavesPerWav_[i] = 0;
      tunePerWav_[i] = 0.0;
    }

    glideTime_ = 0.0;
    lastUpdateTime_ = millis();
    freqLFO_ = 2.0;
    tune_ = 0;
  }


  float computeWaveModifier(int wave) {
    return 12 * octavesPerWav_[wave] + tunePerWav_[wave] + tune_;
  }


  float computeFreq(float pitch) {
    return 220 * pow(2.0, (pitch - 45.0) / 12.0);
  }

#define MIN_AMPLIFICATION 0.15  // doesn't sound nice if amp is too low

  void soundVoice(uint8_t voice, uint8_t pitch, uint8_t velo, bool retrigger, bool glide) {
    IFERROR(voice < 0 || voice >= MAX_VOICES, "soundVoice voice is outsise range 0-2")

    float amplification = MIN_AMPLIFICATION + velo * (1.0 - MIN_AMPLIFICATION) / 127.0;

    waveform1_[voice]->amplitude(amplification);
    waveform2_[voice]->amplitude(amplification);
    if (!isLFO_ && voice != LFO_VOICE)
      waveform3_[voice]->amplitude(amplification);
    noiseAmplifiers_[voice]->gain(amplification);

    targetVoicePitch_[voice] = pitch;
    repitchVoice(voice, glide);

    //Serial.print("amp = "); Serial.print(amplification);
    //Serial.print(" freq = "); Serial.println(freq);


    if (retrigger) {
      filterEnvelopes_[voice]->noteOn();
      envelopes_[voice]->noteOn();
    }

    a.failIfCorrupt();
    b.failIfCorrupt();
  }


  void repitchVoice(int voice, bool isGlide) {
    if (glideTime_ == 0.0 || !isGlide)
      currentglidePitch_[voice] = targetVoicePitch_[voice];
    else if (targetVoicePitch_[voice] != currentglidePitch_[voice]) {
      float deltap = targetVoicePitch_[voice] - currentglidePitch_[voice];

      long deltat = millis() - lastUpdateTime_;
      //DEBUGVAL2("deltap", deltap,"deltat", deltat);

      if (deltat > 0) {
        if (deltap > 0.0) {
          currentglidePitch_[voice] += ((float)deltat / 1000.0 * 12.0 / glideTime_);

          if (currentglidePitch_[voice] > targetVoicePitch_[voice])
            currentglidePitch_[voice] = targetVoicePitch_[voice];
        } else {
          currentglidePitch_[voice] -= ((float)deltat / 1000.0 * 12.0 / glideTime_);

          if (currentglidePitch_[voice] < targetVoicePitch_[voice])
            currentglidePitch_[voice] = targetVoicePitch_[voice];
        }
      }
    }

    lastUpdateTime_ = millis();

    waveform1_[voice]->frequency(computeFreq(currentglidePitch_[voice] + computeWaveModifier(0)));
    waveform2_[voice]->frequency(computeFreq(currentglidePitch_[voice] + computeWaveModifier(1)));
    if (!isLFO_)
      waveform3_[voice]->frequency(computeFreq(currentglidePitch_[voice] + computeWaveModifier(2)));
  }


  void repitchAllWav() {
    for (int voice = 0; voice < MAX_VOICES; voice++)
      repitchVoice(voice, true);
  }


  void printSerialLn() {
    Serial.print("pitches ");

    for (int voice = 0; voice < MAX_VOICES; voice++) {
      Serial.print(currentglidePitch_[voice]);
      Serial.print(" ");
    }

    Serial.println();
  }


  void killVoice(uint8_t voice, bool legato) {
    IFERROR(voice < 0 || voice >= MAX_VOICES, "killVoice voice is outsise range 0-3")

    if (!legato) {
      envelopes_[voice]->noteOff();
      filterEnvelopes_[voice]->noteOff();
    }
  }


  void killAllVoices() {
    for (int i = 0; i < MAX_VOICES; i++)
      killVoice(i, false);
  }

  void setWavOctave(int wave, int val) {
    IFERROR(wave < 0 || wave >= WAV_PER_VOICE, "setWavOctave 'wave' outside 0-2 value")
    octavesPerWav_[wave] = val;
  }


  void setWaveTune(int wave, float t) {
    IFERROR(wave < 0 || wave >= WAV_PER_VOICE, "setWaveTune 'wave' outside 0-2 value")
    tunePerWav_[wave] = t;
  }

  void setGlobalTune(float t) {
    tune_ = t;
    repitchAllWav();
  }

  void setWaveform(int wave, int formselection) {
    IFERROR(wave < 0 || wave >= WAV_PER_VOICE, "setWaveform 'wave' outside 0-2 value")
    IFERROR(formselection < 0 || formselection > 11, "setWaveform 'formselection' outside 0-11 value")

    const int waveforms[12] = {
      WAVEFORM_SINE,               //0
      WAVEFORM_TRIANGLE,           //1
      WAVEFORM_TRIANGLE_VARIABLE,  //2
      WAVEFORM_TRIANGLE_VARIABLE,  //3
      WAVEFORM_SAWTOOTH,           //4
      WAVEFORM_SAWTOOTH_REVERSE,   //5
      WAVEFORM_SQUARE,             //6
      WAVEFORM_PULSE,              //7
      WAVEFORM_ARBITRARY,          //8
      WAVEFORM_ARBITRARY,          //9
      WAVEFORM_ARBITRARY,          //10
      WAVEFORM_SAMPLE_HOLD         //11
    };


    int finalwf = waveforms[formselection];


    const int16_t* wavetable;
    switch (formselection) {
      case 8: wavetable = AKWF_cello_0001; break;
      case 9: wavetable = AKWF_hvoice_0001; break;
      case 10: wavetable = AKWF_violin_0001; break;
    };


    DEBUGVAL("formselection", formselection)

    switch (wave) {
      case 0:

        waveform1_voice1.begin(finalwf);
        waveform1_voice2.begin(finalwf);
        waveform1_voice3.begin(finalwf);
        waveform1_voice4.begin(finalwf);

        if (finalwf == WAVEFORM_ARBITRARY) {
          waveform1_voice1.arbitraryWaveform(wavetable, 6000.0);
          waveform1_voice2.arbitraryWaveform(wavetable, 6000.0);
          waveform1_voice3.arbitraryWaveform(wavetable, 6000.0);
          waveform1_voice4.arbitraryWaveform(wavetable, 6000.0);
        }

        break;
      case 1:

        waveform2_voice1.begin(finalwf);
        waveform2_voice2.begin(finalwf);
        waveform2_voice3.begin(finalwf);
        waveform2_voice4.begin(finalwf);

        if (finalwf == WAVEFORM_ARBITRARY) {
          waveform2_voice1.arbitraryWaveform(wavetable, 6000.0);
          waveform2_voice2.arbitraryWaveform(wavetable, 6000.0);
          waveform2_voice3.arbitraryWaveform(wavetable, 6000.0);
          waveform2_voice4.arbitraryWaveform(wavetable, 6000.0);
        }

        break;
      case 2:
        waveform3_voice1.begin(finalwf);
        waveform3_voice2.begin(finalwf);
        waveform3_voice3.begin(finalwf);
        waveform3_voice4.begin(finalwf);

        if (finalwf == WAVEFORM_ARBITRARY) {
          waveform3_voice1.arbitraryWaveform(wavetable, 6000.0);
          waveform3_voice2.arbitraryWaveform(wavetable, 6000.0);
          waveform3_voice3.arbitraryWaveform(wavetable, 6000.0);
          waveform3_voice4.arbitraryWaveform(wavetable, 6000.0);
        }

        break;
    }
  }

  void setGlideTime(float v) {
    glideTime_ = v;
  }

  void setLFO(bool b) {
    DEBUGTXT("LFO is set")
    isLFO_ = b;
  }

  void setLFOFreq(float f) {
    DEBUGTXT("LFO is set")
    freqLFO_ = f;
  }

  void driveLFO() {
    if (isLFO_) {
      //DEBUGVAL("freqLFO_", freqLFO_)
      waveform3_[0]->frequency(freqLFO_);
      waveform3_[1]->frequency(freqLFO_);
      waveform3_[2]->frequency(freqLFO_);
      waveform3_[3]->frequency(freqLFO_);
      waveform3_[0]->amplitude(0.0);
      waveform3_[1]->amplitude(0.0);
      waveform3_[2]->amplitude(1.0);
      waveform3_[3]->amplitude(1.0);
    }
  }
};