def if_not_efm32(board):
    return board not in [
        "stk3200",
        "slstk3401a",
        "slstk3402a",
        "stk3600",
        "stk3700",
        "stk3800",
        "slwstk6220a",
        "sltb001a",
    ]

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
    "slstk3402a",
    "stk3600",
    "stk3700",
    "stk3800",
    "slwstk6220a",
    "sltb001a",
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
    "tests/periph_hwrng",
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
    {},
    {"CFLAGS": "-DLOW_POWER_ENABLED=0"},
    {"CFLAGS": "-DLOW_POWER_ENABLED=0 -DAEM_ENABLED=0"},
    {"LTO": "1"},
    {"LTO": "1", "CFLAGS": "-DLOW_POWER_ENABLED=0"},
    {"LTO": "1", "CFLAGS": "-DLOW_POWER_ENABLED=0 -DAEM_ENABLED=0"},

    {"CFLAGS": "-DDEBUG_EFM"},
    {"CFLAGS": "-DDEBUG_EFM -DLOW_POWER_ENABLED=0"},
    {"CFLAGS": "-DDEBUG_EFM -DLOW_POWER_ENABLED=0 -DAEM_ENABLED=0"},
    {"LTO": "1", "CFLAGS": "-DDEBUG_EFM"},
    {"LTO": "1", "CFLAGS": "-DDEBUG_EFM -DLOW_POWER_ENABLED=0"},
    {"LTO": "1", "CFLAGS": "-DDEBUG_EFM -DLOW_POWER_ENABLED=0 -DAEM_ENABLED=0"},  # noqa
]

# Compile set optimizers (not all boards support all settings).
OPTIMIZERS = [
    (if_not_efm32, SETTINGS[1], SETTINGS[0]),
    (if_not_efm32, SETTINGS[2], SETTINGS[0]),
    (if_not_efm32, SETTINGS[4], SETTINGS[3]),
    (if_not_efm32, SETTINGS[5], SETTINGS[3]),
    (if_not_efm32, SETTINGS[6], SETTINGS[0]),
    (if_not_efm32, SETTINGS[7], SETTINGS[0]),
    (if_not_efm32, SETTINGS[8], SETTINGS[0]),
    (if_not_efm32, SETTINGS[9], SETTINGS[3]),
    (if_not_efm32, SETTINGS[10], SETTINGS[3]),
    (if_not_efm32, SETTINGS[11], SETTINGS[3]),
]
