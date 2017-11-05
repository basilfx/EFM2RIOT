# Silicon Labs {{ board_display_name }}

## Overview
Silicon Labs {{ marketing_display_name }} is equipped with the EFM32 microcontroller. It is specifically designed for low-power applications, having energy-saving peripherals, different energy modes and short wake-up times.

The starter kit is equipped with an Advanced Energy Monitor. This allows you to actively measure the power consumption of your hardware and code, in real-time.

## Hardware
![{{ board_display_name }} Starter Kit](images/{{board}}.png)

### MCU
| MCU             | {{ cpu|upper|align(52)                            }} |
|-----------------|------------------------------------------------------|
| Family          | {{ ("ARM Cortex-" ~ architecture|upper)|align(52) }} |
| Vendor          | Silicon Labs                                         |
| Vendor Family   | {{ family_display_name_full|align(52)             }} |
| RAM             | {{ (ram_size|to_kb ~ "KB")|align(52)              }} |
| Flash           | {{ (flash_size|to_kb ~ "KB")|align(52)            }} |
| EEPROM          | no                                                   |
| Frequency       | {{ ("up to " ~ freq.hfxo|to_freq)|align(52)       }} |
| FPU             | {{ ("yes" if fpu else "no")|align(52)             }} |
| MPU             | {{ ("yes" if mpu else "no")|align(52)             }} |
{% strip 2 %}
    {% if board in ["slstk3401a"] %}
        | DMA             | 8 channels                                           |
        | Timers          | 2 x 16-bit + 1x 16-bit (low power)                   |
        | ADCs            | 12-bit ADC                                           |
        | UARTs           | 2x USART, 1x LEUART                                  |
        | SPIs            | 2x USART                                             |
        | I2Cs            | 1x                                                   |
        | Vcc             | 1.85V - 3.8V                                         |
    {% elif board in ["slstk3402a"] %}
        | DMA             | 8 channels                                           |
        | Timers          | 2 x 16-bit + 1x 16-bit (low power)                   |
        | ADCs            | 12-bit ADC                                           |
        | UARTs           | 2x USART, 1x LEUART                                  |
        | SPIs            | 2x USART                                             |
        | I2Cs            | 1x                                                   |
        | Vcc             | 1.85V - 3.8V                                         |
    {% elif board in ["sltb001a"] %}
        | DMA             | 12 channels                                          |
        | Timers          | 2 x 16-bit + 1x 16-bit (low power)                   |
        | ADCs            | 12-bit ADC                                           |
        | UARTs           | 3x UART, 2x USART, 1x LEUART                         |
        | SPIs            | 2x USART                                             |
        | I2Cs            | 1x                                                   |
        | Vcc             | 1.85V - 3.8V                                         |
    {% elif board in ["slwstk6220a"] %}
        | DMA             | 12 channels                                          |
        | Timers          | 3 x 16-bit + 1x 16-bit (low power)                   |
        | ADCs, DACs      | 12-bit ADC, 12-bit DAC                               |
        | UARTs           | 2x UART, 3x USART, 2x LEUART                         |
        | SPIs            | 3x USART                                             |
        | I2Cs            | 2x                                                   |
        | Vcc             | 1.98V - 3.8V                                         |
    {% elif board in ["stk3200"] %}
        | DMA             | 12 channels                                          |
        | Timers          | 2 x 16-bit + 1x 16-bit (low power)                   |
        | ADCs            | 12-bit ADC                                           |
        | UARTs           | 2x USART, 1x LEUART                                  |
        | SPIs            | 2x USART                                             |
        | I2Cs            | 1x                                                   |
        | Vcc             | 1.98V - 3.8V                                         |
    {% elif board in ["stk3600"] %}
        | DMA             | 12 channels                                          |
        | Timers          | 3 x 16-bit + 1x 16-bit (low power)                   |
        | ADCs, DACs      | 12-bit ADC, 12-bit DAC                               |
        | UARTs           | 2x UART, 3x USART, 2x LEUART                         |
        | SPIs            | 3x USART                                             |
        | I2Cs            | 2x                                                   |
        | Vcc             | 1.98V - 3.8V                                         |
    {% elif board in ["stk3700"] %}
        | DMA             | 12 channels                                          |
        | Timers          | 3 x 16-bit + 1x 16-bit (low power)                   |
        | ADCs, DACs      | 12-bit ADC, 12-bit DAC                               |
        | UARTs           | 2x UART, 3x USART, 2x LEUART                         |
        | SPIs            | 3x USART                                             |
        | I2Cs            | 2x                                                   |
        | Vcc             | 1.98V - 3.8V                                         |
    {% elif board in ["stk3800"] %}
        | DMA             | 12 channels                                          |
        | Timers          | 3 x 16-bit + 1x 16-bit (low power)                   |
        | ADCs, DACs      | 12-bit ADC, 12-bit DAC                               |
        | UARTs           | 2x UART, 3x USART, 2x LEUART                         |
        | SPIs            | 3x USART                                             |
        | I2Cs            | 2x                                                   |
        | Vcc             | 1.98V - 3.8V                                         |
    {% endif %}
{% endstrip %}
| Datasheet       | {{ ("[Datasheet](" ~ cpu_datasheet ~ ")")|align(120)         }} |
| Manual          | {{ ("[Manual](" ~ family_manual ~ ")")|align(120)            }} |
| Board Manual    | {{ ("[Board Manual](" ~ board_manual ~ ")")|align(120)       }} |
| Board Schematic | {{ ("[Board Schematic](" ~ board_schematic ~ ")")|align(120) }} |

