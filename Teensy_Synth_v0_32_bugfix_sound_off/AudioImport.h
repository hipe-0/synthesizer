#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioSynthNoisePink      noise1;         //xy=82.88889694213867,716.0000114440918
AudioSynthWaveformDc     PulseWidth;     //xy=96.88889694213867,294.0000114440918
AudioMixer4              ModMixer;       //xy=150.88889694213867,539.0000114440918
AudioMixer4              PulseWidthModMixer; //xy=281.8888969421387,313.0000114440918
AudioSynthWaveformDc     CutoffFrequency; //xy=301.8888969421387,1121.0000114440918
AudioAmplifier           PitchMod;       //xy=320.8888969421387,540.0000114440918
AudioAmplifier           CutoffMod;      //xy=337.8888969421387,1036.0000114440918
AudioSynthWaveformDc     FilterContour;  //xy=423.8888969421387,1200.0000114440918
AudioSynthWaveformModulated waveform1_voice2; //xy=604.8888969421387,332.0000114440918
AudioSynthWaveformModulated waveform2_voice2; //xy=605.8888969421387,380.0000114440918
AudioSynthWaveformModulated waveform3_voice2; //xy=607.8888969421387,421.0000114440918
AudioSynthWaveformModulated waveform1_voice3; //xy=607.8888969421387,571.0000114440918
AudioSynthWaveformModulated waveform2_voice3; //xy=608.8888969421387,619.0000114440918
AudioSynthWaveformModulated waveform3_voice3; //xy=610.8888969421387,660.0000114440918
AudioSynthWaveformModulated waveform1_voice1; //xy=614.8888969421387,114.0000114440918
AudioSynthWaveformModulated waveform2_voice1; //xy=614.8888969421387,162.0000114440918
AudioSynthWaveformModulated waveform1_voice4; //xy=612.8888969421387,785.0000114440918
AudioSynthWaveformModulated waveform2_voice4; //xy=613.8888969421387,834.0000114440918
AudioSynthWaveformModulated waveform3_voice1; //xy=616.8888969421387,203.0000114440918
AudioSynthWaveformModulated waveform3_voice4; //xy=615.8888969421387,875.0000114440918
AudioAmplifier           noiseamp2;      //xy=630.8888969421387,478.0000114440918
AudioAmplifier           noiseamp1;      //xy=633.8888969421387,263.0000114440918
AudioAmplifier           noiseamp3;      //xy=634.8888969421387,734.0000114440918
AudioAmplifier           noiseamp4;      //xy=639.8888969421387,948.0000114440918
AudioEffectEnvelope      FilterEnvelope1; //xy=679.8888969421387,1110.0000114440918
AudioEffectEnvelope      FilterEnvelope2; //xy=681.8888969421387,1171.0000114440918
AudioEffectEnvelope      FilterEnvelope3; //xy=709.8888969421387,1237.0000114440918
AudioEffectEnvelope      FilterEnvelope4; //xy=729.8888969421387,1308.0000114440918
AudioMixer4              voice2;         //xy=827.8888969421387,351.0000114440918
AudioAnalyzePeak         peakLFO;        //xy=828.8888969421387,915.0000114440918
AudioMixer4              mixer1;         //xy=831.8888969421387,1117.0000114440918
AudioMixer4              voice3;         //xy=834.8888969421387,590.0000114440918
AudioMixer4              voice1;         //xy=837.8888969421387,133.0000114440918
AudioMixer4              voice4;         //xy=842.8888969421387,805.0000114440918
AudioMixer4              mixer2;         //xy=848.8888969421387,1177.0000114440918
AudioMixer4              mixer3;         //xy=862.8888969421387,1244.0000114440918
AudioMixer4              mixer4;         //xy=878.8888969421387,1314.0000114440918
AudioFilterLadder        ladder2;        //xy=1024.8888969421387,364.0000114440918
AudioFilterLadder        ladder1;        //xy=1025.8888969421387,147.0000114440918
AudioFilterLadder        ladder3;        //xy=1029.8888969421387,605.0000114440918
AudioFilterLadder        ladder4;        //xy=1038.8888969421387,820.0000114440918
AudioEffectEnvelope      envelope2;      //xy=1096.8888969421387,477.0000114440918
AudioEffectEnvelope      envelope1;      //xy=1099.8888969421387,267.0000114440918
AudioEffectEnvelope      envelope3;      //xy=1107.8888969421387,717.0000114440918
AudioEffectEnvelope      envelope4;      //xy=1138.8888969421387,931.0000114440918
AudioMixer4              mixer;          //xy=1283.8888969421387,370.0000114440918
AudioAmplifier           feedback;       //xy=1308.8888969421387,561.0000114440918
AudioMixer4              subMixer;       //xy=1315.8888969421387,290.0000114440918
AudioEffectWaveshaper    waveshape1;     //xy=1350.8888969421387,636.0000114440918
AudioMixer4              effectmixer;    //xy=1448.8888969421387,174.0000114440918
AudioEffectDelay         delay1;         //xy=1448.8888969421387,445.0000114440918
AudioMixer4              FeedBackMixer;  //xy=1531.8888969421387,611.0000114440918
AudioAmplifier           ampLeft;        //xy=1616.8888969421387,132.0000114440918
AudioAmplifier           ampRight;       //xy=1617.8888969421387,169.0000114440918
AudioAnalyzeRMS          rms;            //xy=1629.8888969421387,223.0000114440918
AudioOutputI2S           i2s1;           //xy=1654.8888969421387,67.0000114440918
AudioConnection          patchCord1(noise1, noiseamp1);
AudioConnection          patchCord2(noise1, noiseamp2);
AudioConnection          patchCord3(noise1, noiseamp3);
AudioConnection          patchCord4(noise1, 0, ModMixer, 1);
AudioConnection          patchCord5(noise1, noiseamp4);
AudioConnection          patchCord6(PulseWidth, 0, PulseWidthModMixer, 0);
AudioConnection          patchCord7(ModMixer, PitchMod);
AudioConnection          patchCord8(ModMixer, CutoffMod);
AudioConnection          patchCord9(ModMixer, 0, PulseWidthModMixer, 1);
AudioConnection          patchCord10(PulseWidthModMixer, 0, waveform1_voice1, 1);
AudioConnection          patchCord11(PulseWidthModMixer, 0, waveform2_voice1, 1);
AudioConnection          patchCord12(PulseWidthModMixer, 0, waveform3_voice1, 1);
AudioConnection          patchCord13(PulseWidthModMixer, 0, waveform1_voice2, 1);
AudioConnection          patchCord14(PulseWidthModMixer, 0, waveform2_voice2, 1);
AudioConnection          patchCord15(PulseWidthModMixer, 0, waveform3_voice2, 1);
AudioConnection          patchCord16(PulseWidthModMixer, 0, waveform1_voice3, 1);
AudioConnection          patchCord17(PulseWidthModMixer, 0, waveform2_voice3, 1);
AudioConnection          patchCord18(PulseWidthModMixer, 0, waveform3_voice3, 1);
AudioConnection          patchCord19(PulseWidthModMixer, 0, waveform3_voice4, 1);
AudioConnection          patchCord20(PulseWidthModMixer, 0, waveform2_voice4, 1);
AudioConnection          patchCord21(PulseWidthModMixer, 0, waveform1_voice4, 1);
AudioConnection          patchCord22(CutoffFrequency, 0, mixer1, 0);
AudioConnection          patchCord23(CutoffFrequency, 0, mixer2, 0);
AudioConnection          patchCord24(CutoffFrequency, 0, mixer3, 0);
AudioConnection          patchCord25(CutoffFrequency, 0, mixer4, 0);
AudioConnection          patchCord26(PitchMod, 0, waveform3_voice2, 0);
AudioConnection          patchCord27(PitchMod, 0, waveform2_voice2, 0);
AudioConnection          patchCord28(PitchMod, 0, waveform1_voice2, 0);
AudioConnection          patchCord29(PitchMod, 0, waveform3_voice1, 0);
AudioConnection          patchCord30(PitchMod, 0, waveform2_voice1, 0);
AudioConnection          patchCord31(PitchMod, 0, waveform1_voice1, 0);
AudioConnection          patchCord32(PitchMod, 0, waveform1_voice3, 0);
AudioConnection          patchCord33(PitchMod, 0, waveform2_voice3, 0);
AudioConnection          patchCord34(PitchMod, 0, waveform3_voice3, 0);
AudioConnection          patchCord35(CutoffMod, 0, mixer1, 2);
AudioConnection          patchCord36(CutoffMod, 0, mixer2, 2);
AudioConnection          patchCord37(CutoffMod, 0, mixer3, 2);
AudioConnection          patchCord38(CutoffMod, 0, mixer4, 2);
AudioConnection          patchCord39(FilterContour, FilterEnvelope1);
AudioConnection          patchCord40(FilterContour, FilterEnvelope2);
AudioConnection          patchCord41(FilterContour, FilterEnvelope3);
AudioConnection          patchCord42(FilterContour, FilterEnvelope4);
AudioConnection          patchCord43(waveform1_voice2, 0, voice2, 0);
AudioConnection          patchCord44(waveform2_voice2, 0, voice2, 1);
AudioConnection          patchCord45(waveform3_voice2, 0, voice2, 2);
AudioConnection          patchCord46(waveform1_voice3, 0, voice3, 0);
AudioConnection          patchCord47(waveform2_voice3, 0, voice3, 1);
AudioConnection          patchCord48(waveform3_voice3, 0, voice3, 2);
AudioConnection          patchCord49(waveform1_voice1, 0, voice1, 0);
AudioConnection          patchCord50(waveform2_voice1, 0, voice1, 1);
AudioConnection          patchCord51(waveform1_voice4, 0, voice4, 0);
AudioConnection          patchCord52(waveform2_voice4, 0, voice4, 1);
AudioConnection          patchCord53(waveform3_voice1, 0, voice1, 2);
AudioConnection          patchCord54(waveform3_voice4, 0, voice4, 2);
AudioConnection          patchCord55(waveform3_voice4, peakLFO);
AudioConnection          patchCord56(waveform3_voice4, 0, ModMixer, 0);
AudioConnection          patchCord57(noiseamp2, 0, voice2, 3);
AudioConnection          patchCord58(noiseamp1, 0, voice1, 3);
AudioConnection          patchCord59(noiseamp3, 0, voice3, 3);
AudioConnection          patchCord60(noiseamp4, 0, voice4, 3);
AudioConnection          patchCord61(FilterEnvelope1, 0, mixer1, 1);
AudioConnection          patchCord62(FilterEnvelope2, 0, mixer2, 1);
AudioConnection          patchCord63(FilterEnvelope3, 0, mixer3, 1);
AudioConnection          patchCord64(FilterEnvelope4, 0, mixer4, 1);
AudioConnection          patchCord65(voice2, 0, ladder2, 0);
AudioConnection          patchCord66(mixer1, 0, ladder1, 1);
AudioConnection          patchCord67(voice3, 0, ladder3, 0);
AudioConnection          patchCord68(voice1, 0, ladder1, 0);
AudioConnection          patchCord69(voice4, 0, ladder4, 0);
AudioConnection          patchCord70(mixer2, 0, ladder2, 1);
AudioConnection          patchCord71(mixer3, 0, ladder3, 1);
AudioConnection          patchCord72(mixer4, 0, ladder4, 1);
AudioConnection          patchCord73(ladder2, envelope2);
AudioConnection          patchCord74(ladder1, envelope1);
AudioConnection          patchCord75(ladder3, envelope3);
AudioConnection          patchCord76(ladder4, envelope4);
AudioConnection          patchCord77(envelope2, 0, mixer, 1);
AudioConnection          patchCord78(envelope1, 0, mixer, 0);
AudioConnection          patchCord79(envelope3, 0, mixer, 2);
AudioConnection          patchCord80(envelope4, 0, mixer, 3);
AudioConnection          patchCord81(mixer, 0, subMixer, 0);
AudioConnection          patchCord82(feedback, 0, FeedBackMixer, 0);
AudioConnection          patchCord83(feedback, waveshape1);
AudioConnection          patchCord84(subMixer, 0, effectmixer, 0);
AudioConnection          patchCord85(subMixer, delay1);
AudioConnection          patchCord86(subMixer, feedback);
AudioConnection          patchCord87(waveshape1, 0, FeedBackMixer, 1);
AudioConnection          patchCord88(effectmixer, rms);
AudioConnection          patchCord89(effectmixer, ampLeft);
AudioConnection          patchCord90(effectmixer, ampRight);
AudioConnection          patchCord91(delay1, 0, effectmixer, 1);
AudioConnection          patchCord92(FeedBackMixer, 0, subMixer, 1);
AudioConnection          patchCord93(ampLeft, 0, i2s1, 0);
AudioConnection          patchCord94(ampRight, 0, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1; //xy=1512.8888969421387,765.0000114440918
// GUItool: end automatically generated code
