# Boards to test.
BOARDS = [
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
]