### Pinout
{% strip 2 %}
    {% if board in ["sltb001a"] %}
        This is the pinout of the expansion pins on the front side of the board. PIN 1 is the top-left contact, marked on the silkscreen.
    {% else %}
        This is the pinout of the expansion header on the right side of the board. PIN 1 is the bottom-left contact when the header faces towards you.
    {% endif %}
{% endstrip %}

|      | PIN | PIN |      |
|------|-----|-----|------|
{% strip 2 %}
    {% if board in ["slstk3401a", "slstk3402a"] %}
        | 3V3  | 20  | 19  | RES  |
        | 5V   | 18  | 17  | RES  |
        | PC10 | 16  | 15  | PC11 |
        | PA1  | 14  | 13  | PB13 |
        | PA0  | 12  | 11  | PD11 |
        | PC9  | 10  | 9   | PD10 |
        | PC8  | 8   | 7   | PA4  |
        | PC7  | 6   | 5   | PA3  |
        | PC6  | 4   | 3   | PA2  |
        | VMCU | 2   | 1   | GND  |
    {% elif board in ["sltb001a"] %}
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
    {% elif board in ["slwstk6220a"] %}
        | 3V3  | 20  | 19  | RES  |
        | 5V   | 18  | 17  | RES  |
        | PD6  | 16  | 15  | PD7  |
        | PD5  | 14  | 13  | PF13 |
        | PD4  | 12  | 11  | PB11 |
        | PD3  | 10  | 9   | PE1  |
        | PD2  | 8   | 7   | PE0  |
        | PD1  | 6   | 5   | PC7  |
        | PD0  | 4   | 3   | PC6  |
        | VMCU | 2   | 1   | GND  |
    {% elif board in ["stk3200"] %}
        | 3V3  | 20  | 19  | RES  |
        | 5V   | 18  | 17  | RES  |
        | PE12 | 16  | 15  | PE13 |
        | PD5  | 14  | 13  | PA1  |
        | PD4  | 12  | 11  | PB11 |
        | PC14 | 10  | 9   | PA0  |
        | PC15 | 8   | 7   | PC2  |
        | PD6  | 6   | 5   | PC1  |
        | PD7  | 4   | 3   | PC0  |
        | VMCU | 2   | 1   | GND  |
    {% elif board in ["stk3600", "stk3700", "stk3800"] %}
        | 3V3  | 20  | 19  | RES  |
        | 5V   | 18  | 17  | PC7  |
        | PD6  | 16  | 15  | PC6  |
        | PD5  | 14  | 13  | PB12 |
        | PD4  | 12  | 11  | PB11 |
        | PD3  | 10  | 9   | PC5  |
        | PD2  | 8   | 7   | PC4  |
        | PD1  | 6   | 5   | PC3  |
        | PD0  | 4   | 3   | PC0  |
        | VMCU | 2   | 1   | GND  |
    {% endif %}
{% endstrip %}

**Note**: not all starter kits by Silicon Labs share the same pinout!

{% strip 2 %}
    {% if board not in ["sltb001a"] %}
        **Note:** some pins are connected to the board controller, when enabled!
    {% endif %}
{% endstrip %}

