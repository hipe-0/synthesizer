This DIY synthesizer was created by me in january 2024. (design, assembly, test, code)

Inspiration: The spec and interface is inspired by the 1970 Minimoog model D analogue synthesizer (https://fr.wikipedia.org/wiki/Minimoog)
But I have modernised it to my taste : 4 voices multiphonic, usb-midi, 12 waveforms, use of 5 linear potentiometers, LCD screen with user feedback, slight delay effect on audio output, surprise resonator added to audio feedback loop

# Short demo
https://github.com/user-attachments/assets/83d63550-5824-47d2-82ff-21bb06fb89ea

# Features
- 6x faders, 20x potentiometers, 4x rotary switches and 7x switches for audio control
- 3x voices
- Up to 4x notes simultaneously
- 12x selectable waveforms on each voice
- 1x octave selector for the 3x voices (12 presets)
- Monophonic / Multiphonic
- 1x low pass resonnant filter (typical Moog ladder filter simulation from https://github.com/PaulStoffregen/Audio/blob/master/filter_ladder.h)
- 1x LFO (low frequency oscilator)
- 2x Envelopes for amplitude and filter cutoff
- 3x Modulation sources: LFO or waveform 3 or noise
- 3x Modulation destinations: pitch, filter cut-off and pulse-width
- Modulation listen to midi controller mod wheel (no physical mod wheel on the synth itself)
- Pitch bend from midi controller (no physical pitch bend wheel on the synth itself)
- 7x LEDs
- LCD display, give text feedback about notes and knobs changed
- USB midi In
- USB host (to plug a usb midi keyboard on it)
- Currently mono audio output signal
- Audio processing via 1x Teensy 4.1 microprocessor and a dedicated audio shield (similar to a sound card for a PC)

![20240127_132244](https://github.com/user-attachments/assets/ca2eb124-2db5-49ac-ac9a-af0de6883007)
![20240129_154934](https://github.com/user-attachments/assets/62fbcdee-c000-49c3-8ec4-e17262387ee9)
![20240507_175413](https://github.com/user-attachments/assets/8f0f3085-c412-4e98-9714-f11e11df9299)
![20240109_073950](https://github.com/user-attachments/assets/cb40a885-a8ef-45ae-9ac5-cef7777bf6d3)

You can recreate this project using:

# code 
In this repository

# shematics
tbd (not completed at this point. It's complex project for my shematic skills)

# Audio library analogue connexions (it's a fully digital simulation of the analogue audio path)
It's using the open source "Teensy Audio Library" by PRJC ( https://www.pjrc.com/teensy/td_libs_Audio.html )
![2024-09-21 23_22_59-Audio System Design Tool for Teensy Audio Library](https://github.com/user-attachments/assets/b7d9e195-5441-40b6-9113-86c80dd63448)

# 3D printed parts
You can download my knob design for free on Thingiverse.
https://www.thingiverse.com/thing:6774170

# Bill of Materials
Links to store are shown only for convenience. 
- Teensy 4.1 (https://www.pjrc.com/store/teensy41.html)
- Teensy Audio shield (https://www.pjrc.com/store/teensy3_audio.html)
- usb host cable (prjc)
- 5x 75mm Linear potentiometers  (https://www.aliexpress.com/item/4000455671632.html)
- 1x 45mm Linear potentiometer 
- 14x Rotary potentiometers (https://www.aliexpress.com/item/1005003680612700.html)
- 7x Switches (https://www.aliexpress.com/item/1005003568092031.html)
- 4x Rotary switches with 12 rotational stops (https://www.aliexpress.com/item/4000466292355.html)
- 1x LCD screen 70x24mm
- 1x Rotary encoder (https://www.aliexpress.com/item/1005004907970664.html)
- 1x USB A plug female connector (for midi USB host)
- 7x LEDs WS2812B (cut individually from a 1m led strip) (https://www.aliexpress.com/item/4001249438672.html)
- 2x analogue multiplexors 16 chanels CD74HC4067 (https://www.aliexpress.com/item/1005005977095161.html)
- 1x jack female 6mm (for audio output) (https://www.aliexpress.com/item/1005004458769152.html)
- Sheet of plywood 4mm
- 6x My custom design 3d printed rotary knobs
- 5x My custom design 3d printed faders knob (https://www.thingiverse.com/thing:6774170)
- 1x Red fader knob
- acrylic paint
- various 3d printed labels
- 3d printed sides of synthesizer enclosure
