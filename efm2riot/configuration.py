from efm2riot import patches, filters

# Static copy actions (source, destination).
STATICS = [
    {
        "type": "file",
        "source": "{{ root }}/static/README.md",
        "target": "README.md"
    },
    {
        "type": "directory",
        "source": "{{ root }}/static/cpu/efm32_common",
        "target": "cpu/efm32_common"
    },
    {
        "type": "directory",
        "source": "{{ root }}/static/doc/images",
        "target": "doc/images"
    },
    {
        "type": "directory",
        "source": "{{ root }}/static/examples",
        "target": "examples"
    },
    {
        "type": "directory",
        "source": "{{ sdk }}/emlib",
        "target": "cpu/efm32_common/emlib"
    }
]

# Template files.
TEMPLATES = [
    {
        "type": "file",
        "when": "per_cpu",
        "source": "{{ root }}/templates/cpu/family/ldscripts/cpu.ld",
        "target": "cpu/{{ family }}/ldscripts/{{ cpu }}.ld"
    },
    {
        "type": "file",
        "when": "per_family",
        "source": "{{ sdk }}/Device/SiliconLabs/{{ family|upper }}/Source/system_{{ family }}.c",  # noqa
        "target": "cpu/{{ family }}/system_{{ family }}.c"
    },
    {
        "type": "glob",
        "when": "per_family",
        "source": "{{ root }}/templates/cpu/family/include/*",
        "target": "cpu/{{ family }}/include"
    },
    {
        "type": "glob",
        "when": "per_family",
        "source": "{{ root }}/templates/cpu/family/*",
        "target": "cpu/{{ family }}"
    },
    {
        "type": "glob",
        "when": "per_family",
        "source": "{{ root }}/templates/cpu/family/periph/*",
        "target": "cpu/{{ family }}/periph"
    },
    {
        "type": "glob",
        "when": "per_board",
        "source": "{{ root }}/templates/boards/board/include/*",
        "target": "boards/{{ board }}/include",
        "filters": {
            "{{ root }}/templates/boards/board/include/si70xx_params.h": filters.only_for_board([  # noqa
                "slstk3401a", "slwstk6220a", "sltb001a"
            ])
        }
    },
    {
        "type": "glob",
        "when": "per_board",
        "source": "{{ root }}/templates/boards/board/*",
        "target": "boards/{{ board }}",
    },
    {
        "type": "file",
        "when": "per_board",
        "source": "{{ root }}/templates/doc/Board.md",
        "target": "doc/{{ board_display_name }}.md",
    },
    {
        "type": "glob",
        "when": "once",
        "source": "{{ root }}/templates/contrib/*",
        "target": "contrib/",
    }
]

# Files that need a patch.
PATCHES = [
    {
        "type": "glob",
        "when": "per_family",
        "source": "{{ sdk }}/Device/SiliconLabs/{{ family|upper }}/Include/*.h",  # noqa
        "target": "cpu/{{ family }}/include",
        "methods": [patches.add_extern_c, patches.fix_arm_math]
    }
]

