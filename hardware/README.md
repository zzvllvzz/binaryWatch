# Hardware

Design and manufacturing files for the binary LED wristwatch PCB.

## Files

| File                           | Description                                                       |
|--------------------------------|-------------------------------------------------------------------|
| `ProDoc_Schematic1_*.epro`     | Schematic source file (EasyEDA Pro)                               |
| `binaryWatch.pdf`              | Schematic (corrected revision, PDF export)                        |
| `Gerber_PCB1_*.zip`            | Gerber files for PCB fabrication                                  |
| `BOM_Board1_PCB1_*.xlsx`       | Bill of materials                                                 |
| `PickAndPlace_PCB1_*.xlsx`     | Component placement coordinates for PCBA                          |
| `binaryWatch.jpg`              | Photo of the assembled board                                      |

## Manufacturing

The board was designed in **EasyEDA** and manufactured as a PCBA by **JLCPCB**.
The Gerber, BOM, and pick-and-place files included here are the exact files
used for the assembly order and can be re-submitted as-is.

**Board specs:** 4-layer, 42 × 42 mm, 1.6 mm thickness.

## Revision Notes

The schematic in this directory (both the `.epro` source and the PDF export)
is the **corrected revision** with the USB D+/D- swap fixed. For background
on the original issue, see the
[Known Hardware Issues](../README.md#known-hardware-issues) section in the
root README.

It is recommended to order the board **without header H1 populated** — the
header overhangs the bottom watch-strap hole and is awkward to desolder
after assembly. The bootloader can be flashed directly through the H1 pads.
