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
    "tests/minimal"
]

# Compile settings (e.g. debug settings).
SETTINGS = [
    [],
    ["CFLAGS_OPT=-Os -DLOW_POWER_ENABLED=0"],
    ["CFLAGS_OPT=-Os -DLOW_POWER_ENABLED=0 -DAEM_ENABLED=0"],
    ["LTO=1"],
    ["LTO=1", "CFLAGS_OPT=-Os -DLOW_POWER_ENABLED=0"],
    ["LTO=1", "CFLAGS_OPT=-Os -DLOW_POWER_ENABLED=0 -DAEM_ENABLED=0"],

    ["CFLAGS_OPT=-Os -DDEBUG_EFM"],
    ["CFLAGS_OPT=-Os -DDEBUG_EFM -DLOW_POWER_ENABLED=0"],
    ["CFLAGS_OPT=-Os -DDEBUG_EFM -DLOW_POWER_ENABLED=0 -DAEM_ENABLED=0"],
    ["LTO=1", "CFLAGS_OPT=-Os -DDEBUG_EFM"],
    ["LTO=1", "CFLAGS_OPT=-Os -DDEBUG_EFM -DLOW_POWER_ENABLED=0"],
    ["LTO=1", "CFLAGS_OPT=-Os -DDEBUG_EFM -DLOW_POWER_ENABLED=0 -DAEM_ENABLED=0"],  # noqa
]