### Peripheral mapping
| Peripheral | Number  | Hardware        | Pins                            | Comments                                                  |
|------------|---------|-----------------|---------------------------------|-----------------------------------------------------------|
{% strip 2 %}
    {% if board in ["stk3600", "stk3700", "stk3800"] %}
        | ADC        | 0       | ADC0            | CHAN0: internal temperature     | Ports are fixed, 14/16-bit resolution not supported       |
        | Crypto     | &mdash; | &mdash;         |                                 | AES128/AES256 only                                        |
        | DAC        | 0       | DAC0            | CHAN0: PB11                     | Ports are fixed, shared with I2C                          |
        | I2C        | 0       | I2C0            | SDA: PD6, SCL: PD7              | `I2C_SPEED_LOW` and `I2C_SPEED_HIGH` clock speed deviate  |
        |            | 1       | I2C1            | SDA: PC4, SCL: PC5              | `I2C_SPEED_LOW` and `I2C_SPEED_HIGH` clock speed deviate  |
        | PWM        | 0       | TIMER3          | CHAN0: PE2                      | Mapped to LED0                                            |
        | RTT        | &mdash; | RTC             |                                 | Either RTT or RTC (see below)                             |
        | RTC        | &mdash; | RTC             |                                 | Either RTC or RTT (see below)                             |
        | SPI        | 0       | USART1          | MOSI: PD0, MISO: PD1, CLK: PD2  |                                                           |
        |            | 1       | USART2          | MOSI: NC, MISO: PC3, CLK: PC4   |                                                           |
        | Timer      | 0       | TIMER0 + TIMER1 |                                 | TIMER0 is used as prescaler (must be adjecent)            |
        | UART       | 0       | UART0           | RX: PE1, TX: PE0                | STDIO output                                              |
        |            | 1       | USART1          | RX: PD1, TX: PD7                |                                                           |
        |            | 2       | LEUART0         | RX: PD5, TX: PD4                | Baud rate limited (see below)                             |
    {% elif board in ["stk3200"] %}
        | ADC        | 0       | ADC0            | CHAN0: internal temperature     | Ports are fixed, 14/16-bit resolution not supported       |
        | Crypto     | &mdash; | &mdash;         |                                 | AES128/AES256 only                                        |
        | I2C        | 0       | I2C0            | SDA: PE12, SCL: PE13            | `I2C_SPEED_LOW` and `I2C_SPEED_HIGH` clock speed deviate  |
        | RTT        | &mdash; | RTC             |                                 | Either RTT or RTC (see below)                             |
        | RTC        | &mdash; | RTC             |                                 | Either RTC or RTT (see below)                             |
        | SPI        | 0       | USART1          | MOSI: PD7, MISO: PD6, CLK: PC15 |                                                           |
        | Timer      | 0       | TIMER0 + TIMER1 |                                 | TIMER0 is used as prescaler (must be adjecent)            |
        | UART       | 0       | LEUART0         | RX: PD5, TX: PD4                | STDIO Output, Baud rate limited (see below)               |
        |            | 1       | USART1          | RX: PD6, TX: PD7                |                                                           |
    {% elif board in ["slstk3401a", "slstk3402a"] %}
        | ADC        | 0       | ADC0            | CHAN0: internal temperature     | Ports are fixed, 14/16-bit resolution not supported       |
        | Crypto     | &mdash; | &mdash;         |                                 | AES128/AES256, SHA1, SHA256                               |
        | I2C        | 0       | I2C0            | SDA: PC10, CLK: PC11            | `I2C_SPEED_LOW` and `I2C_SPEED_HIGH` clock speed deviate  |
        | RTT        | &mdash; | RTCC            |                                 | 1 Hz interval. Either RTT or RTC (see below)              |
        | RTC        | &mdash; | RTCC            |                                 | 1 Hz interval. Either RTC or RTT (see below)              |
        | SPI        | 0       | USART1          | MOSI: PC6, MISO: PC7, CLK: PC8  |                                                           |
        | Timer      | 0       | TIMER0 + TIMER1 |                                 | TIMER0 is used as prescaler (must be adjecent)            |
        | UART       | 0       | USART0          | RX: PA1, TX: PA0                | Default STDIO output                                      |
        |            | 1       | USART1          | RX: PC6, TX: PC7                |                                                           |
        |            | 2       | LEUART0         | RX: PD11, TX: PD10              | Baud rate limited (see below)                             |
    {% elif board in ["slwstk6220a"] %}
        | ADC        | 0       | ADC0            | CHAN0: internal temperature     | Ports are fixed, 14/16-bit resolution not supported       |
        | Crypto     | &mdash; | &mdash;         |                                 | AES128/AES256 only                                        |
        | DAC        | 0       | DAC0            | CHAN0: PB11                     | Ports are fixed, shared with I2C                          |
        | PWM        | 0       | TIMER0          | CHAN0: PF6, CHAN1: PF7          | Mapped to LED0 and LED1                                   |
    {% elif board in ["sltb001a"] %}
        | ADC        | 0       | ADC0            | CHAN0: internal temperature     | Ports are fixed, 14/16-bit resolution not supported       |
        | Crypto     | &mdash; | &mdash;         |                                 | AES128/AES256, SHA1, SHA256                               |
        | I2C        | 0       | I2C0            | SDA: PC10, CLK: PC11            | `I2C_SPEED_LOW` and `I2C_SPEED_HIGH` clock speed deviate  |
        | RTT        | &mdash; | RTCC            |                                 | 1 Hz interval. Either RTT or RTC (see below)              |
        | RTC        | &mdash; | RTCC            |                                 | 1 Hz interval. Either RTC or RTT (see below)              |
        | SPI        | 0       | USART1          | MOSI: PC6, MISO: PC7, CLK: PC8  |                                                           |
        | Timer      | 0       | TIMER0 + TIMER1 |                                 | TIMER0 is used as prescaler (must be adjecent)            |
        | UART       | 0       | USART0          | RX: PA1, TX: PA0                | Default STDIO output                                      |
        |            | 1       | USART1          | RX: PC6, TX: PC7                |                                                           |
        |            | 2       | LEUART0         | RX: PD11, TX: PD10              | Baud rate limited (see below)                             |
    {% endif %}
{% endstrip %}

