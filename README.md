# EFM2RIOT
Generator for initializing the EFM32 port for use with RIOT-OS.

## Introduction
EFM32 is a 32-bit micro controller (MCU) family manufactured by Silicon Labs. These MCUs are very energy efficient. [RIOT-OS](http://www.riot-os.org/) is an operating system for Internet of Things applications. It offers a real-time kernel, peripheral abstraction, drivers and network stack.

This generator prepares the required files for using EFM32 with RIOT-OS, which includes:

* Copying and patching vendor peripheral library ([emlib](devtools.silabs.com/dl/documentation/doxygen/)).
* Initializing MCU targets.
* Initializing board targets.

## Usage

### As a developer
You will need Python 2.7 and the EFM32 SDK (comes with Simplicity Studio).

* The `efm2riot/configuration.py` defines all the jobs and boards.
* The `efm2riot/templates/` folder contains all the files that need to be pre-processed.
* The `efm2riot/static/` folder contains files that will be copied.

To generate all files, run:

```
python EFM2Riot.py --sdk /path/to/sdk --dist dist/
```

See [CONTRIBUTING.md](CONTRIBUTING.md) for more information on developing.

### As a end-user
When you have cloned this repository, a ready to use version is available in the `dist/` folder.

## Supported families
All of the 32-bit families that are supported by emlib are converted:

* EFM32 Gecko
* EFM32 Giant Gecko
* EFM32 Happy Gecko
* EFM32 Jade Gecko
* EFM32 Leopard Gecko
* EFM32 Pearl Gecko
* EFM32 Tiny Gecko
* EFM32 Wonder Gecko
* EFM32 Zero Gecko
* EZR32 Leopard Gecko
* EZR32 Wonder Gecko

**Note:** not all MCUs may be supported or sufficient for use with RIOT-OS, e.g. due to low ram or memory sizes.

## Supported boards
Currently, the following boards (development kits) are supported:

* [STK3200](dist/doc/SLSTK3200.md) &mdash; EFM32 Zero Gecko
* [SLSTK3401A](dist/doc/SLSTK3401A.md) &mdash; EFM32 Pearl Gecko
* [STK3600](dist/doc/STK3600.md) &mdash; EFM32 Leopard Gecko
* [STK3700](dist/doc/STK3700.md) &mdash; EFM32 Giant Gecko
* [STK3800](dist/doc/STK3800.md) &mdash; EFM32 Wonder Gecko
* [SLWSTK6220A](dist/doc/SLWSTK6220A.md) &mdash; EZR32 Wonder Gecko (untested)

## TODO
* General: find out which MCUs are limited to run RIOT-OS.
* General: add support for DMA in peripheral drivers.
* Timer: add LEUART peripherals.

## FAQ

### Why a generator?
It started as an experiment on generating code from configuration, but turned out to be pretty neat. Apart from that, there are two other reasons:

* This port uses a slightly modified version of emlib. When this library is updated, these changes have to be applied again. This generator automates that process.
* All supported MCUs are extracted from emlib. Using templates, new MCUs that are supported by emlib will also be supported by this port.

### Why is this not (yet) part of RIOT-OS?
The generator is something completely different and has no intention to be part of the RIOT-OS project.

The generated files (the ones in the `dist/` folder) *could* be part of RIOT-OS. However, the developers have a strong preference for a port that is not dependent on any vendor libraries. While I respect this choice, I have the following arguments for using emlib:

* emlib contains powerful assertions to help development.
* (New) families are supported, as long as the emlib API stays the same.
* Chip errata (where possible) ensures consistency across revisions of the same chip. This is applied during chip setup.
* When developing board-specific applications, chances are you will use emlib for accessing peripherals.
* It reduces the number of errors and cuts the development time.
* The library developers have good understanding of the hardware.

There are doubts on the performance and memory overhead of emlib. I have concluded the following, based on a benchmarking script (included):

* Code size does increase when using emlib. The overhead is in the range of 3 to 5 kb of flash, depending on the target and peripherals used.
* A large part of the overhead is contained within the clock management unit. This is an integral part for proper clock setup and low-power support. It is used by all peripherals and has a constant code size.
* Most get/set/read/write/enable/clear methods are implemented as macro's or inline methods. They are equally efficient as their direct register alternative.

Some benchmarks are available at http://basilfx.github.io/EFM2Riot.

## License
See the `LICENSE` file.

The `dist/` folder contains a modified copy of emlib, copyrighted by Silicon Labs. Some of the other port files have been copied from other RIOT-OS ports.
