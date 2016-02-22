# Boards to test.
BOARDS = [
    "iotlab-m3",
    "frdm-k64f",
    "mbed_lpc1768",
    "weio",
    "stm32f0discovery",
    "stm32f3discovery",
    "stm32f4discovery",
    "stk3200",
    "slstk3401a",
    "stk3600",
    "stk3700",
    "stk3800",
    "slwstk6220a",
]

# Applications to compile (relative to RIOT-OS root).
APPLICATIONS = [
    "examples/default",
    "examples/hello-world",
    "tests/minimal",
    "tests/periph_adc",
    "tests/periph_cpuid",
    "tests/periph_dac",
    "tests/periph_gpio",
    "tests/periph_i2c",
    "tests/periph_pwm",
    "tests/periph_rtc",
    "tests/periph_rtt",
    "tests/periph_spi",
    "tests/periph_timer",
    "tests/periph_uart",
    "tests/shell"
]

# Compile settings (e.g. debug settings).
SETTINGS = [
    [],
    ["CFLAGS_OPT=-Os -DLOW_POWER_ENABLED=0"],
    ["CFLAGS_OPT=-Os -DLOW_POWER_ENABLED=0 -DAEM_ENABLED=0"],
    ["LTO=yes"],
    ["LTO=yes", "CFLAGS_OPT=-Os -DLOW_POWER_ENABLED=0"],
    ["LTO=yes", "CFLAGS_OPT=-Os -DLOW_POWER_ENABLED=0 -DAEM_ENABLED=0"],

    ["CFLAGS_OPT=-Os -DDEBUG_EFM"],
    ["CFLAGS_OPT=-Os -DDEBUG_EFM -DLOW_POWER_ENABLED=0"],
    ["CFLAGS_OPT=-Os -DDEBUG_EFM -DLOW_POWER_ENABLED=0 -DAEM_ENABLED=0"],
    ["LTO=yes", "CFLAGS_OPT=-Os -DDEBUG_EFM"],
    ["LTO=yes", "CFLAGS_OPT=-Os -DDEBUG_EFM -DLOW_POWER_ENABLED=0"],
    ["LTO=yes", "CFLAGS_OPT=-Os -DDEBUG_EFM -DLOW_POWER_ENABLED=0 -DAEM_ENABLED=0"],  # noqa
]
