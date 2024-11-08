# Motion-Responsive Lighting System

## Description

This project is a motion-responsive lighting system controlled by an Arduino. The system uses MOSFETs to manage LED lighting, button controls for mode switching, and additional components like an LDR and speaker for ambient light sensing and sound notifications. The system includes an LED indicator array for status feedback.

## Features

- **Motion-Responsive Lighting:** Adjusts LED brightness based on ambient light.
- **Multiple Modes:** Switch between different lighting modes using a button.
- **Sound Notifications:** Provides auditory feedback via a speaker.
- **Status Indication:** Displays system state using LED indicators.

## Libraries Used

### 1. FastLED

- [GitHub Repository](https://github.com/FastLED/FastLED)
- [Documentation](https://fastled.io/docs/)

### 2. GyverButton

- [GitHub Repository](https://github.com/GyverLibs/GyverButton)
- [Documentation](https://alexgyver.ru/gyverbutton/)

_Note:_ The author of GyverButton also recommends using the newer **EncButton** library:

- [GitHub Repository for EncButton](https://github.com/GyverLibs/EncButton)

## Components Used

- Arduino board
- 2x MOSFETs (for main and additional lighting)
- Button
- Light-Dependent Resistor (LDR)
- 5x LED indicators
- Speaker
- Resistors (10 kΩ, 220 Ω)
- White LED strips

## Usage

1. Connect the components according to the wiring diagram.
2. Upload the Arduino sketch to your Arduino board.
3. Power the system via USB or an external 5V power source.
4. Use the button to switch between different lighting modes.
5. The system will automatically adjust the LED brightness based on ambient light.

---

_This README file was generated with the assistance of ChatGPT._