# Board definitions.
BOARDS = [
    {
        "cpu": "efm32zg222f32",
        "cpu_datasheet": "https://www.silabs.com/Support%20Documents/TechnicalDocs/EFM32ZG222.pdf",  # noqa
        "board": "stk3200",
        "board_display_name": "STK3200",
        "board_manual": "https://www.silabs.com/Support%20Documents/TechnicalDocs/efm32zg-stk3200-ug.pdf",  # noqa
        "board_schematic": "https://www.silabs.com/Support%20Documents/TechnicalDocs/BRD2010A_B01.pdf",  # noqa
        "family_display_name": "EFM32ZG",
        "family_display_name_full": "EFM32 Zero Gecko",
        "family_manual": "https://www.silabs.com/Support%20Documents/TechnicalDocs/EFM32ZG-RM.pdf",  # noqa
        "freq": {
            "hfxo": 24000000,
            "hfrco": 14000000,
            "lfxo": 32768,
            "lfrco": 32768,
            "ulfrco": 1000
        },
        "marketing_display_name": "EFM32 Zero Gecko Starter Kit"
    },
    {
        "cpu": "efm32pg1b200f256gm48",
        "cpu_datasheet": "https://www.silabs.com/Support%20Documents/TechnicalDocs/EFM32PG1-DataSheet.pdf",  # noqa
        "board": "slstk3401a",
        "board_display_name": "SLSTK3401A",
        "board_manual": "",
        "board_schematic": "",
        "family": "efm32pg",
        "family_display_name": "EFM32PG",
        "family_display_name_full": "EFM32 Pearl Gecko",
        "family_manual": "https://www.silabs.com/Support%20Documents/TechnicalDocs/EFM32PG1-ReferenceManual.pdf",  # noqa
        "freq": {
            "hfxo": 40000000,
            "hfrco": 19000000,
            "lfxo": 32768,
            "lfrco": 32768,
            "ulfrco": 1000
        },
        "marketing_display_name": "EFM32 Pearl Gecko Starter Kit"
    },
    {
        "cpu": "efm32lg990f256",
        "cpu_datasheet": "https://www.silabs.com/Support%20Documents/TechnicalDocs/EFM32LG990.pdf",  # noqa
        "board": "stk3600",
        "board_display_name": "STK3600",
        "board_manual": "https://www.silabs.com/Support%20Documents/TechnicalDocs/efm32lg-stk3600-ug.pdf",  # noqa
        "board_schematic": "https://www.silabs.com/Support%20Documents/TechnicalDocs/BRD2201A_A02.pdf",  # noqa
        "family": "efm32lg",
        "family_display_name": "EFM32LG",
        "family_display_name_full": "EFM32 Leoppard Gecko",
        "family_manual": "https://www.silabs.com/Support%20Documents/TechnicalDocs/EFM32LG-RM.pdf",  # noqa
        "freq": {
            "hfxo": 48000000,
            "hfrco": 14000000,
            "lfxo": 32768,
            "lfrco": 32768,
            "ulfrco": 1000
        },
        "marketing_display_name": "EFM32 Leopard Gecko Starter Kit"
    },
    {
        "cpu": "efm32gg990f1024",
        "cpu_datasheet": "https://www.silabs.com/Support%20Documents/TechnicalDocs/EFM32GG990.pdf",  # noqa
        "board": "stk3700",
        "board_display_name": "STK3700",
        "board_manual": "https://www.silabs.com/Support%20Documents/TechnicalDocs/efm32gg-stk3700-ug.pdf",  # noqa
        "board_schematic": "https://www.silabs.com/Support%20Documents/TechnicalDocs/BRD2200A_A03.pdf",  # noqa
        "family": "efm32gg",
        "family_display_name": "EFM32GG",
        "family_display_name_full": "EFM32 Giant Gecko",
        "family_manual": "https://www.silabs.com/Support%20Documents/TechnicalDocs/EFM32GG-RM.pdf",  # noqa
        "freq": {
            "hfxo": 48000000,
            "hfrco": 14000000,
            "lfxo": 32768,
            "lfrco": 32768,
            "ulfrco": 1000
        },
        "marketing_display_name": "EFM32 Giant Gecko Starter Kit"
    },
    {
        "cpu": "efm32wg990f256",
        "cpu_datasheet": "http://www.silabs.com/Support%20Documents/TechnicalDocs/EFM32WG990.pdf",  # noqa
        "board": "stk3800",
        "board_display_name": "STK3800",
        "board_manual": "http://www.silabs.com/Support%20Documents/TechnicalDocs/efm32wg-stk3800-ug.pdf",  # noqa
        "board_schematic": "http://www.silabs.com/Support%20Documents/TechnicalDocs/BRD2400A_A00.pdf",  # noqa
        "family": "efm32wg",
        "family_display_name": "EFM32WG",
        "family_display_name_full": "EFM32 Wonder Gecko",
        "family_manual": "http://www.silabs.com/Support%20Documents/TechnicalDocs/EFM32WG-RM.pdf",  # noqa
        "freq": {
            "hfxo": 48000000,
            "hfrco": 14000000,
            "lfxo": 32768,
            "lfrco": 32768,
            "ulfrco": 1000
        },
        "marketing_display_name": "EFM32 Wonder Gecko Starter Kit"
    },
    {
        "cpu": "ezr32wg330f256r60",
        "cpu_datasheet": "https://www.silabs.com/Support%20Documents/TechnicalDocs/EZR32WG330_DataSheet.pdf",  # noqa
        "board": "slwstk6220a",
        "board_display_name": "SLWSTK6220A",
        "board_manual": "https://www.silabs.com/Support%20Documents/TechnicalDocs/wstk6220_EZR32WG_868MHz_Wireless_Starter_Kit.pdf",  # noqa
        "board_schematic": "http://www.silabs.com/Support%20Documents/TechnicalDocs/BRD2400A_A00.pdf",  # noqa
        "family": "ezr32wg",
        "family_display_name": "EZR32WG",
        "family_display_name_full": "EZR32 Wonder Gecko",
        "family_manual": "http://www.silabs.com/Support%20Documents/TechnicalDocs/EZR32LG-RM.pdf",  # noqa
        "freq": {
            "hfxo": 48000000,
            "hfrco": 14000000,
            "lfxo": 32768,
            "lfrco": 32768,
            "ulfrco": 1000
        },
        "marketing_display_name": "EZR32WG 868MHz Wireless Starter Kit"
    },
    {
        "cpu": "efr32mg1p132f256gm48",
        "cpu_datasheet": "https://www.silabs.com/Support%20Documents/TechnicalDocs/EFR32MG1-DataSheet.pdf",  # noqa
        "board": "sltb001a",
        "board_display_name": "SLTB001A",
        "board_manual": "",
        "board_schematic": "",
        "family": "efm32mg",
        "family_display_name": "EFR32MG",
        "family_display_name_full": "EFM32 Mighty Gecko Gecko",
        "family_manual": "http://www.silabs.com/Support%20Documents/TechnicalDocs/EFR32-ReferenceManual.pdf",  # noqa
        "freq": {
            "hfxo": 38400000,
            "hfrco": 14000000,
            "lfxo": 32768,
            "lfrco": 32768,
            "ulfrco": 1000
        },
        "marketing_display_name": "Thunderboard Sense"
    }
]

# Minimal RAM size.
MIN_RAM = 4096

# Minimal flash size.
MIN_FLASH = 8192
