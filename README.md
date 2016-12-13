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
  
## Get the example application!

Ontain the mbed-OS library from Windows command prompt

git clone https://github.com/ARMmbed/mbed-os


From the command line of Git Bash, for example:
 
```
hg clone https://developer.mbed.org/teams/Nuvoton/code/NuMaker-mbed-NuBrick-example/
cd NuMaker-mbed-GPIO-button-buzzer-rgbled

```

Make shortcut for mbed-os library within the folder NuMaker-mbed-NuBrick-example
 
### Now compile
 
Invoke `mbed compile` specifying the name of your platform and your favorite toolchain (`GCC_ARM`, `ARM`, `IAR`). For example, for the ARM Compiler 5:
 
```
mbed compile -m NUMAKER_PFM_NUC472 -t ARM
```
 
Your PC may take a few minutes to compile your code. At the end you should get the following result:
 
```
+------------------------+-------+-------+---------+
| Module                 | .text | .data |    .bss |
+------------------------+-------+-------+---------+
| Misc                   | 25085 |   132 | 1053500 |
| drivers                |  1086 |     8 |      56 |
| features/FEATURE_LWIP  |   162 |    16 |      16 |
| hal                    |   358 |     8 |       0 |
| platform               |  1631 |    16 |      92 |
| rtos                   |   130 |     8 |       0 |
| rtos/rtx               |  6702 |   100 |    8396 |
| targets/TARGET_NUVOTON | 10164 |   308 |     104 |
| Subtotals              | 45318 |   596 | 1062164 |
+------------------------+-------+-------+---------+
Allocated Heap: unknown
Allocated Stack: unknown
Total Static RAM memory (data + bss): 1062760 bytes
Total RAM memory (data + bss + heap + stack): 1062760 bytes
Total Flash memory (text + data + misc): 45914 bytes
```
 
### Program your board
 
1. Connect your mbed device to the computer over USB.
1. Copy the binary file to the mbed device .
1. Press the reset button to start the program.
 
Please refer to the documents at the path https://github.com/OpenNuvoton/NuMaker_NuWicam_Samples/
 
## Export the project to Keil MDK and debug your application
 
From the command line, run the following command:
 
```
mbed export -m NUMAKER_PFM_NUC472 -i uvision
```
 
To debug the application:
 
1. Start uVision.
1. Import the uVision project generated earlier.
1. Compile your application and generate an `.axf` file.
1. Make sure uVision is configured to debug over CMSIS-DAP (From the Project menu > Options for Target '...' > Debug tab > Use CMSIS-DAP Debugger).
1. Set breakpoints and start a debug session.
 
![Image of uVision](img/uvision.png)
 
## Troubleshooting
 
1. Make sure `mbed-cli` is working correctly and its version is greater than `0.8.9`
 
 ```
 mbed --version
 ```
 
 If not, you can update it easily:
 
 ```
 pip install mbed-cli --upgrade
 ```
 
2. If using Keil MDK, make sure you have a license installed. [MDK-Lite](http://www.keil.com/arm/mdk.asp) has a 32KB restriction on code size.
 
 