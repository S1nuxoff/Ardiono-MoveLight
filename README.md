
# Motion-Responsive Lighting System

## Description
This project is a motion-responsive lighting system controlled by an Arduino. The system uses MOSFETs to manage LED lighting, button controls for mode switching, and additional components like an LDR and speaker for ambient light sensing and sound notifications. The system includes an LED indicator array for status feedback.

## Features
- **Motion-Responsive Lighting:** Adjusts LED brightness based on ambient light.
- **Multiple Modes:** Switch between different lighting modes using a button.
- **Sound Notifications:** Provides auditory feedback via a speaker.
- **Status Indication:** Displays system state using LED indicators.

## Components Used
- Arduino board
- 2x MOSFETs (for main and additional lighting)
- Button
- Light-Dependent Resistor (LDR)
- 5x LED indicators
- Speaker
- Resistors (10 kΩ, 220 Ω)
- White LED strips

## Wiring Diagram
Refer to the connection diagram in the project for detailed wiring instructions.

### Connecting White LED Strips to MOSFETs
1. **Positive terminal of the LED strip** connects to the external power source (+12V or +24V, depending on the strip type).
2. **Negative terminal of the LED strip** connects to the **Drain (D)** of the MOSFET.
3. **Gate (G)** of the MOSFET connects to a PWM pin on Arduino (pins 9 or 10).
4. **Source (S)** of the MOSFET connects to **GND**.

This setup allows the Arduino to control the brightness of the LED strips using PWM.

## Usage
1. Connect the components according to the wiring diagram.
2. Upload the Arduino sketch to your Arduino board.
3. Power the system via USB or an external 5V power source.
4. Use the button to switch between different lighting modes.
5. The system will automatically adjust the LED brightness based on ambient light.

---

*This README file was generated with the assistance of ChatGPT.* 
