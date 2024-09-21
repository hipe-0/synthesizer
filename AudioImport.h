#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioSynthNoisePink      noise1;         //xy=55,727.0000457763672
AudioSynthWaveformDc     PulseWidth; //xy=69.88888549804688,305.8888854980469
AudioMixer4              ModMixer;         //xy=123.8890266418457,550.8888359069824
AudioMixer4              PulseWidthModMixer; //xy=254.88892364501953,324.88892364501953
AudioSynthWaveformDc     CutoffFrequency; //xy=274.8889846801758,1132.0000848770142
AudioAmplifier           PitchMod; //xy=293.88899993896484,551.8889579772949
AudioAmplifier           CutoffMod;           //xy=310.88904571533203,1047.8891220092773
AudioSynthWaveformDc     FilterContour;  //xy=396.8890151977539,1211.000207901001
AudioSynthWaveformModulated waveform1_voice2; //xy=577.8889579772949,343.9999885559082
AudioSynthWaveformModulated waveform2_voice2; //xy=578.8889579772949,391.9999885559082
AudioSynthWaveformModulated waveform3_voice2; //xy=580.8889579772949,432.9999885559082
AudioSynthWaveformModulated waveform1_voice3; //xy=580.8889579772949,582.9999885559082
AudioSynthWaveformModulated waveform2_voice3; //xy=581.8889579772949,630.9999885559082
AudioSynthWaveformModulated waveform3_voice3; //xy=583.8889579772949,671.9999885559082
AudioSynthWaveformModulated waveform1_voice1; //xy=587.8889579772949,125.9999885559082
AudioSynthWaveformModulated waveform2_voice1; //xy=587.8889579772949,173.9999885559082
AudioSynthWaveformModulated waveform1_voice4; //xy=585.8888702392578,796.9999866485596
AudioSynthWaveformModulated waveform2_voice4; //xy=586.8888549804688,845
AudioSynthWaveformModulated waveform3_voice1; //xy=589.8889579772949,214.9999885559082
AudioSynthWaveformModulated waveform3_voice4; //xy=588.8888549804688,886
AudioAmplifier           noiseamp2;      //xy=603.8889617919922,489.00000858306885
AudioAmplifier           noiseamp1;      //xy=606.8889617919922,274.00000381469727
AudioAmplifier           noiseamp3;      //xy=607.8889198303223,745.0000038146973
AudioAmplifier           noiseamp4; //xy=612.8888168334961,959.0000152587891
AudioEffectEnvelope      FilterEnvelope1; //xy=652.8889617919922,1121.0000848770142
AudioEffectEnvelope      FilterEnvelope2; //xy=654.8889617919922,1182.0000867843628
AudioEffectEnvelope      FilterEnvelope3; //xy=682.8890228271484,1248.000087738037
AudioEffectEnvelope      FilterEnvelope4; //xy=702.8888397216797,1319.2221355438232
AudioMixer4              voice2;         //xy=800.8889617919922,362.00000762939453
AudioAnalyzePeak         peakLFO; //xy=801.8888626098633,926.888918876648
AudioMixer4              mixer1;         //xy=804.8889617919922,1128.0001125335693
AudioMixer4              voice3;         //xy=807.8890228271484,601.9999847412109
AudioMixer4              voice1;         //xy=810.8889617919922,144.00001907348633
AudioMixer4              voice4; //xy=815.888843536377,816.9999885559082
AudioMixer4              mixer2;         //xy=821.8889617919922,1188.0001125335693
AudioMixer4              mixer3;         //xy=835.8889617919922,1255.0001125335693
AudioMixer4              mixer4; //xy=851.8889045715332,1325.222255706787
AudioFilterLadder        ladder2;        //xy=997.8890266418457,375.0000686645508
AudioFilterLadder        ladder1;        //xy=998.8890914916992,158.00008010864258
AudioFilterLadder        ladder3;        //xy=1002.8891525268555,616.0001654624939
AudioFilterLadder        ladder4; //xy=1011.889030456543,831.0000476837158
AudioEffectEnvelope      envelope2;      //xy=1069.8891525268555,488.0001015663147
AudioEffectEnvelope      envelope1;      //xy=1072.8890762329102,278.00009632110596
AudioEffectEnvelope      envelope3;      //xy=1080.8892135620117,728.0001068115234
AudioEffectEnvelope      envelope4; //xy=1111.889030456543,942.0001735687256
AudioMixer4              mixer;          //xy=1256.8890953063965,381.0000686645508
AudioAmplifier           feedback;       //xy=1281.8890953063965,572.0000095367432
AudioMixer4              subMixer; //xy=1288.8889770507812,301.8888912200928
AudioEffectWaveshaper    waveshape1;     //xy=1323.8889770507812,647.888988494873
AudioMixer4              effectmixer;    //xy=1421.8889770507812,185.00001907348633
AudioEffectDelay         delay1;         //xy=1421.888973236084,456.0000190734863
AudioMixer4              FeedBackMixer;         //xy=1504.889060974121,622.8889179229736
AudioAmplifier           ampLeft;        //xy=1589.888973236084,143.00001907348633
AudioAmplifier           ampRight;       //xy=1590.888973236084,180.00001907348633
AudioAnalyzeRMS          rms;            //xy=1602.888973236084,234.00001907348633
AudioOutputI2S           i2s1;           //xy=1627.888973236084,78.00001907348633
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
AudioConnection          patchCord92(delay1, 1, effectmixer, 2);
AudioConnection          patchCord93(delay1, 2, effectmixer, 3);
AudioConnection          patchCord94(FeedBackMixer, 0, subMixer, 1);
AudioConnection          patchCord95(ampLeft, 0, i2s1, 0);
AudioConnection          patchCord96(ampRight, 0, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=1485.888973236084,776.0000190734863
// GUItool: end automatically generated code
