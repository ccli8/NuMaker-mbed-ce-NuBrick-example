# Getting started with NuMaker Brick platform on mbed

This is an example to communicate with NuMaker Brick slave modules with [NuMaker mbed NuBrick](https://github.com/opennuvoton/NuMaker-mbed-NuBrick) library.

## What it does?

This example enumerates supported NuMaker Brick slave modules connected on the I2C bus.
- Buzzer
- LED
- AHRS
- Sonar
- Temperature & Humidity
- Gas
- IR
- Keys

## Required hardware

- mbed enabled boards ([NuMaker-PFM-NUC472](https://developer.mbed.org/platforms/Nuvoton-NUC472/) or [NuMaker-PFM-M453]())
- 1 mini-USB cable
- [NuMaker Brick slave modules](http://www.nuvoton.com/hq/support/tool-and-software/development-tool-hardware/numaker-brick/?__locale=en)
- 1 I2C cable or I2C adaptor board

## Known issues
- A NuMaker Brick slave module uses divider resistance to identify its own ID. If supplied voltage diverges from 5V too far away, detected ID would be incorrect.
  The issue gets worse if multiple modules are stacked together.