{% strip 2 %}
    {% if board in ["stk3200", "slstk3401a"] %}
        Board has support for PWM, but there are no timers left to use.
    {% endif %}
{% endstrip %}

### User interface
| Peripheral | Mapped to | Hardware | Pin  | Comments   |
|------------|-----------|----------|------|------------|
{% strip 2 %}
    {% if board in ["stk3600", "stk3700", "stk3800"] %}
        | Button     |           | PB0      | PB9  |            |
        |            |           | PB1      | PB10 |            |
        | LED        | LED_RED   | LED0     | PE2  | Yellow LED |
        |            | LED_GREEN | LED1     | PE3  | Yellow LED |
    {% elif board in ["stk3200"] %}
        | Button     |           | PB0      | PC8  |            |
        |            |           | PB1      | PC9  |            |
        | LED        | LED_RED   | LED0     | PC10 | Yellow LED |
        |            | LED_GREEN | LED1     | PC11 | Yellow LED |
    {% elif board in ["slstk3401a", "slstk3402a"] %}
        | Button     |           | PB0      | PF6  |            |
        |            |           | PB1      | PF7  |            |
        | LED        | LED_RED   | LED0     | PF4  | Yellow LED |
        |            | LED_GREEN | LED1     | PF5  | Yellow LED |
    {% elif board in ["slwstk6220a"] %}
        | Button     |           | PB0      | PE3  |            |
        |            |           | PB1      | PE2  |            |
        | LED        | LED_RED   | LED0     | PF6  | Yellow LED |
        |            | LED_GREEN | LED1     | PF7  | Yellow LED |
    {% elif board in ["sltb001a"] %}
        | Button     |           | PB0      | PD14 |            |
        |            |           | PB1      | PD15 |            |
        | LED        | LED_RED   | LED0     | PD11 | Red LED    |
        |            | LED_GREEN | LED1     | PD12 | Green LED  |
    {% endif %}
{% endstrip %}

