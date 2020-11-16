from efm2riot import patches, filters

from efm2riot.target import *  # noqa


# Static copy actions (source, destination).
STATICS = [
    {
        "type": "directory",
        "source": "{{ root }}/static/examples",
        "target": "examples"
    },
    {
        "type": "directory",
        "source": "{{ root }}/static/boards/slwstk6000b",
        "target": "boards/slwstk6000b"
    }
]

# Template files.
TEMPLATES = [
    {
        "type": "file",
        "when": "per_family",
        "source": "{{ sdk }}/Device/SiliconLabs/{{ family|upper }}/Source/system_{{ family }}.c",  # noqa
        "target": "cpu/efm32/families/{{ family }}/system.c"
    },
    {
        "type": "file",
        "when": "per_cpu",
        "source": "{{ root }}/templates/cpu/efm32/families/family/dist/renode/cpu.repl",  # noqa
        "target": "cpu/efm32/families/{{ family }}/dist/renode/{{ cpu }}.repl",
        "filters": {
            "{{ root }}/templates/cpu/efm32/families/family/dist/renode/cpu.repl": filters.only_for_development(),  # noqa
        }
    },
    {
        "type": "file",
        "when": "per_family",
        "source": "{{ root }}/templates/cpu/efm32/families/family/efm32-info.mk",  # noqa
        "target": "cpu/efm32/families/{{ family }}/efm32-info.mk"
    },
    {
        "type": "file",
        "when": "per_family",
        "source": "{{ root }}/templates/cpu/efm32/families/family/Kconfig",
        "target": "cpu/efm32/families/{{ family }}/Kconfig"
    },
    {
        "type": "file",
        "when": "per_family",
        "source": "{{ root }}/templates/cpu/efm32/families/family/Makefile",
        "target": "cpu/efm32/families/{{ family }}/Makefile"
    },
    {
        "type": "file",
        "when": "per_family",
        "source": "{{ root }}/templates/cpu/efm32/families/family/Makefile.include", # noqa
        "target": "cpu/efm32/families/{{ family }}/Makefile.include"
    },
    {
        "type": "file",
        "when": "per_family",
        "source": "{{ root }}/templates/cpu/efm32/families/family/vectors.c",
        "target": "cpu/efm32/families/{{ family }}/vectors.c"
    },
    {
        "type": "file",
        "when": "per_board",
        "source": "{{ root }}/templates/boards/board/dist/renode/board.repl",
        "target": "boards/{{ board }}/dist/renode/{{ board }}.repl",
        "filters": {
            "{{ root }}/templates/boards/board/dist/renode/board.repl": filters.only_for_development(),  # noqa
        }
    },
    {
        "type": "file",
        "when": "per_board",
        "source": "{{ root }}/templates/boards/board/dist/renode/board.resc",
        "target": "boards/{{ board }}/dist/renode/board.resc",
        "filters": {
            "{{ root }}/templates/boards/board/dist/renode/board.resc": filters.only_for_development(),  # noqa
        }
    },
    {
        "type": "glob",
        "when": "per_board",
        "source": "{{ root }}/templates/boards/board/include/*",
        "target": "boards/{{ board }}/include",
    },
    {
        "type": "glob",
        "when": "per_board",
        "source": "{{ root }}/templates/boards/board/*",
        "target": "boards/{{ board }}",
    },
    {
        "type": "glob",
        "when": "once",
        "source": "{{ root }}/templates/contrib/*",
        "target": "contrib/",
    },
    {
        "type": "file",
        "when": "per_family",
        "source": "{{ root }}/templates/contrib/emul8/DeviceInformation.cs",
        "target": "contrib/emul8/{{ family|upper }}DeviceInformation.cs",
        "filters": {
            "{{ root }}/templates/contrib/emul8/DeviceInformation.cs": filters.only_for_development(),  # noqa
        }
    },
]

# Files that need a patch.
PATCHES = [
    {
        "type": "glob",
        "when": "per_family",
        "source": "{{ sdk }}/Device/SiliconLabs/{{ family|upper }}/Include/*.h",  # noqa
        "target": "cpu/efm32/families/{{ family }}/include/vendor",
        "methods": [patches.add_extern_c, patches.fix_arm_math]
    }
]

