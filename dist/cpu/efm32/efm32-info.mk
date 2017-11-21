EFM32_HEADER = $(RIOTCPU)/efm32/families/$(CPU)/include/vendor/$(CPU_MODEL).h

# Series for compiling specific peripherals.
EFM32_SERIES = $(shell grep '_SILICON_LABS_32B_SERIES' $(EFM32_HEADER))

# Flash and SRAM size for linker script.
EFM32_FLASH_BASE = $(shell grep 'FLASH_BASE' $(EFM32_HEADER) | awk -F"[()]" '{print $2}' | sed -e 's/UL//')
EFM32_FLASH_SIZE = $(shell grep 'FLASH_SIZE' $(EFM32_HEADER) | awk -F"[()]" '{print $2}' | sed -e 's/UL//')
EFM32_SRAM_BASE = $(shell grep 'FLASH_SRAM_BASE' $(EFM32_HEADER) | awk -F"[()]" '{print $2}' | sed -e 's/UL//')
EFM32_SRAM_SIZE = $(shell grep 'FLASH_SRAM_SIZE' $(EFM32_HEADER) | awk -F"[()]" '{print $2}' | sed -e 's/UL//')

# Peripherals for dependencies.
EFM32_TRNG_PRESENT = $(shell grep 'TRNG_COUNT' $(EFM32_HEADER) | awk -F"[()]" '{print $2}')
