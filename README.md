# Binary LED Wristwatch

A compact, battery-powered binary wristwatch built around the ATmega32U4
microcontroller. The current time, date, and year are displayed one digit at a
time in binary on four LEDs, with a fifth mode LED indicating digit position
and active display mode.

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](#license)
![Platform](https://img.shields.io/badge/platform-ATmega32U4-blue)
![PCB](https://img.shields.io/badge/PCB-4%20layer%20%7C%2042%C3%9742%20mm-green)

<!-- Photo of the assembled watch goes here, e.g.:
<p align="center">
  <img src="docs/wristwatch.jpg" alt="Binary LED Wristwatch" width="420">
</p>
-->

## Table of Contents

- [How It Works](#how-it-works)
- [Display Modes](#display-modes)
- [Hardware](#hardware)
- [Repository Structure](#repository-structure)
- [Getting Started](#getting-started)
- [Known Hardware Issues](#known-hardware-issues)
- [License](#license)

## How It Works

Each decimal digit of the current value is shown on four LEDs in binary
(MSB → LSB). The mode LED blinks a number of times before each digit to
indicate its position in the sequence (1–4). After all four digits have been
shown, every LED blinks simultaneously to mark the end of the cycle.

Example — **14:36** is displayed as four sequential 4-bit values:

| Position | Digit | Binary |
|----------|-------|--------|
| 1        | 1     | `0001` |
| 2        | 4     | `0100` |
| 3        | 3     | `0011` |
| 4        | 6     | `0110` |

## Display Modes

Three modes are supported, selected via the three onboard buttons. The mode LED
blink rate indicates which mode is currently active.

| Mode | Format   | Mode LED Blink Rate |
|------|----------|---------------------|
| Time | `HH:MM`  | Fast                |
| Date | `DD/MM`  | Medium              |
| Year | `YYYY`   | Slow                |

## Hardware

| Component | Description                                                      |
|-----------|------------------------------------------------------------------|
| MCU       | ATmega32U4 (QFN, 8 MHz, 3.3 V)                                   |
| RTC       | DS3231M — temperature-compensated, I²C                           |
| Power     | LiPo battery + MCP73831 charger + ME6217 LDO (3.3 V)             |
| Display   | 4× binary LEDs + 1× mode LED                                     |
| Input     | 3× tactile buttons                                               |
| PCB       | 4-layer, 42 × 42 mm, designed in EasyEDA, assembled by JLCPCB    |

Schematic, Gerbers, BOM, and pick-and-place files are in [`hardware/`](hardware/).

## Repository Structure

```
binaryWatch/
├── hardware/   Schematic, Gerbers, BOM and pick-and-place files
├── software/   Firmware source and flashing instructions
└── README.md
```

## Getting Started

1. Fabricate the PCB and source components using the files in [`hardware/`](hardware/README.md).
2. Burn the bootloader and flash the firmware following [`software/README.md`](software/README.md).

## Known Hardware Issues

### Fixed — USB D+/D- swap

On the original PCB revision the D+ and D- lines between the micro-USB
connector and the ATmega32U4 were swapped, so the board could not be
recognised as a USB device. All firmware on affected boards was flashed via
the SPI header using an Arduino UNO as an ISP programmer. The schematic in
this repository is the **corrected revision** with the swap fixed.

### Assembly note — SPI header H1

SPI header **H1** overhangs the bottom watch-strap hole. Although it is a
through-hole component, it is awkward to desolder once installed. It is
therefore recommended to leave **H1 unpopulated** at PCBA time and flash the
bootloader directly through the header pads instead.

## License

Released under the [MIT License](LICENSE).