# Board definitions.
BOARDS = [
    {
        "cpu": "efm32tg11b520f128gm80",
        "cpu_datasheet": "https://www.silabs.com/documents/public/data-sheets/efm32tg11-datasheet.pdf",  # noqa
        "board": "slstk3301a",
        "board_manual": "https://www.silabs.com/documents/public/user-guides/ug303-stk3301.pdf",  # noqa
        "family": "efm32tg11b",
        "family_full_name": "EFM32 Tiny Gecko 11B",
        "family_manual": "https://www.silabs.com/documents/public/reference-manuals/efm32tg11-rm.pdf",  # noqa
        "features": ["bc"],
        "freq": {
            "hfxo": 48000000,
            "hfrco": 19000000,
            "lfxo": 32768,
            "lfrco": 32768,
            "ulfrco": 1000
        },
        "marketing_name": "EFM32 Tiny Gecko 11 Starter Kit",
        "part_number": 1,
        "peripherals": {
            "cmu": {
                "lfa": "cmuSelect_LFXO",
                "lfb": "cmuSelect_LFXO",
                "lfe": "cmuSelect_LFXO"
            },
            "adc": [
                {
                    "peripheral": "ADC0",
                    "channels": [
                        {
                            "dev": 0,
                            "input": "adcPosSelTEMP",
                            "reference": "adcRef1V25",
                            "acq_time": "adcAcqTime8"
                        },
                        {
                            "dev": 0,
                            "input": "adcPosSelAVDD",
                            "reference": "adcRef5V",
                            "acq_time": "adcAcqTime8"
                        }
                    ]
                }
            ],
            "dac": [

            ],
            "i2c": [
                {
                    "peripheral": "I2C0",
                    "sda_pin": gpio_pin(PD, 6),
                    "sda_loc": "I2C_ROUTELOC0_SDALOC_LOC1",
                    "scl_pin": gpio_pin(PD, 7),
                    "scl_loc": "I2C_ROUTELOC0_SCLLOC_LOC1",
                }
            ],
            "pwm": [

            ],
            "spi": [
                {
                    "peripheral": "USART0",
                    "mosi_pin": gpio_pin(PC, 11),
                    "mosi_loc": "USART_ROUTELOC0_RXLOC_LOC2",
                    "miso_pin": gpio_pin(PC, 10),
                    "miso_loc": "USART_ROUTELOC0_TXLOC_LOC2",
                    "clk_pin": gpio_pin(PA, 12),
                    "clk_loc": "USART_ROUTELOC0_CLKLOC_LOC5",
                }
            ],
            "timer": [
                {
                    "prescaler": "TIMER0",
                    "timer": "TIMER1",
                    "channels": "3"
                },
                {
                    "prescaler": "NULL",
                    "timer": "LETIMER0",
                    "channels": "2"
                }
            ],
            "uart": [
                {
                    "peripheral": "USART1",
                    "rx_pin": gpio_pin(PD, 1),
                    "rx_loc": "USART_ROUTELOC0_RXLOC_LOC1",
                    "tx_pin": gpio_pin(PD, 0),
                    "tx_loc": "USART_ROUTELOC0_TXLOC_LOC1"
                }
            ]
        },
        "mappings": {
            "xtimer": {
                "default": {
                    "device": 0,
                    "frequency": 250000,
                    "width": 16
                },
                "letimer": {
                    "device": 1,
                    "frequency": 32768,
                    "width": 16
                }
            },
            "bc": {
                "pin": gpio_pin(PA, 8)
            },
            "buttons": [
                {
                    "name": "PB0_PIN",
                    "pin": gpio_pin(PD, 5)
                },
                {
                    "name": "PB1_PIN",
                    "pin": gpio_pin(PC, 9)
                }
            ],
            "leds": [
                {
                    "name": "LED0_PIN",
                    "pin": gpio_pin(PD, 2)
                },
                {
                    "name": "LED1_PIN",
                    "pin": gpio_pin(PC, 2)
                }
            ],
            "si7021": {
                "i2c": 0,
                "en_pin": gpio_pin(PC, 12)
            }
        }
    },
    {
        "cpu": "efm32hg322f64",
        "cpu_datasheet": "https://www.silabs.com/documents/public/data-sheets/efm32hg-datasheet.pdf",  # noqa
        "board": "slstk3400a",
        "board_manual": "https://www.silabs.com/documents/public/user-guides/ug255-stk3400-user-guide.pdf",  # noqa
        "family": "efm32hg",
        "family_full_name": "EFM32 Happy Gecko",
        "family_manual": "https://www.silabs.com/documents/public/reference-manuals/efm32hg-rm.pdf",  # noqa
        "features": ["bc"],
        "freq": {
            "hfxo": 24000000,
            "hfrco": 14000000,
            "lfxo": 32768,
            "lfrco": 32768,
            "ulfrco": 1000
        },
        "marketing_name": "EFM32 Happy Gecko Starter Kit",
        "part_number": 1,
        "peripherals": {
            "cmu": {
                "lfa": "cmuSelect_LFXO",
                "lfb": "cmuSelect_LFXO"
            },
            "adc": [
                {
                    "peripheral": "ADC0",
                    "channels": [
                        {
                            "dev": 0,
                            "input": "adcSingleInputTemp",
                            "reference": "adcRef1V25",
                            "acq_time": "adcAcqTime8"
                        },
                        {
                            "dev": 0,
                            "input": "adcSingleInputVDDDiv3",
                            "reference": "adcRef1V25",
                            "acq_time": "adcAcqTime8"
                        }
                    ]
                }
            ],
            "dac": [

            ],
            "i2c": [
                {
                    "peripheral": "I2C0",
                    "sda_pin": gpio_pin(PD, 6),
                    "scl_pin": gpio_pin(PD, 7),
                    "loc": "I2C_ROUTE_LOCATION_LOC1",
                }
            ],
            "pwm": [

            ],
            "spi": [
                {
                    "peripheral": "USART0",
                    "mosi_pin": gpio_pin(PE, 10),
                    "miso_pin": gpio_pin(PE, 11),
                    "clk_pin": gpio_pin(PE, 12),
                    "loc": "USART_ROUTE_LOCATION_LOC0",
                }
            ],
            "timer": [
                {
                    "prescaler": "TIMER0",
                    "timer": "TIMER1",
                    "channels": "3"
                }
            ],
            "uart": [
                {
                    "peripheral": "USART1",
                    "rx_pin": gpio_pin(PA, 0),
                    "tx_pin": gpio_pin(PF, 2),
                    "loc": "USART_ROUTE_LOCATION_LOC4"
                },
                {
                    "peripheral": "LEUART0",
                    "rx_pin": gpio_pin(PD, 5),
                    "tx_pin": gpio_pin(PD, 4),
                    "loc": "LEUART_ROUTE_LOCATION_LOC0"
                }
            ]
        },
        "mappings": {
            "xtimer": {
                "default": {
                    "device": 0,
                    "frequency": 250000,
                    "width": 16
                }
            },
            "bc": {
                "pin": gpio_pin(PA, 9)
            },
            "buttons": [
                {
                    "name": "PB0_PIN",
                    "pin": gpio_pin(PC, 9)
                },
                {
                    "name": "PB1_PIN",
                    "pin": gpio_pin(PC, 10)
                }
            ],
            "leds": [
                {
                    "name": "LED0_PIN",
                    "pin": gpio_pin(PF, 4)
                },
                {
                    "name": "LED1_PIN",
                    "pin": gpio_pin(PF, 5)
                }
            ],
            "ls013b7dh03": {
                "spi": 0,
                "com_pin": gpio_pin(PF, 3),
                "cs_pin": gpio_pin(PA, 10),
                "en_pin": gpio_pin(PA, 8)
            },
            "si7021": {
                "i2c": 0,
                "en_pin": gpio_pin(PC, 8)
            }
        }
    },
    {
        "cpu": "efm32pg1b200f256gm48",
        "cpu_datasheet": "https://www.silabs.com/documents/public/data-sheets/efm32pg1-datasheet.pdf",  # noqa
        "board": "slstk3401a",
        "board_manual": "https://www.silabs.com/documents/public/user-guides/ug154-stk3401-user-guide.pdf",  # noqa
        "family": "efm32pg1b",
        "family_full_name": "EFM32 Pearl Gecko 1B",
        "family_manual": "https://www.silabs.com/documents/public/reference-manuals/efm32pg1-rm.pdf",  # noqa
        "features": ["aem", "bc"],
        "freq": {
            "hfxo": 40000000,
            "hfrco": 19000000,
            "lfxo": 32768,
            "lfrco": 32768,
            "ulfrco": 1000
        },
        "marketing_name": "EFM32 Pearl Gecko PG1 Starter Kit",
        "part_number": 1,
        "peripherals": {
            "cmu": {
                "lfa": "cmuSelect_LFXO",
                "lfb": "cmuSelect_LFXO",
                "lfe": "cmuSelect_LFXO"
            },
            "adc": [
                {
                    "peripheral": "ADC0",
                    "channels": [
                        {
                            "dev": 0,
                            "input": "adcPosSelTEMP",
                            "reference": "adcRef1V25",
                            "acq_time": "adcAcqTime8"
                        },
                        {
                            "dev": 0,
                            "input": "adcPosSelAVDD",
                            "reference": "adcRef5V",
                            "acq_time": "adcAcqTime8"
                        }
                    ]
                }
            ],
            "dac": [

            ],
            "i2c": [
                {
                    "peripheral": "I2C0",
                    "sda_pin": gpio_pin(PC, 10),
                    "sda_loc": "I2C_ROUTELOC0_SDALOC_LOC15",
                    "scl_pin": gpio_pin(PC, 11),
                    "scl_loc": "I2C_ROUTELOC0_SCLLOC_LOC15",
                }
            ],
            "pwm": [

            ],
            "spi": [
                {
                    "peripheral": "USART1",
                    "mosi_pin": gpio_pin(PC, 6),
                    "mosi_loc": "USART_ROUTELOC0_RXLOC_LOC11",
                    "miso_pin": gpio_pin(PC, 7),
                    "miso_loc": "USART_ROUTELOC0_TXLOC_LOC11",
                    "clk_pin": gpio_pin(PC, 8),
                    "clk_loc": "USART_ROUTELOC0_CLKLOC_LOC11",
                }
            ],
            "timer": [
                {
                    "prescaler": "TIMER0",
                    "timer": "TIMER1",
                    "channels": "3"
                },
                {
                    "prescaler": "NULL",
                    "timer": "LETIMER0",
                    "channels": "2"
                }
            ],
            "uart": [
                {
                    "peripheral": "USART0",
                    "rx_pin": gpio_pin(PA, 1),
                    "rx_loc": "USART_ROUTELOC0_RXLOC_LOC0",
                    "tx_pin": gpio_pin(PA, 0),
                    "tx_loc": "USART_ROUTELOC0_TXLOC_LOC0"
                },
                {
                    "peripheral": "LEUART0",
                    "rx_pin": gpio_pin(PD, 11),
                    "rx_loc": "LEUART_ROUTELOC0_RXLOC_LOC18",
                    "tx_pin": gpio_pin(PD, 10),
                    "tx_loc": "LEUART_ROUTELOC0_TXLOC_LOC18"
                }
            ]
        },
        "mappings": {
            "xtimer": {
                "default": {
                    "device": 0,
                    "frequency": 250000,
                    "width": 16
                },
                "letimer": {
                    "device": 1,
                    "frequency": 32768,
                    "width": 16
                }
            },
            "bc": {
                "pin": gpio_pin(PA, 5)
            },
            "buttons": [
                {
                    "name": "PB0_PIN",
                    "pin": gpio_pin(PF, 6)
                },
                {
                    "name": "PB1_PIN",
                    "pin": gpio_pin(PF, 7)
                }
            ],
            "leds": [
                {
                    "name": "LED0_PIN",
                    "pin": gpio_pin(PF, 4)
                },
                {
                    "name": "LED1_PIN",
                    "pin": gpio_pin(PF, 5)
                }
            ],
            "ls013b7dh03": {
                "spi": 0,
                "com_pin": gpio_pin(PD, 13),
                "cs_pin": gpio_pin(PD, 14),
                "en_pin": gpio_pin(PD, 15)
            },
            "si7021": {
                "i2c": 0,
                "en_pin": gpio_pin(PD, 9)
            }
        }
    },
    {
        "cpu": "efm32pg12b500f1024gl125",
        "cpu_datasheet": "https://www.silabs.com/documents/public/data-sheets/efm32pg12-datasheet.pdf",  # noqa
        "board": "slstk3402a",
        "board_manual": "https://www.silabs.com/documents/public/user-guides/ug257-stk3402-usersguide.pdf",  # noqa
        "family": "efm32pg12b",
        "family_full_name": "EFM32 Pearl Gecko 12B",
        "family_manual": "https://www.silabs.com/documents/public/reference-manuals/efm32pg12-rm.pdf",  # noqa
        "features": ["aem", "bc"],
        "freq": {
            "hfxo": 40000000,
            "hfrco": 19000000,
            "lfxo": 32768,
            "lfrco": 32768,
            "ulfrco": 1000
        },
        "marketing_name": "EFM32 Pearl Gecko PG12 Starter Kit",
        "part_number": 1,
        "peripherals": {
            "cmu": {
                "lfa": "cmuSelect_LFXO",
                "lfb": "cmuSelect_LFXO",
                "lfe": "cmuSelect_LFXO"
            },
            "adc": [
                {
                    "peripheral": "ADC0",
                    "channels": [
                        {
                            "dev": 0,
                            "input": "adcPosSelTEMP",
                            "reference": "adcRef1V25",
                            "acq_time": "adcAcqTime8"
                        },
                        {
                            "dev": 0,
                            "input": "adcPosSelAVDD",
                            "reference": "adcRef5V",
                            "acq_time": "adcAcqTime8"
                        }
                    ]
                }
            ],
            "dac": [

            ],
            "i2c": [
                {
                    "peripheral": "I2C0",
                    "sda_pin": gpio_pin(PC, 10),
                    "sda_loc": "I2C_ROUTELOC0_SDALOC_LOC15",
                    "scl_pin": gpio_pin(PC, 11),
                    "scl_loc": "I2C_ROUTELOC0_SCLLOC_LOC15",
                }
            ],
            "pwm": [

            ],
            "spi": [
                {
                    "peripheral": "USART1",
                    "mosi_pin": gpio_pin(PC, 6),
                    "mosi_loc": "USART_ROUTELOC0_RXLOC_LOC11",
                    "miso_pin": gpio_pin(PC, 7),
                    "miso_loc": "USART_ROUTELOC0_TXLOC_LOC11",
                    "clk_pin": gpio_pin(PC, 8),
                    "clk_loc": "USART_ROUTELOC0_CLKLOC_LOC11",
                }
            ],
            "timer": [
                {
                    "prescaler": "WTIMER0",
                    "timer": "WTIMER1",
                    "channels": "3"
                },
                {
                    "prescaler": "TIMER0",
                    "timer": "TIMER1",
                    "channels": "3"
                },
                {
                    "prescaler": "NULL",
                    "timer": "LETIMER0",
                    "channels": "2"
                }
            ],
            "uart": [
                {
                    "peripheral": "USART0",
                    "rx_pin": gpio_pin(PA, 1),
                    "rx_loc": "USART_ROUTELOC0_RXLOC_LOC0",
                    "tx_pin": gpio_pin(PA, 0),
                    "tx_loc": "USART_ROUTELOC0_TXLOC_LOC0"
                },
                {
                    "peripheral": "LEUART0",
                    "rx_pin": gpio_pin(PD, 11),
                    "rx_loc": "LEUART_ROUTELOC0_RXLOC_LOC18",
                    "tx_pin": gpio_pin(PD, 10),
                    "tx_loc": "LEUART_ROUTELOC0_TXLOC_LOC18"
                }
            ]
        },
        "mappings": {
            "xtimer": {
                "default": {
                    "device": 0,
                    "frequency": 1000000,
                    "width": 32
                },
                "letimer": {
                    "device": 2,
                    "frequency": 32768,
                    "width": 16
                }
            },
            "bc": {
                "pin": gpio_pin(PA, 5)
            },
            "buttons": [
                {
                    "name": "PB0_PIN",
                    "pin": gpio_pin(PF, 6)
                },
                {
                    "name": "PB1_PIN",
                    "pin": gpio_pin(PF, 7)
                }
            ],
            "leds": [
                {
                    "name": "LED0_PIN",
                    "pin": gpio_pin(PF, 4)
                },
                {
                    "name": "LED1_PIN",
                    "pin": gpio_pin(PF, 5)
                }
            ],
            "ls013b7dh03": {
                "spi": 0,
                "com_pin": gpio_pin(PD, 13),
                "cs_pin": gpio_pin(PD, 14),
                "en_pin": gpio_pin(PD, 15)
            },
            "si7021": {
                "i2c": 0,
                "en_pin": gpio_pin(PB, 10)
            }
        }
    },
    {
        "cpu": "efm32gg11b820f2048gl192",
        "cpu_datasheet": "https://www.silabs.com/documents/public/data-sheets/efm32gg11-datasheet.pdf",  # noqa
        "board": "slstk3701a",
        "board_manual": "https://www.silabs.com/documents/public/user-guides/ug287-stk3701.pdf",  # noqa
        "family": "efm32gg11b",
        "family_full_name": "EFM32 Giant Gecko 11B",
        "family_manual": "https://www.silabs.com/documents/public/reference-manuals/efm32gg11-rm.pdf",  # noqa
        "features": ["aem", "bc"],
        "freq": {
            "hfxo": 50000000,
            "hfrco": 19000000,
            "lfxo": 32768,
            "lfrco": 32768,
            "ulfrco": 1000
        },
        "marketing_name": "EFM32 Giant Gecko GG11 Starter Kit",
        "part_number": 1,
        "peripherals": {
            "cmu": {
                "lfa": "cmuSelect_LFXO",
                "lfb": "cmuSelect_LFXO",
                "lfe": "cmuSelect_LFXO"
            },
            "adc": [
                {
                    "peripheral": "ADC0",
                    "channels": [
                        {
                            "dev": 0,
                            "input": "adcPosSelTEMP",
                            "reference": "adcRef1V25",
                            "acq_time": "adcAcqTime8"
                        },
                        {
                            "dev": 0,
                            "input": "adcPosSelAVDD",
                            "reference": "adcRef5V",
                            "acq_time": "adcAcqTime8"
                        }
                    ]
                }
            ],
            "dac": [

            ],
            "i2c": [
                {
                    "peripheral": "I2C0",
                    "sda_pin": gpio_pin(PC, 0),
                    "sda_loc": "I2C_ROUTELOC0_SDALOC_LOC4",
                    "scl_pin": gpio_pin(PC, 1),
                    "scl_loc": "I2C_ROUTELOC0_SCLLOC_LOC4",
                },
                {
                    "peripheral": "I2C1",
                    "sda_pin": gpio_pin(PC, 7),
                    "sda_loc": "I2C_ROUTELOC0_SDALOC_LOC0",
                    "scl_pin": gpio_pin(PC, 5),
                    "scl_loc": "I2C_ROUTELOC0_SCLLOC_LOC0",
                },
                {
                    "peripheral": "I2C2",
                    "sda_pin": gpio_pin(PI, 4),
                    "sda_loc": "I2C_ROUTELOC0_SDALOC_LOC7",
                    "scl_pin": gpio_pin(PI, 5),
                    "scl_loc": "I2C_ROUTELOC0_SCLLOC_LOC7",
                }
            ],
            "pwm": [

            ],
            "spi": [
                {
                    "peripheral": "USART1",
                    "mosi_pin": gpio_pin(PA, 14),
                    "mosi_loc": "USART_ROUTELOC0_TXLOC_LOC6",
                    "miso_pin": gpio_undef(),
                    "miso_loc": None,
                    "clk_pin": gpio_pin(PC, 15),
                    "clk_loc": "USART_ROUTELOC0_CLKLOC_LOC3",
                }
            ],
            "timer": [
                {
                    "prescaler": "WTIMER0",
                    "timer": "WTIMER1",
                    "channels": "3"
                },
                {
                    "prescaler": "TIMER0",
                    "timer": "TIMER1",
                    "channels": "3"
                },
                {
                    "prescaler": "NULL",
                    "timer": "LETIMER0",
                    "channels": "2"
                }
            ],
            "uart": [
                {
                    "peripheral": "USART4",
                    "rx_pin": gpio_pin(PH, 5),
                    "rx_loc": "USART_ROUTELOC0_RXLOC_LOC4",
                    "tx_pin": gpio_pin(PH, 4),
                    "tx_loc": "USART_ROUTELOC0_TXLOC_LOC4"
                }
            ]
        },
        "mappings": {
            "xtimer": {
                "default": {
                    "device": 0,
                    "frequency": 1000000,
                    "width": 32
                },
                "letimer": {
                    "device": 2,
                    "frequency": 32768,
                    "width": 16
                }
            },
            "bc": {
                "pin": gpio_pin(PE, 1)
            },
            "buttons": [
                {
                    "name": "PB0_PIN",
                    "pin": gpio_pin(PC, 8)
                },
                {
                    "name": "PB1_PIN",
                    "pin": gpio_pin(PC, 9)
                }
            ],
            "leds": [
                {
                    "name": "LED0R_PIN",
                    "pin": gpio_pin(PH, 10)
                },
                {
                    "name": "LED0G_PIN",
                    "pin": gpio_pin(PH, 11)
                },
                {
                    "name": "LED0B_PIN",
                    "pin": gpio_pin(PH, 12)
                },
                {
                    "name": "LED1R_PIN",
                    "pin": gpio_pin(PH, 13)
                },
                {
                    "name": "LED1G_PIN",
                    "pin": gpio_pin(PH, 14)
                },
                {
                    "name": "LED1B_PIN",
                    "pin": gpio_pin(PH, 15)
                },
                {
                    "name": "LED0_PIN",
                    "pin": gpio_alias("LED0R_PIN")
                },
                {
                    "name": "LED1_PIN",
                    "pin": gpio_alias("LED1R_PIN")
                }
            ],
            "ls013b7dh03": {
                "spi": 0,
                "com_pin": gpio_pin(PA, 11),
                "cs_pin": gpio_pin(PC, 14),
                "en_pin": gpio_pin(PA, 9)
            },
            "si7021": {
                "i2c": 2,
                "en_pin": gpio_pin(PB, 3)
            }
        }
    },
    {
        "cpu": "efr32mg1p132f256gm48",
        "cpu_datasheet": "https://www.silabs.com/documents/public/data-sheets/efr32mg1-datasheet.pdf",  # noqa
        "board": "sltb001a",
        "board_manual": "https://www.silabs.com/documents/public/user-guides/ug250-tb001-user-guide.pdf",  # noqa
        "family": "efr32mg1p",
        "family_full_name": "EFR32 Mighty Gecko 1P",
        "family_manual": "https://www.silabs.com/documents/public/reference-manuals/efr32xg1-rm.pdf",  # noqa
        "features": [],
        "freq": {
            "hfxo": 38400000,
            "hfrco": 19000000,
            "lfxo": 32768,
            "lfrco": 32768,
            "ulfrco": 1000
        },
        "marketing_name": "Thunderboard Sense",
        "part_number": 1,
        "peripherals": {
            "cmu": {
                "lfa": "cmuSelect_LFXO",
                "lfb": "cmuSelect_LFXO",
                "lfe": "cmuSelect_LFXO"
            },
            "adc": [
                {
                    "peripheral": "ADC0",
                    "channels": [
                        {
                            "dev": 0,
                            "input": "adcPosSelTEMP",
                            "reference": "adcRef1V25",
                            "acq_time": "adcAcqTime8"
                        },
                        {
                            "dev": 0,
                            "input": "adcPosSelAVDD",
                            "reference": "adcRef5V",
                            "acq_time": "adcAcqTime8"
                        }
                    ]
                }
            ],
            "dac": [

            ],
            "i2c": [
                {
                    "peripheral": "I2C0",
                    "sda_pin": gpio_pin(PC, 10),
                    "sda_loc": "I2C_ROUTELOC0_SDALOC_LOC15",
                    "scl_pin": gpio_pin(PC, 11),
                    "scl_loc": "I2C_ROUTELOC0_SCLLOC_LOC15",
                }
            ],
            "pwm": [

            ],
            "spi": [
                {
                    "peripheral": "USART1",
                    "mosi_pin": gpio_pin(PC, 6),
                    "mosi_loc": "USART_ROUTELOC0_RXLOC_LOC11",
                    "miso_pin": gpio_pin(PC, 7),
                    "miso_loc": "USART_ROUTELOC0_TXLOC_LOC11",
                    "clk_pin": gpio_pin(PC, 8),
                    "clk_loc": "USART_ROUTELOC0_CLKLOC_LOC11",
                }
            ],
            "timer": [
                {
                    "prescaler": "TIMER0",
                    "timer": "TIMER1",
                    "channels": "3"
                },
                {
                    "prescaler": "NULL",
                    "timer": "LETIMER0",
                    "channels": "2"
                }
            ],
            "uart": [
                {
                    "peripheral": "USART0",
                    "rx_pin": gpio_pin(PA, 1),
                    "rx_loc": "USART_ROUTELOC0_RXLOC_LOC0",
                    "tx_pin": gpio_pin(PA, 0),
                    "tx_loc": "USART_ROUTELOC0_TXLOC_LOC0"
                },
                {
                    "peripheral": "LEUART0",
                    "rx_pin": gpio_pin(PD, 11),
                    "rx_loc": "LEUART_ROUTELOC0_RXLOC_LOC18",
                    "tx_pin": gpio_pin(PD, 10),
                    "tx_loc": "LEUART_ROUTELOC0_TXLOC_LOC18"
                }
            ]
        },
        "mappings": {
            "xtimer": {
                "default": {
                    "device": 0,
                    "frequency": 250000,
                    "width": 16
                },
                "letimer": {
                    "device": 1,
                    "frequency": 32768,
                    "width": 16
                }
            },
            "buttons": [
                {
                    "name": "PB0_PIN",
                    "pin": gpio_pin(PD, 14)
                },
                {
                    "name": "PB1_PIN",
                    "pin": gpio_pin(PD, 15)
                }
            ],
            "leds": [
                {
                    "name": "LED0_PIN",
                    "pin": gpio_pin(PD, 12)
                },
                {
                    "name": "LED1_PIN",
                    "pin": gpio_pin(PD, 11)
                }
            ]
        }
    },
    {
        "cpu": "efr32mg12p332f1024gl125",
        "cpu_datasheet": "https://www.silabs.com/documents/public/data-sheets/efr32mg12-datasheet.pdf",  # noqa
        "board": "sltb004a",
        "board_manual": "https://www.silabs.com/documents/public/user-guides/ug309-sltb004a-user-guide.pdf",  # noqa
        "family": "efr32mg12p",
        "family_full_name": "EFR32 Mighty Gecko 12P",
        "family_manual": "https://www.silabs.com/documents/public/reference-manuals/efr32xg12-rm.pdf",  # noqa
        "features": [],
        "freq": {
            "hfxo": 38400000,
            "hfrco": 19000000,
            "lfxo": 32768,
            "lfrco": 32768,
            "ulfrco": 1000
        },
        "marketing_name": "Thunderboard Sense 2",
        "part_number": 1,
        "peripherals": {
            "cmu": {
                "lfa": "cmuSelect_LFXO",
                "lfb": "cmuSelect_LFXO",
                "lfe": "cmuSelect_LFXO"
            },
            "adc": [
                {
                    "peripheral": "ADC0",
                    "channels": [
                        {
                            "dev": 0,
                            "input": "adcPosSelTEMP",
                            "reference": "adcRef1V25",
                            "acq_time": "adcAcqTime8"
                        },
                        {
                            "dev": 0,
                            "input": "adcPosSelAVDD",
                            "reference": "adcRef5V",
                            "acq_time": "adcAcqTime8"
                        }
                    ]
                }
            ],
            "dac": [

            ],
            "i2c": [
                {
                    "peripheral": "I2C0",
                    "sda_pin": gpio_pin(PC, 10),
                    "sda_loc": "I2C_ROUTELOC0_SDALOC_LOC15",
                    "scl_pin": gpio_pin(PC, 11),
                    "scl_loc": "I2C_ROUTELOC0_SCLLOC_LOC15",
                }
            ],
            "pwm": [

            ],
            "spi": [
                {
                    "peripheral": "USART1",
                    "mosi_pin": gpio_pin(PC, 6),
                    "mosi_loc": "USART_ROUTELOC0_RXLOC_LOC11",
                    "miso_pin": gpio_pin(PC, 7),
                    "miso_loc": "USART_ROUTELOC0_TXLOC_LOC11",
                    "clk_pin": gpio_pin(PC, 8),
                    "clk_loc": "USART_ROUTELOC0_CLKLOC_LOC11",
                }
            ],
            "timer": [
                {
                    "prescaler": "TIMER0",
                    "timer": "TIMER1",
                    "channels": "3"
                },
                {
                    "prescaler": "NULL",
                    "timer": "LETIMER0",
                    "channels": "2"
                }
            ],
            "uart": [
                {
                    "peripheral": "USART0",
                    "rx_pin": gpio_pin(PA, 1),
                    "rx_loc": "USART_ROUTELOC0_RXLOC_LOC0",
                    "tx_pin": gpio_pin(PA, 0),
                    "tx_loc": "USART_ROUTELOC0_TXLOC_LOC0"
                },
                {
                    "peripheral": "LEUART0",
                    "rx_pin": gpio_pin(PD, 11),
                    "rx_loc": "LEUART_ROUTELOC0_RXLOC_LOC18",
                    "tx_pin": gpio_pin(PD, 10),
                    "tx_loc": "LEUART_ROUTELOC0_TXLOC_LOC18"
                }
            ]
        },
        "mappings": {
            "xtimer": {
                "default": {
                    "device": 0,
                    "frequency": 250000,
                    "width": 16
                },
                "letimer": {
                    "device": 1,
                    "frequency": 32768,
                    "width": 16
                }
            },
            "buttons": [
                {
                    "name": "PB0_PIN",
                    "pin": gpio_pin(PD, 14)
                },
                {
                    "name": "PB1_PIN",
                    "pin": gpio_pin(PD, 15)
                }
            ],
            "leds": [
                {
                    "name": "LED0_PIN",
                    "pin": gpio_pin(PD, 8)
                },
                {
                    "name": "LED1_PIN",
                    "pin": gpio_pin(PD, 9)
                }
            ]
        }
    },
    {
        "cpu": "efm32gg12b810f1024gm64",
        "cpu_datasheet": "https://www.silabs.com/documents/public/data-sheets/efm32gg12-datasheet.pdf",  # noqa
        "board": "sltb009a",
        "board_manual": "https://www.silabs.com/documents/public/user-guides/ug371-sltb009a-user-guide.pdf",  # noqa
        "family": "efm32gg12b",
        "family_full_name": "EFM32 Giant Gecko 12B",
        "family_manual": "https://www.silabs.com/documents/public/reference-manuals/efm32gg12-rm.pdf",  # noqa
        "features": [],
        "freq": {
            "hfxo": 50000000,
            "hfrco": 19000000,
            "lfxo": 32768,
            "lfrco": 32768,
            "ulfrco": 1000
        },
        "marketing_name": "Thunderboard GG12",
        "part_number": 1,
        "peripherals": {
            "cmu": {
                "lfa": "cmuSelect_LFXO",
                "lfb": "cmuSelect_LFXO",
                "lfe": "cmuSelect_LFXO"
            },
            "adc": [
                {
                    "peripheral": "ADC0",
                    "channels": [
                        {
                            "dev": 0,
                            "input": "adcPosSelTEMP",
                            "reference": "adcRef1V25",
                            "acq_time": "adcAcqTime8"
                        },
                        {
                            "dev": 0,
                            "input": "adcPosSelAVDD",
                            "reference": "adcRef5V",
                            "acq_time": "adcAcqTime8"
                        }
                    ]
                }
            ],
            "dac": [

            ],
            "i2c": [
                {
                    "peripheral": "I2C0",
                    "sda_pin": gpio_pin(PC, 10),
                    "sda_loc": "I2C_ROUTELOC0_SDALOC_LOC15",
                    "scl_pin": gpio_pin(PC, 11),
                    "scl_loc": "I2C_ROUTELOC0_SCLLOC_LOC15",
                }
            ],
            "pwm": [

            ],
            "spi": [
                {
                    "peripheral": "USART1",
                    "mosi_pin": gpio_pin(PC, 6),
                    "mosi_loc": "USART_ROUTELOC0_RXLOC_LOC11",
                    "miso_pin": gpio_pin(PC, 7),
                    "miso_loc": "USART_ROUTELOC0_TXLOC_LOC11",
                    "clk_pin": gpio_pin(PC, 8),
                    "clk_loc": "USART_ROUTELOC0_CLKLOC_LOC11",
                }
            ],
            "timer": [
                {
                    "prescaler": "TIMER0",
                    "timer": "TIMER1",
                    "channels": "3"
                },
                {
                    "prescaler": "NULL",
                    "timer": "LETIMER0",
                    "channels": "2"
                }
            ],
            "uart": [
                {
                    "peripheral": "USART0",
                    "rx_pin": gpio_pin(PE, 6),
                    "rx_loc": "USART_ROUTELOC0_RXLOC_LOC1",
                    "tx_pin": gpio_pin(PE, 7),
                    "tx_loc": "USART_ROUTELOC0_TXLOC_LOC1"
                },
                {
                    "peripheral": "LEUART0",
                    "rx_pin": gpio_pin(PD, 11),
                    "rx_loc": "LEUART_ROUTELOC0_RXLOC_LOC18",
                    "tx_pin": gpio_pin(PD, 10),
                    "tx_loc": "LEUART_ROUTELOC0_TXLOC_LOC18"
                }
            ]
        },
        "mappings": {
            "xtimer": {
                "default": {
                    "device": 0,
                    "frequency": 250000,
                    "width": 16
                },
                "letimer": {
                    "device": 1,
                    "frequency": 32768,
                    "width": 16
                }
            },
            "buttons": [
                {
                    "name": "PB0_PIN",
                    "pin": gpio_pin(PD, 5)
                },
                {
                    "name": "PB1_PIN",
                    "pin": gpio_pin(PD, 8)
                }
            ],
            "leds": [
                {
                    "name": "LED0R_PIN",
                    "pin": gpio_pin(PA, 12)
                },
                {
                    "name": "LED0G_PIN",
                    "pin": gpio_pin(PA, 13)
                },
                {
                    "name": "LED0B_PIN",
                    "pin": gpio_pin(PA, 14)
                },
                {
                    "name": "LED1R_PIN",
                    "pin": gpio_pin(PD, 6)
                },
                {
                    "name": "LED1G_PIN",
                    "pin": gpio_pin(PF, 12)
                },
                {
                    "name": "LED1B_PIN",
                    "pin": gpio_pin(PE, 12)
                },
                {
                    "name": "LED0_PIN",
                    "pin": gpio_alias("LED0R_PIN")
                },
                {
                    "name": "LED1_PIN",
                    "pin": gpio_alias("LED1R_PIN")
                }
            ]
        }
    },
    {
        "cpu": "efr32bg22c224f512im40",
        "cpu_datasheet": "https://www.silabs.com/documents/public/data-sheets/efr32bg22-datasheet.pdf",  # noqa
        "board": "sltb010a",
        "board_manual": "https://www.silabs.com/documents/public/user-guides/ug415-sltb010a-user-guide.pdf",  # noqa
        "family": "efr32bg22",
        "family_full_name": "EFR32 BG22",
        "family_manual": "https://www.silabs.com/documents/public/reference-manuals/efr32xg22-rm.pdf",  # noqa
        "features": [],
        "freq": {
            "hfxo": 38400000,
            "hfrco": 19000000,
            "lfxo": 32768,
            "lfrco": 32768,
            "ulfrco": 1000
        },
        "marketing_name": "Thunderboard BG22 Kit",
        "part_number": 1,
        "peripherals": {
            "cmu": {
                "lfa": "cmuSelect_LFXO",
                "lfb": "cmuSelect_LFXO",
                "lfe": "cmuSelect_LFXO"
            },
            "adc": [
                {
                    "peripheral": "ADC0",
                    "channels": [
                        {
                            "dev": 0,
                            "input": "adcPosSelTEMP",
                            "reference": "adcRef1V25",
                            "acq_time": "adcAcqTime8"
                        },
                        {
                            "dev": 0,
                            "input": "adcPosSelAVDD",
                            "reference": "adcRef5V",
                            "acq_time": "adcAcqTime8"
                        }
                    ]
                }
            ],
            "dac": [

            ],
            "i2c": [
                {
                    "peripheral": "I2C0",
                    "sda_pin": gpio_pin(PC, 10),
                    "scl_pin": gpio_pin(PC, 11),
                }
            ],
            "pwm": [

            ],
            "spi": [
                {
                    "peripheral": "USART1",
                    "mosi_pin": gpio_pin(PC, 6),
                    "miso_pin": gpio_pin(PC, 7),
                    "clk_pin": gpio_pin(PC, 8),
                }
            ],
            "timer": [
                {
                    "prescaler": "TIMER0",
                    "timer": "TIMER1",
                    "channels": "3"
                },
                {
                    "prescaler": "NULL",
                    "timer": "LETIMER0",
                    "channels": "2"
                }
            ],
            "uart": [
                {
                    "peripheral": "USART1",
                    "rx_pin": gpio_pin(PA, 6),
                    "tx_pin": gpio_pin(PA, 5),
                },
                {
                    "peripheral": "LEUART0",
                    "rx_pin": gpio_pin(PD, 11),
                    "tx_pin": gpio_pin(PD, 10),
                }
            ]
        },
        "mappings": {
            "xtimer": {
                "default": {
                    "device": 0,
                    "frequency": 250000,
                    "width": 16
                },
                "letimer": {
                    "device": 1,
                    "frequency": 32768,
                    "width": 16
                }
            },
            "buttons": [
                {
                    "name": "PB0_PIN",
                    "pin": gpio_pin(PB, 1)
                },
                {
                    "name": "PB1_PIN",
                    "pin": gpio_undef()
                }
            ],
            "leds": [
                {
                    "name": "LED0_PIN",
                    "pin": gpio_pin(PB, 0)
                },
                {
                    "name": "LED1_PIN",
                    "pin": gpio_undef()
                }
            ]
        }
    },
    {
        "cpu": "efr32mg12p332f1024gl125",
        "cpu_datasheet": "https://www.silabs.com/documents/public/data-sheets/efr32mg12-datasheet.pdf",  # noqa
        "board": "slwstk6000b",
        "board_manual": "https://www.silabs.com/documents/public/user-guides/ug260-brd4161a.pdf",  # noqa
        "family": "efr32mg12p",
        "family_full_name": "EFR32 Mighty Gecko 12P",
        "family_manual": "https://www.silabs.com/documents/public/reference-manuals/efr32xg12-rm.pdf",  # noqa
        "features": ["aem", "bc"],
        "freq": {
            "hfxo": 38400000,
            "hfrco": 19000000,
            "lfxo": 32768,
            "lfrco": 32768,
            "ulfrco": 1000
        },
        "marketing_name": "Mighty Gecko Wireless Starter Kit",
        "part_number": 1,
        "peripherals": {
            "cmu": {
                "lfa": "cmuSelect_LFRCO",
                "lfb": "cmuSelect_LFRCO",
                "lfe": "cmuSelect_LFRCO"
            },
            "adc": [
                {
                    "peripheral": "ADC0",
                    "channels": [
                        {
                            "dev": 0,
                            "input": "adcPosSelTEMP",
                            "reference": "adcRef1V25",
                            "acq_time": "adcAcqTime8"
                        },
                        {
                            "dev": 0,
                            "input": "adcPosSelAVDD",
                            "reference": "adcRef5V",
                            "acq_time": "adcAcqTime8"
                        }
                    ]
                }
            ],
            "dac": [

            ],
            "i2c": [
                {
                    "peripheral": "I2C0",
                    "sda_pin": gpio_alias("MODULE_PIN_P13"),
                    "sda_loc": "I2C_ROUTELOC0_SDALOC_LOC16",
                    "scl_pin": gpio_alias("MODULE_PIN_P12"),
                    "scl_loc": "I2C_ROUTELOC0_SCLLOC_LOC14",
                }
            ],
            "pwm": [

            ],
            "spi": [
                {
                    "peripheral": "USART1",
                    "mosi_pin": gpio_alias("MODULE_PIN_F16"),
                    "mosi_loc": "USART_ROUTELOC0_RXLOC_LOC11",
                    "miso_pin": gpio_alias("MODULE_PIN_P3"),
                    "miso_loc": "USART_ROUTELOC0_TXLOC_LOC11",
                    "clk_pin": gpio_alias("MODULE_PIN_F15"),
                    "clk_loc": "USART_ROUTELOC0_CLKLOC_LOC11",
                }
            ],
            "timer": [
                {
                    "prescaler": "TIMER0",
                    "timer": "TIMER1",
                    "channels": "3"
                },
                {
                    "prescaler": "NULL",
                    "timer": "LETIMER0",
                    "channels": "2"
                }
            ],
            "uart": [
                {
                    "peripheral": "USART0",
                    "rx_pin": gpio_alias("MODULE_PIN_F7"),
                    "rx_loc": "USART_ROUTELOC0_RXLOC_LOC0",
                    "tx_pin": gpio_alias("MODULE_PIN_F6"),
                    "tx_loc": "USART_ROUTELOC0_TXLOC_LOC0"
                }
            ]
        },
        "mappings": {
            "xtimer": {
                "default": {
                    "device": 0,
                    "frequency": 250000,
                    "width": 16
                },
                "letimer": {
                    "device": 1,
                    "frequency": 32768,
                    "width": 16
                }
            },
            "bc": {
                "pin": gpio_alias("MODULE_PIN_F5")
            },
            "buttons": [
                {
                    "name": "PB0_PIN",
                    "pin": gpio_alias("MODULE_PIN_F12")
                },
                {
                    "name": "PB1_PIN",
                    "pin": gpio_alias("MODULE_PIN_F13")
                }
            ],
            "leds": [
                {
                    "name": "LED0_PIN",
                    "pin": gpio_alias("MODULE_PIN_F10")
                },
                {
                    "name": "LED1_PIN",
                    "pin": gpio_alias("MODULE_PIN_F11")
                }
            ],
            "ls013b7dh03": {
                "spi": 0,
                "com_pin": gpio_alias("MODULE_PIN_F18"),
                "cs_pin": gpio_alias("MODULE_PIN_F17"),
                "en_pin": gpio_alias("MODULE_PIN_F14")
            },
            "si7021": {
                "i2c": 0,
                "en_pin": gpio_alias("MODULE_PIN_P37")
            }
        }
    },
    {
        "cpu": "ezr32wg330f256r60",
        "cpu_datasheet": "https://www.silabs.com/documents/public/data-sheets/EZR32WG330_DataSheet.pdf",  # noqa
        "board": "slwstk6220a",
        "board_manual": "https://www.silabs.com/documents/public/user-guides/ug200-brd4502c-user-guide.pdf",  # noqa
        "family": "ezr32wg",
        "family_full_name": "EZR32 Wonder Gecko",
        "family_manual": "https://www.silabs.com/documents/public/reference-manuals/EZR32LG-RM.pdf",  # noqa
        "features": ["aem", "bc"],
        "freq": {
            "hfxo": 48000000,
            "hfrco": 14000000,
            "lfxo": 32768,
            "lfrco": 32768,
            "ulfrco": 1000
        },
        "marketing_name": "EZR32WG 868MHz Wireless Starter Kit",
        "part_number": 1,
        "peripherals": {
            "cmu": {
                "lfa": "cmuSelect_LFXO",
                "lfb": "cmuSelect_LFXO",
                "lfe": "cmuSelect_LFXO"
            },
            "adc": [
                {
                    "peripheral": "ADC0",
                    "channels": [
                        {
                            "dev": 0,
                            "input": "adcSingleInputTemp",
                            "reference": "adcRef1V25",
                            "acq_time": "adcAcqTime8"
                        },
                        {
                            "dev": 0,
                            "input": "adcSingleInputVDDDiv3",
                            "reference": "adcRef1V25",
                            "acq_time": "adcAcqTime8"
                        }
                    ]
                }
            ],
            "dac": [
                {
                    "peripheral": "DAC0",
                    "channels": [
                        {
                            "dev": 0,
                            "index": 1,
                            "ref": "dacRefVDD"
                        }
                    ]
                }
            ],
            "i2c": [
                {
                    "peripheral": "I2C1",
                    "sda_pin": gpio_pin(PE, 0),
                    "scl_pin": gpio_pin(PE, 1),
                    "loc": "I2C_ROUTE_LOCATION_LOC2",
                }
            ],
            "pwm": [
                {
                    "peripheral": "TIMER0",
                    "channels": [
                        {
                            "index": 0,
                            "pin": gpio_pin(PF, 6),
                            "loc": "TIMER_ROUTE_LOCATION_LOC2"
                        },
                        {
                            "index": 1,
                            "pin": gpio_pin(PF, 7),
                            "loc": "TIMER_ROUTE_LOCATION_LOC2"
                        }
                    ]
                }
            ],
            "spi": [
                {
                    "peripheral": "USART1",
                    "mosi_pin": gpio_pin(PD, 0),
                    "miso_pin": gpio_pin(PD, 1),
                    "clk_pin": gpio_pin(PD, 2),
                    "loc": "USART_ROUTE_LOCATION_LOC1",
                }
            ],
            "timer": [
                {
                    "prescaler": "TIMER1",
                    "timer": "TIMER2",
                    "channels": "3"
                },
                {
                    "prescaler": "NULL",
                    "timer": "LETIMER0",
                    "channels": "2"
                }
            ],
            "uart": [
                {
                    "peripheral": "USART2",
                    "rx_pin": gpio_pin(PB, 4),
                    "tx_pin": gpio_pin(PB, 3),
                    "loc": "USART_ROUTE_LOCATION_LOC1"
                },
                {
                    "peripheral": "LEUART0",
                    "rx_pin": gpio_pin(PD, 5),
                    "tx_pin": gpio_pin(PD, 4),
                    "loc": "LEUART_ROUTE_LOCATION_LOC0"
                }
            ]
        },
        "mappings": {
            "xtimer": {
                "default": {
                    "device": 0,
                    "frequency": 250000,
                    "width": 16
                },
                "letimer": {
                    "device": 1,
                    "frequency": 32768,
                    "width": 16
                }
            },
            "bc": {
                "pin": gpio_pin(PA, 12)
            },
            "buttons": [
                {
                    "name": "PB0_PIN",
                    "pin": gpio_pin(PE, 3)
                },
                {
                    "name": "PB1_PIN",
                    "pin": gpio_pin(PE, 2)
                }
            ],
            "leds": [
                {
                    "name": "LED0_PIN",
                    "pin": gpio_pin(PF, 6)
                },
                {
                    "name": "LED1_PIN",
                    "pin": gpio_pin(PF, 7)
                }
            ],
            "ls013b7dh03": {
                "spi": 0,
                "com_pin": gpio_pin(PE, 10),
                "cs_pin": gpio_pin(PE, 11),
                "select_pin": gpio_pin(PA, 8),
                "power_pin": gpio_pin(PA, 10)
            },
            "si7021": {
                "i2c": 0,
                "en_pin": gpio_pin(PF, 8)
            }
        }
    },
    {
        "cpu": "efm32zg222f32",
        "cpu_datasheet": "https://www.silabs.com/documents/public/data-sheets/efm32zg-datasheet.pdf",  # noqa
        "board": "stk3200",
        "board_manual": "https://www.silabs.com/documents/public/user-guides/efm32zg-stk3200-ug.pdf",  # noqa
        "family_full_name": "EFM32 Zero Gecko",
        "family_manual": "https://www.silabs.com/documents/public/reference-manuals/EFM32ZG-RM.pdf",  # noqa
        "features": ["bc"],
        "freq": {
            "hfxo": 24000000,
            "hfrco": 14000000,
            "lfxo": 32768,
            "lfrco": 32768,
            "ulfrco": 1000
        },
        "marketing_name": "EFM32 Zero Gecko Starter Kit",
        "part_number": 1,
        "peripherals": {
            "cmu": {
                "lfa": "cmuSelect_LFXO",
                "lfb": "cmuSelect_CORELEDIV2"
            },
            "adc": [
                {
                    "peripheral": "ADC0",
                    "channels": [
                        {
                            "dev": 0,
                            "input": "adcSingleInputTemp",
                            "reference": "adcRef1V25",
                            "acq_time": "adcAcqTime8"
                        },
                        {
                            "dev": 0,
                            "input": "adcSingleInputVDDDiv3",
                            "reference": "adcRef1V25",
                            "acq_time": "adcAcqTime8"
                        }
                    ]
                }
            ],
            "dac": [

            ],
            "i2c": [
                {
                    "peripheral": "I2C0",
                    "sda_pin": gpio_pin(PE, 12),
                    "scl_pin": gpio_pin(PE, 13),
                    "loc": "I2C_ROUTE_LOCATION_LOC6",
                }
            ],
            "pwm": [

            ],
            "spi": [
                {
                    "peripheral": "USART1",
                    "mosi_pin": gpio_pin(PD, 7),
                    "miso_pin": gpio_pin(PD, 6),
                    "clk_pin": gpio_pin(PC, 15),
                    "loc": "USART_ROUTE_LOCATION_LOC1",
                }
            ],
            "timer": [
                {
                    "prescaler": "TIMER0",
                    "timer": "TIMER1",
                    "channels": "3"
                }
            ],
            "uart": [
                {
                    "peripheral": "LEUART0",
                    "rx_pin": gpio_pin(PD, 5),
                    "tx_pin": gpio_pin(PD, 4),
                    "loc": "LEUART_ROUTE_LOCATION_LOC0"
                }
            ]
        },
        "mappings": {
            "xtimer": {
                "default": {
                    "device": 0,
                    "frequency": 250000,
                    "width": 16
                }
            },
            "bc": {
                "pin": gpio_pin(PA, 9)
            },
            "buttons": [
                {
                    "name": "PB0_PIN",
                    "pin": gpio_pin(PC, 8)
                },
                {
                    "name": "PB1_PIN",
                    "pin": gpio_pin(PC, 9)
                }
            ],
            "leds": [
                {
                    "name": "LED0_PIN",
                    "pin": gpio_pin(PC, 10)
                },
                {
                    "name": "LED1_PIN",
                    "pin": gpio_pin(PC, 11)
                }
            ],
            "ls013b7dh03": {
                "spi": 0,
                "com_pin": gpio_pin(PE, 10),
                "cs_pin": gpio_pin(PE, 11),
                "select_pin": gpio_pin(PA, 8),
                "power_pin": gpio_pin(PA, 10)
            }
        }
    },
    {
        "cpu": "efm32lg990f256",
        "cpu_datasheet": "https://www.silabs.com/documents/public/data-sheets/efm32lg-datasheet.pdf",  # noqa
        "board": "stk3600",
        "board_manual": "https://www.silabs.com/documents/public/user-guides/efm32lg-stk3600-ug.pdf",  # noqa
        "family": "efm32lg",
        "family_full_name": "EFM32 Leoppard Gecko",
        "family_manual": "https://www.silabs.com/documents/public/reference-manuals/EFM32LG-RM.pdf",  # noqa
        "features": ["aem", "bc"],
        "freq": {
            "hfxo": 48000000,
            "hfrco": 14000000,
            "lfxo": 32768,
            "lfrco": 32768,
            "ulfrco": 1000
        },
        "marketing_name": "EFM32 Leopard Gecko Starter Kit",
        "part_number": 1,
        "peripherals": {
            "cmu": {
                "lfa": "cmuSelect_LFXO",
                "lfb": "cmuSelect_LFXO"
            },
            "adc": [
                {
                    "peripheral": "ADC0",
                    "channels": [
                        {
                            "dev": 0,
                            "input": "adcSingleInputTemp",
                            "reference": "adcRef1V25",
                            "acq_time": "adcAcqTime8"
                        },
                        {
                            "dev": 0,
                            "input": "adcSingleInputVDDDiv3",
                            "reference": "adcRef1V25",
                            "acq_time": "adcAcqTime8"
                        }
                    ]
                }
            ],
            "dac": [
                {
                    "peripheral": "DAC0",
                    "channels": [
                        {
                            "dev": 0,
                            "index": 1,
                            "ref": "dacRefVDD"
                        }
                    ]
                }
            ],
            "i2c": [
                {
                    "peripheral": "I2C0",
                    "sda_pin": gpio_pin(PD, 6),
                    "scl_pin": gpio_pin(PD, 7),
                    "loc": "I2C_ROUTE_LOCATION_LOC1",
                },
                {
                    "peripheral": "I2C1",
                    "sda_pin": gpio_pin(PC, 4),
                    "scl_pin": gpio_pin(PC, 5),
                    "loc": "I2C_ROUTE_LOCATION_LOC0",
                }
            ],
            "pwm": [
                {
                    "peripheral": "TIMER3",
                    "channels": [
                        {
                            "index": 2,
                            "pin": gpio_pin(PE, 2),
                            "loc": "TIMER_ROUTE_LOCATION_LOC1"
                        }
                    ]
                }
            ],
            "spi": [
                {
                    "peripheral": "USART1",
                    "mosi_pin": gpio_pin(PD, 0),
                    "miso_pin": gpio_pin(PD, 1),
                    "clk_pin": gpio_pin(PD, 2),
                    "loc": "USART_ROUTE_LOCATION_LOC1",
                },
                {
                    "peripheral": "USART2",
                    "mosi_pin": gpio_undef(),
                    "miso_pin": gpio_pin(PC, 3),
                    "clk_pin": gpio_pin(PC, 4),
                    "loc": "USART_ROUTE_LOCATION_LOC0",
                }
            ],
            "timer": [
                {
                    "prescaler": "TIMER0",
                    "timer": "TIMER1",
                    "channels": "3"
                },
                {
                    "prescaler": "NULL",
                    "timer": "LETIMER0",
                    "channels": "2"
                }
            ],
            "uart": [
                {
                    "peripheral": "UART0",
                    "rx_pin": gpio_pin(PE, 1),
                    "tx_pin": gpio_pin(PE, 0),
                    "loc": "UART_ROUTE_LOCATION_LOC1"
                },
                {
                    "peripheral": "LEUART0",
                    "rx_pin": gpio_pin(PD, 5),
                    "tx_pin": gpio_pin(PD, 4),
                    "loc": "LEUART_ROUTE_LOCATION_LOC0"
                }
            ]
        },
        "mappings": {
            "xtimer": {
                "default": {
                    "device": 0,
                    "frequency": 250000,
                    "width": 16
                },
                "letimer": {
                    "device": 1,
                    "frequency": 32768,
                    "width": 16
                }
            },
            "bc": {
                "pin": gpio_pin(PF, 7)
            },
            "buttons": [
                {
                    "name": "PB0_PIN",
                    "pin": gpio_pin(PB, 9)
                },
                {
                    "name": "PB1_PIN",
                    "pin": gpio_pin(PB, 10)
                }
            ],
            "leds": [
                {
                    "name": "LED0_PIN",
                    "pin": gpio_pin(PE, 2)
                },
                {
                    "name": "LED1_PIN",
                    "pin": gpio_pin(PE, 3)
                }
            ]
        }
    },
    {
        "cpu": "efm32gg990f1024",
        "cpu_datasheet": "https://www.silabs.com/documents/public/data-sheets/efm32gg-datasheet.pdf",  # noqa
        "board": "stk3700",
        "board_manual": "https://www.silabs.com/documents/public/user-guides/efm32gg-stk3700-ug.pdf",  # noqa
        "family": "efm32gg",
        "family_full_name": "EFM32 Giant Gecko",
        "family_manual": "https://www.silabs.com/documents/public/reference-manuals/EFM32GG-RM.pdf",  # noqa
        "features": ["aem", "bc"],
        "freq": {
            "hfxo": 48000000,
            "hfrco": 14000000,
            "lfxo": 32768,
            "lfrco": 32768,
            "ulfrco": 1000
        },
        "marketing_name": "EFM32 Giant Gecko Starter Kit",
        "part_number": 1,
        "peripherals": {
            "cmu": {
                "lfa": "cmuSelect_LFXO",
                "lfb": "cmuSelect_LFXO"
            },
            "adc": [
                {
                    "peripheral": "ADC0",
                    "channels": [
                        {
                            "dev": 0,
                            "input": "adcSingleInputTemp",
                            "reference": "adcRef1V25",
                            "acq_time": "adcAcqTime8"
                        },
                        {
                            "dev": 0,
                            "input": "adcSingleInputVDDDiv3",
                            "reference": "adcRef1V25",
                            "acq_time": "adcAcqTime8"
                        }
                    ]
                }
            ],
            "dac": [
                {
                    "peripheral": "DAC0",
                    "channels": [
                        {
                            "dev": 0,
                            "index": 1,
                            "ref": "dacRefVDD"
                        }
                    ]
                }
            ],
            "i2c": [
                {
                    "peripheral": "I2C0",
                    "sda_pin": gpio_pin(PD, 6),
                    "scl_pin": gpio_pin(PD, 7),
                    "loc": "I2C_ROUTE_LOCATION_LOC1",
                },
                {
                    "peripheral": "I2C1",
                    "sda_pin": gpio_pin(PC, 4),
                    "scl_pin": gpio_pin(PC, 5),
                    "loc": "I2C_ROUTE_LOCATION_LOC0",
                }
            ],
            "pwm": [
                {
                    "peripheral": "TIMER3",
                    "channels": [
                        {
                            "index": 2,
                            "pin": gpio_pin(PE, 2),
                            "loc": "TIMER_ROUTE_LOCATION_LOC1"
                        }
                    ]
                }
            ],
            "spi": [
                {
                    "peripheral": "USART1",
                    "mosi_pin": gpio_pin(PD, 0),
                    "miso_pin": gpio_pin(PD, 1),
                    "clk_pin": gpio_pin(PD, 2),
                    "loc": "USART_ROUTE_LOCATION_LOC1",
                },
                {
                    "peripheral": "USART2",
                    "mosi_pin": gpio_undef(),
                    "miso_pin": gpio_pin(PC, 3),
                    "clk_pin": gpio_pin(PC, 4),
                    "loc": "USART_ROUTE_LOCATION_LOC0",
                }
            ],
            "timer": [
                {
                    "prescaler": "TIMER0",
                    "timer": "TIMER1",
                    "channels": "3"
                },
                {
                    "prescaler": "NULL",
                    "timer": "LETIMER0",
                    "channels": "2"
                }
            ],
            "uart": [
                {
                    "peripheral": "UART0",
                    "rx_pin": gpio_pin(PE, 1),
                    "tx_pin": gpio_pin(PE, 0),
                    "loc": "UART_ROUTE_LOCATION_LOC1"
                },
                {
                    "peripheral": "LEUART0",
                    "rx_pin": gpio_pin(PD, 5),
                    "tx_pin": gpio_pin(PD, 4),
                    "loc": "LEUART_ROUTE_LOCATION_LOC0"
                }
            ]
        },
        "mappings": {
            "xtimer": {
                "default": {
                    "device": 0,
                    "frequency": 250000,
                    "width": 16
                },
                "letimer": {
                    "device": 1,
                    "frequency": 32768,
                    "width": 16
                }
            },
            "bc": {
                "pin": gpio_pin(PF, 7)
            },
            "buttons": [
                {
                    "name": "PB0_PIN",
                    "pin": gpio_pin(PB, 9)
                },
                {
                    "name": "PB1_PIN",
                    "pin": gpio_pin(PB, 10)
                }
            ],
            "leds": [
                {
                    "name": "LED0_PIN",
                    "pin": gpio_pin(PE, 2)
                },
                {
                    "name": "LED1_PIN",
                    "pin": gpio_pin(PE, 3)
                }
            ]
        }
    },
    {
        "cpu": "efm32wg990f256",
        "cpu_datasheet": "https://www.silabs.com/documents/public/data-sheets/efm32wg-datasheet.pdf",  # noqa
        "board": "stk3800",
        "board_manual": "https://www.silabs.com/documents/public/user-guides/efm32wg-stk3800-ug.pdf",  # noqa
        "family": "efm32wg",
        "family_full_name": "EFM32 Wonder Gecko",
        "family_manual": "https://www.silabs.com/documents/public/reference-manuals/EFM32WG-RM.pdf",  # noqa
        "features": ["aem", "bc"],
        "freq": {
            "hfxo": 48000000,
            "hfrco": 14000000,
            "lfxo": 32768,
            "lfrco": 32768,
            "ulfrco": 1000
        },
        "marketing_name": "EFM32 Wonder Gecko Starter Kit",
        "part_number": 1,
        "peripherals": {
            "cmu": {
                "lfa": "cmuSelect_LFXO",
                "lfb": "cmuSelect_LFXO"
            },
            "adc": [
                {
                    "peripheral": "ADC0",
                    "channels": [
                        {
                            "dev": 0,
                            "input": "adcSingleInputTemp",
                            "reference": "adcRef1V25",
                            "acq_time": "adcAcqTime8"
                        },
                        {
                            "dev": 0,
                            "input": "adcSingleInputVDDDiv3",
                            "reference": "adcRef1V25",
                            "acq_time": "adcAcqTime8"
                        }
                    ]
                }
            ],
            "dac": [
                {
                    "peripheral": "DAC0",
                    "channels": [
                        {
                            "dev": 0,
                            "index": 1,
                            "ref": "dacRefVDD"
                        }
                    ]
                }
            ],
            "i2c": [
                {
                    "peripheral": "I2C0",
                    "sda_pin": gpio_pin(PD, 6),
                    "scl_pin": gpio_pin(PD, 7),
                    "loc": "I2C_ROUTE_LOCATION_LOC1",
                },
                {
                    "peripheral": "I2C1",
                    "sda_pin": gpio_pin(PC, 4),
                    "scl_pin": gpio_pin(PC, 5),
                    "loc": "I2C_ROUTE_LOCATION_LOC0",
                }
            ],
            "pwm": [
                {
                    "peripheral": "TIMER3",
                    "channels": [
                        {
                            "index": 2,
                            "pin": gpio_pin(PE, 2),
                            "loc": "TIMER_ROUTE_LOCATION_LOC1"
                        }
                    ]
                }
            ],
            "spi": [
                {
                    "peripheral": "USART1",
                    "mosi_pin": gpio_pin(PD, 0),
                    "miso_pin": gpio_pin(PD, 1),
                    "clk_pin": gpio_pin(PD, 2),
                    "loc": "USART_ROUTE_LOCATION_LOC1",
                },
                {
                    "peripheral": "USART2",
                    "mosi_pin": gpio_undef(),
                    "miso_pin": gpio_pin(PC, 3),
                    "clk_pin": gpio_pin(PC, 4),
                    "loc": "USART_ROUTE_LOCATION_LOC0",
                }
            ],
            "timer": [
                {
                    "prescaler": "TIMER0",
                    "timer": "TIMER1",
                    "channels": "3"
                },
                {
                    "prescaler": "NULL",
                    "timer": "LETIMER0",
                    "channels": "2"
                }
            ],
            "uart": [
                {
                    "peripheral": "UART0",
                    "rx_pin": gpio_pin(PE, 1),
                    "tx_pin": gpio_pin(PE, 0),
                    "loc": "UART_ROUTE_LOCATION_LOC1"
                },
                {
                    "peripheral": "LEUART0",
                    "rx_pin": gpio_pin(PD, 5),
                    "tx_pin": gpio_pin(PD, 4),
                    "loc": "LEUART_ROUTE_LOCATION_LOC0"
                }
            ]
        },
        "mappings": {
            "xtimer": {
                "default": {
                    "device": 0,
                    "frequency": 250000,
                    "width": 16
                },
                "letimer": {
                    "device": 1,
                    "frequency": 32768,
                    "width": 16
                }
            },
            "bc": {
                "pin": gpio_pin(PF, 7)
            },
            "buttons": [
                {
                    "name": "PB0_PIN",
                    "pin": gpio_pin(PB, 9)
                },
                {
                    "name": "PB1_PIN",
                    "pin": gpio_pin(PB, 10)
                }
            ],
            "leds": [
                {
                    "name": "LED0_PIN",
                    "pin": gpio_pin(PE, 2)
                },
                {
                    "name": "LED1_PIN",
                    "pin": gpio_pin(PE, 3)
                }
            ]
        }
    }
]