## Implementation Status
| Device                        | ID                                  | Supported | Comments                                                       |
|-------------------------------|-------------------------------------|-----------|----------------------------------------------------------------|
| MCU                           | {{ family_display_name|align(35) }} | yes       | LPM: EM1 maps to `LPM_IDLE` and EM2 maps to `LPM_SLEEP`        |
| Low-level driver              | ADC                                 | yes       |                                                                |
{% strip 2 %}
    {% if board in ["stk3600", "stk3700", "stk3800", "slwstk6220a"] %}
        |                               | DAC                                 | yes       |                                                                |
    {% endif %}
{% endstrip %}
|                               | GPIO                                | yes       | Interrupts are shared across pins (see reference manual)       |
|                               | I2C                                 | yes       |                                                                |
|                               | PWM                                 | yes       |                                                                |
{% strip 2 %}
    {% if cpu_platform == 1 %}
        |                               | RTC                                 | yes       | As RTT or RTC                                                  |
    {% else %}
        |                               | RTCC                                | yes       | As RTT or RTC                                                  |
    {% endif %}
{% endstrip %}
|                               | SPI                                 | partially | Only master mode                                               |
|                               | Timer                               | yes       |                                                                |
|                               | UART                                | yes       | USART is shared with SPI. LEUART baud rate limited (see below) |
|                               | USB                                 | no        |                                                                |
{% strip 2 %}
    {% if board in ["slstk3401a", "slstk3402a", "slwstk6220a", "stk3200"] %}
        | LCD driver                    | LS013B7DH03                         | yes       | Sharp Low Power Memory LCD                                     |
    {% endif %}
    {% if board in ["slstk3401a", "slstk3402a", "sltb001a", "slwstk6220a"] %}
        | Temperature + humidity sensor | Si7021                              | yes       | Silicon Labs Temperature + Humidity sensor                     |
    {% endif %}
    {% if board in ["sltb001a"] %}
        | Microphone                    |                                     | no        |                                                                |
        | Pressure + temperature sensor | BMP280                              | yes       | Bosch pressure and temperature sensor                          |
        | Light sensor                  | Si1133                              | no        | Silicon Labs UV/Ambient Light sensor                           |
        | Hall-effect sensor            | Si7210A                             | no        | Silicon Labs Hall-effect sensor (Rev. A02 boards only)         |
        | IMU sensor                    | ICM-20648                           | no        | InvenSense 6-axis inertial sensor                              |
        | Air sensor                    | CCS811                              | no        | Cambridge CMOS Sensors Air Quality/Gas sensor                  |
    {% endif %}
{% endstrip %}

## Board configuration

### Board controller
{% strip 2 %}
    {% if board not in ["sltb001a"] %}
        The starter kit is equipped with a Board Controller. This controller provides a virtual serial port. The board controller is enabled via a GPIO pin.

        By default, this pin is enabled. It can be disable by passing `BC_ENABLED=0` to the compiler.

        **Note:** to use the virtual serial port, ensure you have the latest board controller firmware installed.
    {% else %}
        The starter kit is equipped with a Board Controller. This controller provides a virtual serial port.
    {% endif %}
{% endstrip %}

**Note:** the board controller *always* configures the virtual serial port at 115200 baud with 8 bits, no parity and one stop bit. This also means that it expects data from the MCU with the same settings.

{% strip 2, ">" %}
    {% if board in ["slstk3401a", "slstk3402a", "slwstk6220a", "stk3200"] %}
        The low power LCD is also used by the board controller when the `DISP_SELECTED` pin is low. This pin is not initialized by the board, so you have to ensure this pin is initialized by your application if you want to control the low power LCD.
    {% endif %}
{% endstrip %}

{% strip 2, ">" %}
    {% if board in ["slstk3401a", "slstk3402a", "slwstk6220a", "stk3200", "stk3600", "stk3700", "stk3800"] %}
        ### Advanced Energy Monitor
        This development kit has an Advanced Energy Monitor. It can be connected to the Simplicity Studio development software.

        {% strip 2 %}
            {% if board in ["slstk3401a", "slstk3402a", "slwstk6220a", "stk3600", "stk3700", "stk3800"] %}
                This development kit can measure energy consumption and correlate this with the code. It allows you to measure energy consumption on code-level.

                The board controller is responsible for measuring energy consumption. For real-time code correlation, the CoreDebug peripheral will be configured to output MCU register data and interrupt data via the SWO port.

                By default, this feature is enabled. It can be disabled by passing `AEM_ENABLED=0` to the compiler. This feature costs approximately 300 bytes (default compilation settings).

                Note that Simplicity Studio requires debug symbols to correlate code. RIOT-OS defaults to GDB debug symbols, but Simplicity Studio requires DWARF-2 debug symbols.
            {% else %}
                This development kit can measure energy consumption, but it does not support real-time code correlation.
            {% endif %}
        {% endstrip %}
    {% endif %}
{% endstrip %}

