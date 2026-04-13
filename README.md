# Binary LED Wristwatch

A compact, battery-powered binary wristwatch built around the ATmega32U4 microcontroller.
Time is displayed sequentially in binary format using four LEDs, with a fifth mode LED
indicating the current digit position and display mode.

## How It Works

Each decimal digit of the current time is displayed one at a time on four LEDs in binary.
A fifth LED blinks before each digit to indicate its position in the sequence (1–4).
After all four digits are shown, all LEDs blink simultaneously to signal the end of the cycle.

For example, 14:36 is displayed as four sequential binary values: 1, 4, 3, 6.

Three modes are supported, selected via the three onboard buttons:
- **Time** (HH:MM) — mode LED blinks at the fastest rate
- **Date** (DD/MM) — mode LED blinks at medium rate
- **Year** (YYYY) — mode LED blinks at the slowest rate

## Hardware

- **MCU:** ATmega32U4 (QFN, 8 MHz, 3.3V)
- **RTC:** DS3231M — temperature-compensated, I2C
- **Power:** LiPo battery + MCP73831 charging circuit + ME6217 LDO (3.3V)
- **Display:** 4x binary LEDs + 1x mode LED
- **Input:** 3x tactile buttons
- **PCB:** 4-layer, 42x42mm, designed in EasyEDA, manufactured as PCBA by JLCPCB

## Repository Structure

- `software/` — firmware source code and programming instructions
- `hardware/` — schematics (fixed revision)

### Known Hardware Issue

**Fixed:**
The D+ and D- lines between the micro-USB connector and the ATmega32U4 were swapped on
the PCB. As a result, the board could not be recognized as a USB device. All firmware was
flashed via the SPI header using Arduino UNO as an external ISP programmer.

SPI header **H1** is hanging over the bottom watch strap hole. Even though it is a THT
component, it was fairly difficult to remove. It would be recommended to avoid purchasing
this component already solderen on the board and upload firmware through pads instead.

## License

MIT
