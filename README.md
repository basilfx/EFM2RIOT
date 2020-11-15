# EFM2RIOT
Generator for initializing the EFM32 port for use with RIOT-OS.

## Introduction
EFM32 is a 32-bit micro controller (MCU) family manufactured by Silicon Labs.
These MCUs are very energy efficient. [RIOT-OS](http://www.riot-os.org/) is an
operating system for Internet of Things applications. It offers a real-time
kernel, peripheral abstraction, drivers and network stack.

This generator prepares the required files for using EFM32 with RIOT-OS, which
includes:

* Initializing MCU targets.
* Initializing board targets.

## Usage

### As an end-user
When you have cloned this repository, a ready-to-use version is available in
the `dist/` folder. Copy the desired CPU and board folder from `cpu/` and
`boards/` to your RIOT-OS project.

### As a developer
You will need Python 3.7 and the 32-bit MCU SDK 5.9.7.0 (can be installed via
[Simplicity Studio v4](https://www.silabs.com/products/development-tools/software/simplicity-studio)).

* The `efm2riot/configuration.py` defines all the jobs and boards.
* The `efm2riot/templates/` folder contains all the files that need to be
  pre-processed.
* The `efm2riot/static/` folder contains files that will be copied.

To (re)generate all files, run:

```
python3 EFM2RIOT.py --sdk /path/to/sdk/platform --svds /path/to/svds --dist dist/
```

To enable some features that are not yet part of RIOT-OS, pass `--development`.

You can download SVD files from the [KEIL](keil.com/dd2/) website. Categorize
them in a folder per family.

See [CONTRIBUTING.md](CONTRIBUTING.md) for more information on developing.

## Supported families
Most of the 32-bit families that are supported by EMLIB are supported by
EFM2RIOT:

* EFM32 Gecko
* EFM32 Giant Gecko
* EFM32 Happy Gecko
* EFM32 Jade Gecko
* EFM32 Leopard Gecko
* EFM32 Pearl Gecko
* EFM32 Tiny Gecko
* EFM32 Wonder Gecko
* EFM32 Zero Gecko
* EFR32 Blue Gecko
* EFR32 Flex Gecko
* EFR32 Mighty Gecko
* EFR32 Zen Gecko
* EZR32 Happy Gecko
* EZR32 Leopard Gecko
* EZR32 Wonder Gecko

**Note:** not all MCUs may be supported or have sufficient resources for use
with RIOT-OS, for instance, low-memory MCUs.

## Supported boards
Currently, the following boards (development kits) are supported:

* [SLSTK3301A](dist/doc/slstk3301a) &mdash; EFM32 Tiny Gecko 11B
* [SLSTK3400A](dist/doc/slstk3400a) &mdash; EFM32 Happy Gecko
* [SLSTK3401A](dist/doc/slstk3401a) &mdash; EFM32 Pearl Gecko 1B
* [SLSTK3402A](dist/doc/slstk3402a) &mdash; EFM32 Pearl Gecko 12B
* [SLSTK3701A](dist/doc/slstk3701a) &mdash; EFM32 Giant Gecko 11B (untested)
* [SLTB001A](dist/doc/sltb001a) &mdash; EFR32 Mighty Gecko 1P
* [SLTB004A](dist/doc/sltb004a) &mdash; EFR32 Mighty Gecko 12P (untested)
* [SLTB009A](dist/doc/sltb009a) &mdash; EFR32 Giant Gecko 12B (untested)
* [SLTB010A](dist/doc/sltb010a) &mdash; EFR32 Blue Gecko 22
* [SLWSTK6000B](dist/doc/slwstk6000b) &mdash; EFR32 Mighty Gecko (untested)
* [SLWSTK6220A](dist/doc/slwstk6220a) &mdash; EZR32 Wonder Gecko (untested)
* [STK3200](dist/doc/stk3200) &mdash; EFM32 Zero Gecko
* [STK3600](dist/doc/stk3600) &mdash; EFM32 Leopard Gecko
* [STK3700](dist/doc/stk3700) &mdash; EFM32 Giant Gecko
* [STK3800](dist/doc/stk3800) &mdash; EFM32 Wonder Gecko

## FAQ

### Why a generator?
It started as an experiment on generating code from configuration, but turned
out to be pretty neat. Apart from that, there are two other reasons:

* This port patches the vendor header files for warning-free usage with
  RIOT-OS. After each update, this process must be repeated. This generator
  automates that process.
* All supported MCUs are extracted from the SDK. Using templates, new MCUs that
  are supported by the SDK will also be supported by this port.

### Why is this not (yet) part of RIOT-OS?
As of November 2017, support for the EFM32 is included in RIOT-OS. This
generator still exists to initialize new targets, albeit it needs to be in
sync with RIOT-OS.

### What is the benefit of using EMLIB?
The use of EMLIB abstracts away all the chip-specific details, while providing
a clean interface to RIOT-OS.

* EMLIB contains powerful assertions to help development.
* (New) families are supported, as long as the EMLIB API stays the same.
* Chip errata (where possible) ensures consistency across revisions of the same
  chip. This is applied during chip setup.
* When developing board-specific applications, chances are you will use EMLIB
  for accessing peripherals.
* It reduces the number of errors and cuts the development time.
* The library developers have good understanding of the hardware.
* No need to 'reinvent the wheel'.

There are doubts on the performance and memory overhead of EMLIB. I have
concluded the following, based on a benchmarking script (included):

* Code size does increase when using EMLIB. The overhead is in the range of 5
  to 10 KiB of flash, depending on the target and peripherals used.
* A large part of the overhead is contained within the clock management unit.
  This is an integral part for proper clock setup and low-power support. It is
  used by all peripherals and has a constant code size.
* Most get/set/read/write/enable/clear methods are implemented as macros or
  inline methods. They are equally efficient as their direct register
  alternative.

Some benchmarks are available at http://basilfx.github.io/EFM2RIOT.

As of October 2017, EMLIB is not included anymore, but available as an
[external](https://github.com/basilfx/RIOT-gecko-sdk) package for RIOT-OS. This
reduces the number of source files included.

## License
See the `LICENSE` file.

Some of the other port files have been copied from other RIOT-OS ports.
