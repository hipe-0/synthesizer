class Synthesizer {
private:
  bool isForceUpdate;
  volatile float modWheel_;
  float modWheelPrevious_;
  float addedContour_;
  float breathcontrolerVolume_;

public:

  Synthesizer() {
    isForceUpdate = true;
    modWheel_ = 0.0;
    addedContour_ = 0.0;
    breathcontrolerVolume_ = 1.0;
  }

  void setBreathControlervolume(float value) {
    breathcontrolerVolume_ = value;
  }

private:
  void manageSwitches_() {

    if (switches.isChanged(SWITCH_POLYPHONY) || isForceUpdate)
      if (switches.getState(SWITCH_POLYPHONY) == 1) {
        DEBUGTXT("Switched to mono")
        voices.killVoice(1, false);
        voices.killVoice(2, false);
        voices.killVoice(3, false);
      }

    if (switches.isChanged(SWITCH_LFO) || isForceUpdate) {
      bool isLFO = switches.getState(SWITCH_LFO) == 1;
      DEBUGTXT("Switched  LFO/detune3")

      voices.setLFO(isLFO);
    }
  }

// reducing volume for 4 voices, in order to avoid mixer saturation
#define MIXER_VOLUME 0.25

  void manageVolumeMixer_()  // volumes per voice, feedback, noise
  {

    float volume1 = pots.getPotValueMaped(POT_VOLUME1) * MIXER_VOLUME;
    float volume2 = pots.getPotValueMaped(POT_VOLUME2) * MIXER_VOLUME;
    float volume3 = pots.getPotValueMaped(POT_VOLUME3) * MIXER_VOLUME;
    float volumefb = pots.getPotValueMaped(POT_VOLUME_FEEDBACK);
    float volumeNoise = pots.getPotValueMaped(POT_VOLUME_NOISE) * MIXER_VOLUME;
    voice1.gain(0, volume1);
    voice2.gain(0, volume1);
    voice3.gain(0, volume1);
    voice4.gain(0, volume1);
    voice1.gain(1, volume2);
    voice2.gain(1, volume2);
    voice3.gain(1, volume2);
    voice4.gain(1, volume2);

    if (switches.getState(SWITCH_LFO) == 1) {
      voice1.gain(2, 0.0);
      voice2.gain(2, 0.0);
      voice3.gain(2, 0.0);
      voice4.gain(2, 0.0);
    } else {
      voice1.gain(2, volume3);
      voice2.gain(2, volume3);
      voice3.gain(2, volume3);
      voice4.gain(2, volume3);
    }

    voice1.gain(3, volumeNoise);
    voice2.gain(3, volumeNoise);
    voice3.gain(3, volumeNoise);
    voice4.gain(3, volumeNoise);
    feedback.gain(volumefb);
  }


  void manageMultiplexer1_()  // ADSR, master volume, cutoff, resonance, filter amount
  {
    float attack = mux1.getPotValueMaped(MUX_ATTACK);
    float decay = mux1.getPotValueMaped(MUX_DECAY);
    float sustain = mux1.getPotValueMaped(MUX_SUSTAIN);
    float release = decay;

    float cutoff = mux1.getPotValueMaped(MUX_CUTOFF_FREQUENCY);
    float resonance = mux1.getPotValueMaped(MUX_RESONANCE);

    float filterAttack = mux1.getPotValueMaped(MUX_FILTER_ATTACK);
    float filterDecay = mux1.getPotValueMaped(MUX_FILTER_DECAY);
    float filterSustain = mux1.getPotValueMaped(MUX_FILTER_SUSTAIN);
    float filterRelease = filterDecay;
    float contour = mux1.getPotValueMaped(MUX_CONTOUR);

    float masterVolume = mux1.getPotValueMaped(MUX_MASTER_VOLUME) * breathcontrolerVolume_;
    ampLeft.gain(masterVolume);
    ampRight.gain(masterVolume);

    CutoffFrequency.amplitude(cutoff);
    FilterContour.amplitude(contour + addedContour_);
    //DEBUGVAL("addedContour_", addedContour_)

    ladder1.resonance(resonance);
    ladder2.resonance(resonance);
    ladder3.resonance(resonance);
    ladder4.resonance(resonance);

    envelope1.attack(attack);
    envelope2.attack(attack);
    envelope3.attack(attack);
    envelope4.attack(attack);
    envelope1.decay(decay);
    envelope2.decay(decay);
    envelope3.decay(decay);
    envelope4.decay(decay);
    envelope1.sustain(sustain);
    envelope2.sustain(sustain);
    envelope3.sustain(sustain);
    envelope4.sustain(sustain);


    if (switches.getState(SWITCH_RELEASE) == 0) {
      envelope1.release(release);
      envelope2.release(release);
      envelope3.release(release);
      envelope4.release(release);
    } else {
      envelope1.release(5.0);
      envelope2.release(5.0);
      envelope3.release(5.0);
      envelope4.release(5.0);
    }

    FilterEnvelope1.attack(filterAttack);
    FilterEnvelope2.attack(filterAttack);
    FilterEnvelope3.attack(filterAttack);
    FilterEnvelope4.attack(filterAttack);
    FilterEnvelope1.decay(filterDecay);
    FilterEnvelope2.decay(filterDecay);
    FilterEnvelope3.decay(filterDecay);
    FilterEnvelope4.decay(filterDecay);
    FilterEnvelope1.sustain(filterSustain);
    FilterEnvelope2.sustain(filterSustain);
    FilterEnvelope3.sustain(filterSustain);
    FilterEnvelope4.sustain(filterSustain);
    FilterEnvelope1.release(filterRelease);
    FilterEnvelope2.release(filterRelease);
    FilterEnvelope3.release(filterRelease);
    FilterEnvelope4.release(filterRelease);
  }

  float mapfloat(float x, float in_min, float in_max, float out_min, float out_max) {
    return (x - in_min) * (out_max - out_min) / (float)(in_max - in_min) + out_min;
  }

  void manageMultiplexer2_()  // tuning, octave, waveform
  {
    if (mux2.hasChanged(MUX2_TUNE2) || isForceUpdate) {
      float f = mux2.getPotValueMaped(MUX2_TUNE2);
      voices.setWaveTune(1, f);  // 1 is wave number 2
      voices.repitchAllWav();
    }

    if (mux2.hasChanged(MUX2_TUNE3) || isForceUpdate) {
      float f = mux2.getPotValueMaped(MUX2_TUNE3);
      voices.setWaveTune(2, f);  // 2 is wave number 3

      float lfofreq = mapfloat(f, -5.0, 5.0, 0.5, 20);
      voices.setLFOFreq(lfofreq);
      voices.repitchAllWav();
    }

    if (mux2.hasChanged(MUX2_GLIDETIME) || isForceUpdate) {
      float f = mux2.getPotValueMaped(MUX2_GLIDETIME);
      voices.setGlideTime(f);
      voices.repitchAllWav();
    }

    if (mux2.hasChanged(MUX2_OCTAVE) || isForceUpdate) {
      int octaveSwitch = round(mux2.getPotValueMaped(MUX2_OCTAVE));

      DEBUGVAL("octaveswitch", octaveSwitch)

      for (int w = 0; w < 3; w++)
        voices.setWavOctave(w, OCTAVES[octaveSwitch][w]);

      voices.repitchAllWav();
    }

    if (mux2.hasChanged(MUX2_WAVEFORM1) || isForceUpdate) {
      int waveform = round(mux2.getPotValueMaped(MUX2_WAVEFORM1));
      voices.setWaveform(0, waveform);
    }
    if (mux2.hasChanged(MUX2_WAVEFORM2) || isForceUpdate) {
      int waveform = round(mux2.getPotValueMaped(MUX2_WAVEFORM2));
      voices.setWaveform(1, waveform);
    }
    if (mux2.hasChanged(MUX2_WAVEFORM3) || isForceUpdate) {
      int waveform = round(mux2.getPotValueMaped(MUX2_WAVEFORM3));
      voices.setWaveform(2, waveform);
    }

    if (mux2.hasChanged(MUX2_MIX) || isForceUpdate) {
      float mix = mux2.getPotValueMaped(MUX2_MIX);
      ModMixer.gain(0, 1.0 - mix);  // OSC3 channel
      ModMixer.gain(1, mix);        // noise channel
    }

    if (mux2.hasChanged(MUX2_PULSE_WIDTH) || isForceUpdate) {
      float pw = mux2.getPotValueMaped(MUX2_PULSE_WIDTH);
      PulseWidth.amplitude(pw);
    }
  }


  void manageModWheel_() {

    if (modWheelPrevious_ != modWheel_) {
      lcd.loadTxt("Modulation Wheel", modWheel_);
      lcd.displayLoaded();
    }
    modWheelPrevious_ = modWheel_;


    if (switches.getState(SWITCH_CUTOFF_MOD) == 0)
      CutoffMod.gain(modWheel_);
    else
      CutoffMod.gain(0.0);

    if (switches.getState(SWITCH_PITCH_MOD) == 0)
      PitchMod.gain(modWheel_);
    else
      PitchMod.gain(0.0);

    if (switches.getState(SWITCH_PULSE_WIDTH_MOD) == 0)
      PulseWidthModMixer.gain(1, modWheel_);
    else
      PulseWidthModMixer.gain(1, 0.0);
  }



  void lcdPrintPotChanges_() {
    if (isForceUpdate) return;

    for (int i = 0; i < 16; i++)
      if (pots.hasChanged(i))
        lcd.loadTxt(POT_NAMES[i], pots.getPotValueMaped(i));

    for (int i = 0; i < 16; i++)
      if (mux1.hasChanged(i))
        lcd.loadTxt(MUX_NAMES[i], mux1.getPotValueMaped(i));

    for (int i = 0; i < 16; i++)
      if (mux2.hasChanged(i)) {
        switch (i) {
          case MUX2_OCTAVE:
            {
              int select = (int)round(mux2.getPotValueMaped(i));
              lcd.loadTxt(OCTAVES_NAMES[select]);
              break;
            }
          case MUX2_WAVEFORM1:
          case MUX2_WAVEFORM2:
          case MUX2_WAVEFORM3:
            {
              int select = (int)round(mux2.getPotValueMaped(i));
              lcd.loadTxt(WAVEFORM_NAMES[select]);
              break;
            }
          case MUX2_TUNE2:
          case MUX2_TUNE3:
          case MUX2_GLIDETIME:
          case MUX2_MIX:
          case MUX2_PULSE_WIDTH:
            lcd.loadTxt(MUX2_NAMES[i], mux2.getPotValueMaped(i));
        };
      }

    for (int i = 0; i < BUTTON_NUM; i++)
      if (switches.isChanged(i))
        lcd.loadTxt(SWITCH_NAMES[i], switches.getState(i));

    lcd.displayLoaded();
  }


  void serialPrintPotChanges_() {
    for (int i = 0; i < 16; i++)
      if (pots.hasChanged(i)) {
        Serial.print(POT_NAMES[i]);
        Serial.print(" = ");
        Serial.print(pots.getRawPotValue(i));
        Serial.print(" = ");
        Serial.println(pots.getPotValueMaped(i));
      }

    for (int i = 0; i < 16; i++)
      if (mux1.hasChanged(i)) {
        Serial.print(MUX_NAMES[i]);
        Serial.print(" = ");
        Serial.print(mux1.getRawPotValue(i));
        Serial.print(" = ");
        Serial.println(mux1.getPotValueMaped(i));
      }

    for (int i = 0; i < 16; i++)
      if (mux2.hasChanged(i)) {
        Serial.print(MUX2_NAMES[i]);
        Serial.print(" = ");
        Serial.print(mux2.getRawPotValue(i));
        Serial.print(" = ");
        Serial.println(mux2.getPotValueMaped(i));
      }


    for (int i = 0; i < BUTTON_NUM; i++)
      if (switches.isChanged(i)) {
        Serial.print(SWITCH_NAMES[i]);
        Serial.print(" = ");
        Serial.println(switches.getState(i));
      }
  }

public:

  void manageParameters() {
    // read sensors
    switches.update();
    pots.readPotentiometers();
    mux1.readPotentiometers();
    mux2.readPotentiometers();


    // manage the synth logic based on sensors
    manageSwitches_();
    manageVolumeMixer_();
    manageMultiplexer1_();
    manageMultiplexer2_();
    manageModWheel_();


    lcdPrintPotChanges_();
    //Serial.print(" mux2: ");
    //mux2.serialPrintAllPotentiometersln();
    serialPrintPotChanges_();

    if (isForceUpdate) {
      DEBUGTXT("Synth parameter initialisation complete")
      isForceUpdate = false;
    }
  }

  void setModWheel(float value) {
    modWheel_ = value;
  }

  float getModWheel() {
    return modWheel_;
  }

  void setAddedContour(float value) {
    addedContour_ = value;
  }

} synth;