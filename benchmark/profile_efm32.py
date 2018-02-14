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
    "examples/javascript",
    "examples/saul",
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
    "tests/sched_testing",
    "tests/shell",
    "tests/xtimer_periodic_wakeup"
]

# Compile settings (e.g. debug settings).
SETTINGS = [
    {"CFLAGS": "-DNO_DEBUG_EFM"},
    {"CFLAGS": "-DNO_DEBUG_EFM -DLOW_POWER_ENABLED=0"},
    {"CFLAGS": "-DNO_DEBUG_EFM -DLOW_POWER_ENABLED=0", "DISABLE_MODULE": "silabs_aem"},  # noqa
    {"LTO": "1", "CFLAGS": "-DNO_DEBUG_EFM"},
    {"LTO": "1", "CFLAGS": "-DNO_DEBUG_EFM -DLOW_POWER_ENABLED=0"},
    {"LTO": "1", "CFLAGS": "-DNO_DEBUG_EFM -DLOW_POWER_ENABLED=0", "DISABLE_MODULE": "silabs_aem"},  # noqa

    {"CFLAGS": "-DDEBUG_EFM"},
    {"CFLAGS": "-DDEBUG_EFM -DLOW_POWER_ENABLED=0"},
    {"CFLAGS": "-DDEBUG_EFM -DLOW_POWER_ENABLED=0", "DISABLE_MODULE": "silabs_aem"},  # noqa
    {"LTO": "1", "CFLAGS": "-DDEBUG_EFM"},
    {"LTO": "1", "CFLAGS": "-DDEBUG_EFM -DLOW_POWER_ENABLED=0"},
    {"LTO": "1", "CFLAGS": "-DDEBUG_EFM -DLOW_POWER_ENABLED=0", "DISABLE_MODULE": "silabs_aem"},  # noqa
]

# Compile set optimizers (not all boards support all settings).
OPTIMIZERS = []
