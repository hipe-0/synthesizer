
#include "MIDIUSB.h"  // 1.0.5 by Gary Grewal
#include "iferror.h"

class MidiIn {
private:
  void (*fptrNoteOn_)(uint8_t, uint8_t, uint8_t);
  void (*fptrNoteOff_)(uint8_t, uint8_t, uint8_t);
  void (*fptrKillAllNotes_)();

public:
  void setHandleNoteOn(void (*fptr)(uint8_t, uint8_t, uint8_t)) {
    fptrNoteOn_ = fptr;
  }

  void setHandleNoteOff(void (*fptr)(uint8_t, uint8_t, uint8_t)) {
    fptrNoteOff_ = fptr;
  }

  void setHandleKillAllNotes(void (*fptr)()) {
    fptrKillAllNotes_ = fptr;
  }

#define MIDI_CODE_NOTE_ON 0x09
#define MIDI_CODE_NOTE_OFF 0x08
#define MIDI_CODE_KILL_ALL_NOTES 0x0B


  void read() {
    midiEventPacket_t event = MidiUSB.read();

    if (event.header != 0)
      DEBUGVAL4("header", event.header, "byte1", event.byte1, "byte2", event.byte2, "byte3", event.byte3)

    if (event.header == MIDI_CODE_NOTE_ON)  // Midi code for note on
    {
      fptrNoteOn_(0, event.byte2, event.byte3);
    }

    if (event.header == MIDI_CODE_NOTE_OFF) {
      fptrNoteOff_(0, event.byte2, event.byte3);
    }

    if (event.header == MIDI_CODE_KILL_ALL_NOTES) {
      fptrKillAllNotes_();
    }
  }

  // First parameter is the event type (0x09 = note on, 0x08 = note off).
  // Second parameter is note-on/note-off, combined with the channel.
  // Channel can be anything between 0-15. Typically reported to the user as 1-16.
  // Third parameter is the note number (48 = middle C).
  // Fourth parameter is the velocity (64 = normal, 127 = fastest).

  void noteOn(byte channel, byte pitch, byte velocity) {
    midiEventPacket_t noteOn = { 0x09, 0x90 | channel, pitch, velocity };
    MidiUSB.sendMIDI(noteOn);
  }

  void noteOff(byte channel, byte pitch, byte velocity) {
    midiEventPacket_t noteOff = { 0x08, 0x80 | channel, pitch, velocity };
    MidiUSB.sendMIDI(noteOff);
  }


  void killAllNotes() {
    for (int i = 0; i < 128; i++)
      noteOff(0, i, 0);
  }

  void flush() {
    MidiUSB.flush();
  }

  // First parameter is the event type (0x0B = control change).
  // Second parameter is the event type, combined with the channel.
  // Third parameter is the control number number (0-119).
  // Fourth parameter is the control value (0-127).
  void controlChange(byte channel, byte control, byte value) {
    midiEventPacket_t event = { 0x0B, 0xB0 | channel, control, value };
    MidiUSB.sendMIDI(event);
  }
};
