> **Note:** These programming instructions apply to revision 1 of the PCB, which has a
> hardware bug causing USB to be non-functional. On a corrected revision, the bootloader
> still needs to be burned once via ISP using the same process described below. After
> that, firmware can be uploaded directly over USB using `Sketch > Upload` with the
> Adafruit Feather 32U4 board selected, without needing the ISP setup again.

## Programming

Since USB is non-functional, the chip must be programmed via the onboard SPI header using
an Arduino UNO as an ISP programmer.

### Requirements
- Arduino UNO
- Jumper wires
- 10µF capacitor
- Resistors (1K) for voltage regulation (the UNO is 5V, the PCB runs at 3.3V)

### Wiring (UNO -> PCB SPI header)

| UNO Pin | PCB SPI Header |
|---------|---------------|
| Pin 13  | SCK           |
| Pin 12  | MISO          |
| Pin 11  | MOSI          |
| Pin 10  | RESET         |
| --      | VCC           |  (do not connect — PCB is powered separately)
| GND     | GND           |

Place a 10µF capacitor between RESET and GND on the UNO (positive to RESET).

**Important:** Add a 1K resistor in series on MOSI, SCK and RESET lines between the UNO
and the PCB. This is necessary because the UNO outputs 5V logic and the PCB runs at 3.3V.
MISO needs no resistor.

### Burning the Bootloader

1. Upload `File > Examples > 11.ArduinoISP > ArduinoISP` to the UNO
2. In Arduino IDE, install Adafruit AVR Boards via Boards Manager
3. Set `Tools > Board` to **Adafruit Feather 32U4** (8MHz, 3.3V)
4. Set `Tools > Programmer` to **Arduino as ISP**
5. Click `Tools > Burn Bootloader`

### Uploading Firmware

After the bootloader is burned, use `Sketch > Upload Using Programmer` for all future
uploads on this revision. On a corrected PCB revision with working USB, use the standard
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
