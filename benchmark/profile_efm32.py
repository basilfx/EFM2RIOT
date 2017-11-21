# Boards to test.
BOARDS = [
    "brd4162a",
    "stk3200",
    "slstk3401a",
    "slstk3402a",
    "slstk3701a",
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
OPTIMIZERS = []
