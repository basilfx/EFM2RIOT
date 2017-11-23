from efm2riot import patches, filters

# Static copy actions (source, destination).
STATICS = [
    {
        "type": "directory",
        "source": "{{ root }}/static/cpu/efm32",
        "target": "cpu/efm32"
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
        "source": "{{ root }}/static/pkg/gecko_sdk",
        "target": "pkg/gecko_sdk"
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
        "when": "per_family",
        "source": "{{ root }}/templates/cpu/efm32/families/family/Makefile",
        "target": "cpu/efm32/families/{{ family }}/Makefile"
    },
    {
        "type": "file",
        "when": "per_family",
        "source": "{{ root }}/templates/cpu/efm32/families/family/vectors.c",
        "target": "cpu/efm32/families/{{ family }}/vectors.c"
    },
    {
        "type": "file",
        "when": "per_family",
        "source": "{{ root }}/templates/cpu/efm32/families/family/cpus.txt",
        "target": "cpu/efm32/families/{{ family }}/cpus.txt"
    },
    {
        "type": "glob",
        "when": "per_board",
        "source": "{{ root }}/templates/boards/board/dist/*",
        "target": "boards/{{ board }}/dist",
        "filters": {
            "{{ root }}/templates/boards/board/dist/board.resc": filters.only_for_development(),  # noqa
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
        "type": "file",
        "when": "per_board",
        "source": "{{ root }}/templates/doc/Board.md",
        "target": "doc/{{ board|upper }}.md",
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
    {
        "type": "file",
        "when": "per_board",
        "source": "{{ root }}/templates/contrib/renode/platforms/boards/board.repl",  # noqa
        "target": "contrib/renode/platforms/boards/{{ board }}.repl",
        "filters": {
            "{{ root }}/templates/contrib/renode/platforms/boards/board.repl": filters.only_for_development(),  # noqa
        }
    },
    {
        "type": "file",
        "when": "per_cpu",
        "source": "{{ root }}/templates/contrib/renode/platforms/cpus/cpu.repl",  # noqa
        "target": "contrib/renode/platforms/cpus/{{ cpu }}.repl",
        "filters": {
            "{{ root }}/templates/contrib/renode/platforms/cpus/cpu.repl": filters.only_for_development(),  # noqa
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
        "cpu": "efr32mg12p332f1024gl125",
        "cpu_datasheet": "https://www.silabs.com/documents/public/data-sheets/efr32mg12-datasheet.pdf",  # noqa
        "board": "brd4162a",
        "board_manual": "https://www.silabs.com/documents/public/reference-manuals/brd4162a-rm.pdf",  # noqa
        "board_schematic": "https://www.silabs.com/documents/public/reference-manuals/brd4162a-rm.pdf",  # noqa
        "family": "efr32mg12p",
        "family_full_name": "EFR32 Mighty Gecko 12P",
        "family_manual": "http://www.silabs.com/Support%20Documents/TechnicalDocs/EFR32-ReferenceManual.pdf",  # noqa
        "features": ["aem", "bc"],
        "freq": {
            "hfxo": 38400000,
            "hfrco": 19000000,
            "lfxo": 32768,
            "lfrco": 32768,
            "ulfrco": 1000
        },
        "marketing_name": "Mighty Gecko Radio Board"
    },
    {
        "cpu": "efm32pg1b200f256gm48",
        "cpu_datasheet": "https://www.silabs.com/Support%20Documents/TechnicalDocs/EFM32PG1-DataSheet.pdf",  # noqa
        "board": "slstk3401a",
        "board_manual": "https://www.silabs.com/documents/public/user-guides/ug154-stk3401-user-guide.pdf",  # noqa
        "board_schematic": "",
        "family": "efm32pg1b",
        "family_full_name": "EFM32 Pearl Gecko 1B",
        "family_manual": "https://www.silabs.com/Support%20Documents/TechnicalDocs/EFM32PG1-ReferenceManual.pdf",  # noqa
        "features": ["aem", "bc"],
        "freq": {
            "hfxo": 40000000,
            "hfrco": 19000000,
            "lfxo": 32768,
            "lfrco": 32768,
            "ulfrco": 1000
        },
        "marketing_name": "EFM32 Pearl Gecko PG1 Starter Kit"
    },
    {
        "cpu": "efm32pg12b500f1024gl125",
        "cpu_datasheet": "https://www.silabs.com/documents/public/data-sheets/efm32pg12-datasheet.pdf",  # noqa
        "board": "slstk3402a",
        "board_manual": "https://www.silabs.com/documents/public/user-guides/ug257-stk3402-usersguide.pdf",  # noqa
        "board_schematic": "",
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
        "marketing_name": "EFM32 Pearl Gecko PG12 Starter Kit"
    },
    {
        "cpu": "efm32gg11b820f2048gl192",
        "cpu_datasheet": "https://www.silabs.com/documents/public/data-sheets/efm32gg11-datasheet.pdf",  # noqa
        "board": "slstk3701a",
        "board_manual": "https://www.silabs.com/documents/public/user-guides/ug287-stk3701.pdf",  # noqa
        "board_schematic": "https://www.silabs.com/documents/public/schematic-files/BRD2204A-B00-schematic.pdf",
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
        "marketing_name": "EFM32 Giant Gecko GG11 Starter Kit"
    },
    {
        "cpu": "efr32mg1p132f256gm48",
        "cpu_datasheet": "https://www.silabs.com/Support%20Documents/TechnicalDocs/EFR32MG1-DataSheet.pdf",  # noqa
        "board": "sltb001a",
        "board_manual": "http://www.silabs.com/Support%20Documents/TechnicalDocs/UG250.pdf",  # noqa
        "board_schematic": "http://www.silabs.com/Support%20Documents/TechnicalDocs/UG250.pdf",  # noqa
        "family": "efr32mg1p",
        "family_full_name": "EFR32 Mighty Gecko 1P",
        "family_manual": "http://www.silabs.com/Support%20Documents/TechnicalDocs/EFR32-ReferenceManual.pdf",  # noqa
        "features": [],
        "freq": {
            "hfxo": 38400000,
            "hfrco": 19000000,
            "lfxo": 32768,
            "lfrco": 32768,
            "ulfrco": 1000
        },
        "marketing_name": "Thunderboard Sense"
    },
    {
        "cpu": "ezr32wg330f256r60",
        "cpu_datasheet": "https://www.silabs.com/Support%20Documents/TechnicalDocs/EZR32WG330_DataSheet.pdf",  # noqa
        "board": "slwstk6220a",
        "board_manual": "https://www.silabs.com/Support%20Documents/TechnicalDocs/wstk6220_EZR32WG_868MHz_Wireless_Starter_Kit.pdf",  # noqa
        "board_schematic": "http://www.silabs.com/Support%20Documents/TechnicalDocs/BRD2400A_A00.pdf",  # noqa
        "family": "ezr32wg",
        "family_full_name": "EZR32 Wonder Gecko",
        "family_manual": "http://www.silabs.com/Support%20Documents/TechnicalDocs/EZR32LG-RM.pdf",  # noqa
        "features": ["aem", "bc"],
        "freq": {
            "hfxo": 48000000,
            "hfrco": 14000000,
            "lfxo": 32768,
            "lfrco": 32768,
            "ulfrco": 1000
        },
        "marketing_name": "EZR32WG 868MHz Wireless Starter Kit"
    },
    {
        "cpu": "efm32zg222f32",
        "cpu_datasheet": "https://www.silabs.com/Support%20Documents/TechnicalDocs/EFM32ZG222.pdf",  # noqa
        "board": "stk3200",
        "board_manual": "https://www.silabs.com/Support%20Documents/TechnicalDocs/efm32zg-stk3200-ug.pdf",  # noqa
        "board_schematic": "https://www.silabs.com/Support%20Documents/TechnicalDocs/BRD2010A_B01.pdf",  # noqa
        "family_full_name": "EFM32 Zero Gecko",
        "family_manual": "https://www.silabs.com/Support%20Documents/TechnicalDocs/EFM32ZG-RM.pdf",  # noqa
        "features": ["aem", "bc"],
        "freq": {
            "hfxo": 24000000,
            "hfrco": 14000000,
            "lfxo": 32768,
            "lfrco": 32768,
            "ulfrco": 1000
        },
        "marketing_name": "EFM32 Zero Gecko Starter Kit"
    },
    {
        "cpu": "efm32lg990f256",
        "cpu_datasheet": "https://www.silabs.com/Support%20Documents/TechnicalDocs/EFM32LG990.pdf",  # noqa
        "board": "stk3600",
        "board_manual": "https://www.silabs.com/Support%20Documents/TechnicalDocs/efm32lg-stk3600-ug.pdf",  # noqa
        "board_schematic": "https://www.silabs.com/Support%20Documents/TechnicalDocs/BRD2201A_A02.pdf",  # noqa
        "family": "efm32lg",
        "family_full_name": "EFM32 Leoppard Gecko",
        "family_manual": "https://www.silabs.com/Support%20Documents/TechnicalDocs/EFM32LG-RM.pdf",  # noqa
        "features": ["aem", "bc"],
        "freq": {
            "hfxo": 48000000,
            "hfrco": 14000000,
            "lfxo": 32768,
            "lfrco": 32768,
            "ulfrco": 1000
        },
        "marketing_name": "EFM32 Leopard Gecko Starter Kit"
    },
    {
        "cpu": "efm32gg990f1024",
        "cpu_datasheet": "https://www.silabs.com/Support%20Documents/TechnicalDocs/EFM32GG990.pdf",  # noqa
        "board": "stk3700",
        "board_manual": "https://www.silabs.com/Support%20Documents/TechnicalDocs/efm32gg-stk3700-ug.pdf",  # noqa
        "board_schematic": "https://www.silabs.com/Support%20Documents/TechnicalDocs/BRD2200A_A03.pdf",  # noqa
        "family": "efm32gg",
        "family_full_name": "EFM32 Giant Gecko",
        "family_manual": "https://www.silabs.com/Support%20Documents/TechnicalDocs/EFM32GG-RM.pdf",  # noqa
        "features": ["aem", "bc"],
        "freq": {
            "hfxo": 48000000,
            "hfrco": 14000000,
            "lfxo": 32768,
            "lfrco": 32768,
            "ulfrco": 1000
        },
        "marketing_name": "EFM32 Giant Gecko Starter Kit"
    },
    {
        "cpu": "efm32wg990f256",
        "cpu_datasheet": "http://www.silabs.com/Support%20Documents/TechnicalDocs/EFM32WG990.pdf",  # noqa
        "board": "stk3800",
        "board_manual": "http://www.silabs.com/Support%20Documents/TechnicalDocs/efm32wg-stk3800-ug.pdf",  # noqa
        "board_schematic": "http://www.silabs.com/Support%20Documents/TechnicalDocs/BRD2400A_A00.pdf",  # noqa
        "family": "efm32wg",
        "family_full_name": "EFM32 Wonder Gecko",
        "family_manual": "http://www.silabs.com/Support%20Documents/TechnicalDocs/EFM32WG-RM.pdf",  # noqa
        "features": ["aem", "bc"],
        "freq": {
            "hfxo": 48000000,
            "hfrco": 14000000,
            "lfxo": 32768,
            "lfrco": 32768,
            "ulfrco": 1000
        },
        "marketing_name": "EFM32 Wonder Gecko Starter Kit"
    }
]
