# Boards to test.
BOARDS = [
    "stk3200",
    "slstk3401a",
    "stk3600",
    "stk3700",
    "stk3800",
    "slwstk6220a",
    "sltb001a",
]

# Applications to compile (relative to RIOT-OS root).
APPLICATIONS = [
    "examples/default",
]

# Compile settings (e.g. debug settings).
SETTINGS = [
    {},
    {"CFLAGS": "-DLOW_POWER_ENABLED=0"},
    {"CFLAGS": "-DLOW_POWER_ENABLED=0 -DAEM_ENABLED=0"},

    {"CFLAGS": "-DDEBUG_EFM"},
    {"CFLAGS": "-DDEBUG_EFM -DLOW_POWER_ENABLED=0"},
    {"CFLAGS": "-DDEBUG_EFM -DLOW_POWER_ENABLED=0 -DAEM_ENABLED=0"},
]

# Compile set optimizers (not all boards support all settings).
OPTIMIZERS = []
