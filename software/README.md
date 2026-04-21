# Firmware

Arduino C++ firmware for the binary LED wristwatch.

> **Note — old PCB revision:** the original PCB revision has a USB D+/D- swap
> that makes USB non-functional (see
> [Known Hardware Issues](../README.md#known-hardware-issues) in the root
> README). The bootloader must be burned via ISP on **both** revisions because
> the ATmega32U4 ships blank. On the current revision, all subsequent
> firmware uploads can be done over USB using `Sketch > Upload` with
> **Adafruit Feather 32U4** selected.

## Contents

- [Burning the Bootloader](#burning-the-bootloader)
- [Uploading Firmware](#uploading-firmware)
- [Libraries](#libraries)
- [Setting the Time](#setting-the-time)
- [Pin Map](#pin-map)

## Burning the Bootloader

The ATmega32U4 ships blank, so a bootloader must be burned before any firmware
can be uploaded. This is done with an Arduino UNO acting as an ISP programmer,
connected via the onboard SPI header.

### Requirements

- Arduino UNO
- Jumper wires
- 10 µF capacitor
- 3× 1 kΩ resistors (the UNO drives 5 V logic; the PCB runs at 3.3 V)

### Step 1 — Prepare the UNO as an ISP programmer

1. Open the Arduino IDE.
2. Open `File > Examples > 11.ArduinoISP > ArduinoISP`.
3. With `Tools > Board` set to **Arduino Uno**, upload the sketch to the UNO.
4. Place a 10 µF capacitor between the UNO's **RESET** and **GND** pins
   (positive terminal to RESET).

### Step 2 — Wire the UNO to the PCB SPI header

Add a 1 kΩ resistor in series on the MOSI, SCK, and RESET lines to bridge the
5 V → 3.3 V logic level difference. MISO needs no resistor.

| UNO Pin | Resistor | PCB SPI Header |
|---------|----------|----------------|
| Pin 13  | 1 kΩ     | SCK            |
| Pin 12  | —        | MISO           |
| Pin 11  | 1 kΩ     | MOSI           |
| Pin 10  | 1 kΩ     | RESET          |
| —       | —        | VCC            |
| GND     | —        | GND            |

> Do **not** connect VCC — the PCB is already powered at 3.3 V via either the
> LiPo battery or the USB cable.

### Step 3 — Burn the bootloader

1. In the Arduino IDE, install **Adafruit AVR Boards** via
   `Tools > Board > Boards Manager`.
2. Set `Tools > Board` to **Adafruit Feather 32U4** (8 MHz, 3.3 V).
3. Set `Tools > Programmer` to **Arduino as ISP**.
4. Click `Tools > Burn Bootloader`.

## Uploading Firmware

Once the bootloader has been burned:

- **Current PCB revision (working USB):** use the standard `Sketch > Upload`.
- **Old PCB revision (USB non-functional):** use `Sketch > Upload Using Programmer`
  with the ISP wiring from above.

## Libraries

Written in Arduino C++. The only external dependency is:

- [RTClib by Adafruit](https://github.com/adafruit/RTClib)

`Wire.h` is bundled with the Arduino IDE and requires no separate installation.

## Setting the Time

When the RTC loses power, the firmware automatically sets it to the sketch's
compile time using the `__DATE__` / `__TIME__` macros, so in most cases no
action is required.

To set a specific time manually instead, uncomment and edit the alternate
`rtc.adjust(...)` call in `setup()`:

```cpp
rtc.adjust(DateTime(2026, 4, 13, 14, 36, 0)); // Y, M, D, H, Min, Sec
```

Upload once with the line active, then comment it out and upload again.

## Pin Map

| Pin | Function        |
|-----|-----------------|
| 30  | LED 1 (MSB)     |
| 4   | LED 2           |
| 12  | LED 3           |
| 6   | LED 4 (LSB)     |
| 13  | Mode LED        |
| 0   | Button — Time   |
| 1   | Button — Date   |
| 11  | Button — Year   |
