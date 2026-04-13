> **Note:** Old revision of the PCB has a hardware bug causing USB to be non-functional.
> See the Known Hardware Issues section in the root README for details. The bootloader
> still needs to be burned via ISP regardless of PCB revision, as the chip ships blank.
> On a current revision, only the bootloader burn requires ISP — all subsequent firmware
> uploads can be done over USB using `Sketch > Upload` with Adafruit Feather 32U4 selected.

## Programming

The ATmega32U4 ships blank and requires a bootloader to be burned first before any
firmware can be uploaded. This is done using an Arduino UNO as an ISP programmer via
the onboard SPI header.

### Requirements
- Arduino UNO
- Jumper wires
- 10µF capacitor
- 3x 1K resistors (the UNO outputs 5V logic, the PCB runs at 3.3V)

### Step 1 — Prepare the UNO as an ISP programmer

1. Open Arduino IDE
2. Go to `File > Examples > 11.ArduinoISP > ArduinoISP`
3. Upload the sketch to the UNO with `Tools > Board` set to **Arduino Uno**
4. Place a 10µF capacitor between the UNO's **RESET** and **GND** pins (positive to RESET)

### Step 2 — Wire the UNO to the PCB SPI header

Add a 1K resistor in series on MOSI, SCK and RESET lines. This is required because the
UNO outputs 5V logic and the PCB runs at 3.3V. MISO needs no resistor.

| UNO Pin | Resistor | PCB SPI Header |
|---------|----------|----------------|
| Pin 13  | 1K       | SCK            |
| Pin 12  | —        | MISO           |
| Pin 11  | 1K       | MOSI           |
| Pin 10  | 1K       | RESET          |
| —       | —        | VCC            |
| GND     | —        | GND            |

(do not connect VCC — PCB is powered with 3.3 V by either LiPo battery or USB cable)

### Step 3 — Burn the bootloader

1. In Arduino IDE, install **Adafruit AVR Boards** via `Tools > Board > Boards Manager`
2. Set `Tools > Board` to **Adafruit Feather 32U4** (8MHz, 3.3V — matches this hardware)
3. Set `Tools > Programmer` to **Arduino as ISP**
4. Click `Tools > Burn Bootloader`

### Step 4 — Uploading Firmware

After the bootloader is burned, use `Sketch > Upload Using Programmer` for all future
uploads on old revision. On a current PCB revision with working USB, use the standard
`Sketch > Upload` instead.

## Firmware

Written in Arduino C++. Uses the following library:

- [RTClib by Adafruit](https://github.com/adafruit/RTClib)

`Wire.h` is built into Arduino IDE and requires no separate installation.

On first boot, if the RTC has lost power, set the time manually by uncommenting and
editing this line in `setup()`:

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