### Clock selection
There are several clock sources that are available for the different peripherals. You are advised to read [AN0004](https://www.silabs.com/Support%20Documents/TechnicalDocs/AN0004.pdf) to get familiar with the different clocks.

| Source  | Internal | Speed                               | Comments                           |
|---------|----------|-------------------------------------|------------------------------------|
| HFRCO   | Yes      | {{ freq.hfrco|to_freq|align(35)  }} | Enabled during startup, changeable |
| HFXO    | No       | {{ freq.hfxo|to_freq|align(35)   }} |                                    |
| LFRCO   | Yes      | {{ freq.lfrco|to_freq|align(35)  }} |                                    |
| LFXO    | No       | {{ freq.lfxo|to_freq|align(35)   }} |                                    |
| ULFRCO  | No       | {{ freq.ulfrco|to_freq|align(35) }} | Not very reliable as a time source |

The sources can be used to clock following branches:

| Branch | Sources                 | Comments                     |
|--------|-------------------------|------------------------------|
| HF     | HFRCO, HFXO             | Core, peripherals            |
| LFA    | LFRCO, LFXO             | Low-power timers             |
| LFB    | LFRCO, LFXO, CORELEDIV2 | Low-power UART               |
{% strip 2 %}
    {% if cpu_platform == 2 %}
        | LFE    | LFRCO, LFXO             | Real-time Clock and Calendar |
    {% endif %}
{% endstrip %}

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

{% strip 2 %}
    {% if cpu_platform == 1 %}
        However, this board MCU family has support for a 24-bit *Real-Time Counter* only, which is a ticker only. A compatibility layer for ticker-to-calendar is available, but this includes extra code size to convert from timestamps to time structures and visa versa.

        Configured at 1 Hz interval, the RTC will overflow each 194 days. When using the ticker-to-calendar mode, this interval is extended artificially.
    {% else %}
        However, this board MCU family has support for a 32-bit *Real-Time Clock and Calendar*, which can be configured in ticker mode **or** calendar mode. Therefore, only one of both peripherals can be enabled at the same time.

        Configured at 1 Hz interval, the RTCC will overflow each 136 years.
    {% endif %}
{% endstrip %}

### Hardware crypto
{% strip 2 %}
    {% if cpu_platform == 1 %}
        The MCU has support for hardware accelerated AES128 and AES256.
    {% else %}
        The Gemstone MCUs are equipped with a hardware accelerated crypto peripheral that can speed up AES128, AES256, SHA1, SHA256 and several other cryptographic computations.
    {% endif %}
{% endstrip %}

A peripheral driver interface for RIOT-OS is proposed, but not yet implemented.

### Usage of emlib
This port makes uses of emlib by Silicon Labs to abstract peripheral registers. While some overhead is to be expected, it ensures proper setup of devices, provides chip errata and simplifies development. The exact overhead depends on the application and peripheral usage, but the largest overhead is expected during peripheral setup. A lot of read/write/get/set methods are implemented as inline methods or macros (which have no overhead).

Another advantage of emlib are the included assertions. These assertions ensure that peripherals are used properly. To enable this, pass `DEBUG_EFM` to your compiler.

### Pin locations
The EFM32 platform supports peripheral to be mapped to different pins (predefined locations). The definitions in `periph_conf.h` mostly consist of a location number and the actual pins. The actual pins are required to configure the pins via GPIO driver, while the location is used to map the peripheral to these pins.

In other words, these definitions must match. Refer to the data sheet for more information.

{% strip 2, ">" %}
    {% if cpu_platform == 2 %}
        The EFM32 Gemstone MCUs have extended support for pin mapping. Each pin of a peripheral can be connected separately to one of the predefined pins for that peripheral.
    {% endif %}
{% endstrip %}

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
For using the Silicon Labs {{ board_display_name }} starter kit we strongly recommend the usage of the [GNU Tools for ARM Embedded Processors](https://developer.arm.com/open-source/gnu-toolchain/gnu-rm) toolchain.

## License information
* Silicon Labs' emlib: zlib-style license (permits distribution of source).
* Images: taken from starter kit user manual.
