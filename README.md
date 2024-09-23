This DIY synthesizer was created by me in january 2024. (design, assembly, test, code)

Inspiration: The spec and interface is inspired by the 1970 Minimoog model D analogue synthesizer (https://fr.wikipedia.org/wiki/Minimoog)
But I have it modernised: 4 voices multiphonic, usb-midi, 12 waveforms, use of linear potentiometers

# Short demo
https://github.com/user-attachments/assets/83d63550-5824-47d2-82ff-21bb06fb89ea

# Features
- 26x faders
- 3x voices
- 12x selectable waveforms on each voice
- up to 4x notes simultaneously
- Monophonic / Multiphonic
- 1x low pass resonnant filter
- 1x LFO
- 1x envelope for amplitude
- 1x envelope for filter cutoff
- 3x modulation destinations: pitch, filter cut-off and pulse-width
- 3x modulation sources: modwheel, LFO, waveform 3
- modulation listen to midi controller mod wheel
- pitch bend
- Core : teensy 4.1 microcontroller board
- 7x LEDs
- LCD display, give text feedback about notes and knobs changed
- usb midi In
- usb host (to plug a usb midi keyboard on it)
- 1x Teensy 4.1 microprocessor for all audio processing

![20240127_132244](https://github.com/user-attachments/assets/ca2eb124-2db5-49ac-ac9a-af0de6883007)
![20240129_154934](https://github.com/user-attachments/assets/62fbcdee-c000-49c3-8ec4-e17262387ee9)
![20240507_175413](https://github.com/user-attachments/assets/8f0f3085-c412-4e98-9714-f11e11df9299)
![20240109_073950](https://github.com/user-attachments/assets/cb40a885-a8ef-45ae-9ac5-cef7777bf6d3)

You can recreate this project using:

# code 
In this repository

# shematics:
tbd

# Audio library analogue connexions:
![2024-09-21 23_22_59-Audio System Design Tool for Teensy Audio Library](https://github.com/user-attachments/assets/b7d9e195-5441-40b6-9113-86c80dd63448)


# Bill of Materials:
- Teensy 4.1 (https://www.pjrc.com/store/teensy41.html)
- Teensy Audio shield (https://www.pjrc.com/store/teensy3_audio.html)
- usb host cable (from prjc)
- 5x 75mm linear potentiometers  (https://www.aliexpress.com/item/4000455671632.html)
- 1x 45mm linear potentiometer 
- 18x rotary potentiometers (https://www.aliexpress.com/item/1005003680612700.html)
- 5x switches (https://www.aliexpress.com/item/1005003568092031.html)
- 4x rotary switches (https://www.aliexpress.com/item/4000466292355.html)
- 1x LCD screen
- 1x rotary encoder (https://www.aliexpress.com/item/1005004907970664.html)
- 1x usb A plug female
- 7x LEDs WS2812B (7x from a led strip) (https://www.aliexpress.com/item/4001249438672.html)
- 2x analogue multiplexors 16 chanels CD74HC4067 (https://www.aliexpress.com/item/1005005977095161.html)
- 1x jack female 6mm (https://www.aliexpress.com/item/1005004458769152.html)
- sheet of plywood 4mm
- 6x my custom design 3d printed rotary knobs (https://www.thingiverse.com/thing:6774170)
- 5x my custom design 3d printed faders knob (https://www.thingiverse.com/thing:6774170)
- 1x red fader knob
- acrylic paint
- various 3d printed labels
- 3d printed sides of synthesizer enclosure
