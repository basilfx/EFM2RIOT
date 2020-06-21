from efm2riot import patches, filters

# Static copy actions (source, destination).
STATICS = [
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
        "marketing_name": "EFM32 Tiny Gecko 11 Starter Kit"
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
        "marketing_name": "EFM32 Pearl Gecko PG1 Starter Kit"
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
        "marketing_name": "EFM32 Pearl Gecko PG12 Starter Kit"
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
        "marketing_name": "EFM32 Giant Gecko GG11 Starter Kit"
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
        "marketing_name": "Thunderboard Sense"
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
        "marketing_name": "Mighty Gecko Wireless Starter Kit"
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
        "marketing_name": "EZR32WG 868MHz Wireless Starter Kit"
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
        "marketing_name": "EFM32 Zero Gecko Starter Kit"
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
        "marketing_name": "EFM32 Leopard Gecko Starter Kit"
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
        "marketing_name": "EFM32 Giant Gecko Starter Kit"
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
        "marketing_name": "EFM32 Wonder Gecko Starter Kit"
    }
]
