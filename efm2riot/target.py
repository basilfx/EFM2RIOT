# GPIO ports.
PA = 0
PB = 1
PC = 2
PD = 3
PE = 4
PF = 5
PG = 6
PH = 7
PI = 8
PJ = 9
PK = 10

# Reverse lookup of GPIO port index to GPIO port name.
PORTS = [
    "PA", "PB", "PC", "PD", "PE", "PF", "PG", "PH", "PI", "PJ", "PK"
]


def gpio_pin(port, pin):
    """
    GPIO pin definition.
    """
    return ("pin", (port, pin))


def gpio_undef():
    """
    Undefined GPIO definition.
    """
    return ("pin", None)


def gpio_alias(name):
    """
    GPIO alias definition.
    """
    return ("alias", name)
