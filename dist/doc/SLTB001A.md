# Silicon Labs SLTB001A

## Overview
Silicon Labs Thunderboard Sense is equipped with the EFM32 microcontroller. It is specifically designed for low-power applications, having energy-saving peripherals, different energy modes and short wake-up times.

The starter kit is equipped with an Advanced Energy Monitor. This allows you to actively measure the power consumption of your hardware and code, in real-time.

## Hardware
![SLTB001A Starter Kit](images/sltb001a.png)

### MCU
| MCU             | EFR32MG1P132F256GM48                          |
|-----------------|------------------------------------------|
| Family          | ARM Cortex-M4      |
| Vendor          | Silicon Labs                             |
| Vendor Family   | EFM32 Mighty Gecko Gecko           |
| RAM             | 31KB                   |
| Flash           | 256KB                 |
| EEPROM          | no                                       |
| Frequency       | up to 38 MHz            |
| FPU             | yes                                      |
| DMA             | 12 channel                               |
| Timers          | 2 x 16-bit + 1x 16-bit (low power)       |
| ADCs            | 12-bit ADC                               |
| UARTs           | 3x UART, 2x USART, 1x LEUART             |
| SPIs            | 2x USART                                 |
| I2Cs            | 1x                                       |
| Vcc             | 1.85V - 3.8V                             |
| Datasheet       | [Datasheet](https://www.silabs.com/Support%20Documents/TechnicalDocs/EFR32MG1-DataSheet.pdf)         |
| Manual          | [Manual](http://www.silabs.com/Support%20Documents/TechnicalDocs/EFR32-ReferenceManual.pdf)            |
| Board Manual    | [Board Manual](http://www.silabs.com/Support%20Documents/TechnicalDocs/UG250.pdf)       |
| Board Schematic | [Board Schematic](http://www.silabs.com/Support%20Documents/TechnicalDocs/UG250.pdf) |

### Pinout
This is the pinout of the Expansion Pins on the front side of the board. PIN 1 is the top-left contact, marked on the silkscreen.

|      | PIN | PIN |      |
|------|-----|-----|------|
| GND  | 1   | 2   | VMCU |
| PA2  | 3   | 4   | PC6  |
| PA3  | 5   | 6   | PC7  |
| PF3  | 7   | 8   | PC8  |
| PF4  | 9   | 10  | PC9  |
| PF5  | 11  | 12  | PC0  |
| PF6  | 13  | 14  | PC1  |
| PC11 | 15  | 16  | PC10 |
| RES  | 17  | 18  | 5V   |
| RES  | 19  | 20  | 3V3  |

**Note**: not all starter kits by Silicon Labs share the same pinout!


### Peripheral mapping
| Peripheral | Number  | Hardware        | Pins                            | Comments                                                  |
|------------|---------|-----------------|---------------------------------|-----------------------------------------------------------|



### User interface
| Peripheral | Mapped to | Hardware | Pin  | Comments   |
|------------|-----------|----------|------|------------|


## Implementation Status
| Device                        | ID                             | Supported | Comments                                                       |
|-------------------------------|--------------------------------|-----------|----------------------------------------------------------------|
| MCU                           | EFR32MG1P      | yes       | LPM: EM1 maps to `LPM_IDLE` and EM2 maps to `LPM_SLEEP`        |
| Low-level driver              | ADC                            | yes       |                                                                |
|                               | GPIO                           | yes       | Interrupts are shared across pins (see reference manual)       |
|                               | I2C                            | yes       |                                                                |
|                               | PWM                            | yes       |                                                                |
|                               | RTCC                           | yes       | As RTT or RTC                                                  |
|                               | SPI                            | partially | Only master mode                                               |
|                               | Timer                          | yes       |                                                                |
|                               | UART                           | yes       | USART is shared with SPI. LEUART baud rate limited (see below) |
|                               | USB                            | no        |                                                                |
| Temperature + Humidity sensor | Si7021                         | yes       | Silicon Labs Temperature + Humidity sensor                     |
| Microphone                    |                                | no        |                                                                |
| Light sensor                  | Si1133                         | no        | Silicon Labs UV/Ambient Light sensor                           |
| Hall-effect sensor            | Si7210A                        | no        | Silicon Labs Hall-effect sensor                                |
| IMU sensor                    | ICM-20648                      | no        | InvenSense 6-axis inertial sensor                              |
| Air sensor                    | CCS811                         | no        | Cambridge CMOS Sensors Air Quality/Gas sensor                  |

## Board configuration

### Board controller
The starter kit is equipped with a Board Controller. This controller provides a virtual serial port.

**Note:** the board controller *always* configures the virtual serial port at 115200 baud with 8 bits, no parity and one stop bit. This also means that it expects data from the MCU with the same settings.

### Clock selection
There are several clock sources that are available for the different peripherals. You are advised to read [AN0004](https://www.silabs.com/Support Documents/TechnicalDocs/AN0004.pdf) to get familiar with the different clocks.

| Source  | Internal | Speed                     | Comments                           |
|---------|----------|---------------------------|------------------------------------|
| HFRCO   | Yes      | 14 MHz  | Enabled during startup, changeable |
| HFXO    | No       | 38 MHz   |                                    |
| LFRCO   | Yes      | 32.768 kHz  |                                    |
| LFXO    | No       | 32.768 kHz   |                                    |
| ULFRCO  | No       | 1.000 kHz | Not very reliable as a time source |

The sources can be used to clock following branches:

| Branch | Sources                 | Comments                     |
|--------|-------------------------|------------------------------|
| HF     | HFRCO, HFXO             | Core, peripherals            |
| LFA    | LFRCO, LFXO             | Low-power timers             |
| LFB    | LFRCO, LFXO, CORELEDIV2 | Low-power UART               |
| LFE    | LFRCO, LFXO             | Real-time Clock and Calendar |

CORELEDIV2 is a source that depends on the clock source that powers the core. It is divided by 2 or 4 to not exceed maximum clock frequencies (emlib takes care of this).

The frequencies mentioned in the tables above are specific for this starter kit.

It is important that the clock speeds are known to the code, for proper calculations of speeds and baud rates. If the HFXO or LFXO are different from the speeds above, ensure to pass `EFM32_HFXO_FREQ=freq_in_hz` and `EFM32_LFXO_FREQ=freq_in_hz` to your compiler defines.

You can override the branch's clock source by adding `CLOCK_LFA=source` to your compiler defines, e.g. `CLOCK_LFA=cmuSelect_LFRCO`.

### Low-power peripherals
The low-power UART is capable of providing an UART peripheral using a low-speed clock. When the LFB clock source is the LFRCO or LFXO, it can still be used in EM2. However, this limits the baud rate to 9600 baud. If a higher baud rate is desired, set the clock source to CORELEDIV2.

If you don't need low-power peripheral support, passing `LOW_POWER_ENABLED=0` to the compiler will disable support in the drivers (currently LEUART). This feature costs approximately 600 bytes (default compilation settings, LEUART only).

**Note:** peripheral mappings in your board definitions will not be affected by this setting. Ensure you do not refer to any low-power peripherals.

### RTC or RTT
RIOT-OS has support for *Real-Time Tickers* and *Real-Time Clocks*.

However, this board MCU family has support for a 32-bit *Real-Time Clock and Calendar*, which can be configured in ticker mode **or** calendar mode. Therefore, only one of both peripherals can be supported.

Configured at 1 Hz interval, the RTCC will overflow each 136 years.

Use the ticker mode if your application keeps track of seconds only (e.g. unix timestamp). By default the counter is enabled. You can switch by passing `RTT_AS_RTC=1` to your compiler.

### Hardware crypto
The Gemstone MCUs are equipped with a hardware accelerated crypto peripheral that can speed up AES128, AES256, SHA1, SHA256 and several other cryptographic computations.

A peripheral driver interface for RIOT-OS is proposed, but not yet implemented.

### Usage of emlib
This port makes uses of emlib by Silicon Labs to abstract peripheral registers. While some overhead is to be expected, it ensures proper setup of devices, provides chip errata and simplifies development. The exact overhead depends on the application and peripheral usage, but the largest overhead is expected during peripheral setup. A lot of read/write/get/set methods are implemented as inline methods or macros (which have no overhead).

Another advantage of emlib are the included assertions. These assertions ensure that peripherals are used properly. To enable this, pass `DEBUG_EFM` to your compiler.

### Pin locations
The EFM32 platform supports peripheral to be mapped to different pins (predefined locations). The definitions in `periph_conf.h` mostly consist of a location number and the actual pins. The actual pins are required to configure the pins via GPIO driver, while the location is used to map the peripheral to these pins.

In other words, these definitions must match. Refer to the data sheet for more information.

The EFM32 Gemstone MCUs have extended support for pin mapping. Each pin of a peripheral can be connected separately to one of the predefined pins for that peripheral.

## Flashing the device
To flash, the [J-Link Software](https://www.segger.com/jlink-software.html) from SEGGER is required.

Flashing is supported by RIOT-OS by the command below:

```
make flash
```

To run the GDB debugger, use the command:

```
make debug
```

Or, to connect with your own debugger:

```
make debug-server
```

## Supported Toolchains
For using the Silicon Labs SLTB001A starter kit we strongly recommend the usage of the [GNU Tools for ARM Embedded Processors](https://launchpad.net/gcc-arm-embedded) toolchain.

## License information
* Silicon Labs' emlib: zlib-style license (permits distribution of source).
* Images: taken from starter kit user manual.