from cmsis_svd.parser import SVDParser

import hashlib
import json
import glob
import os
import re


def parse_families(sdk_directory):
    """
    Index all available families from the SDK.
    """

    if not os.path.isdir(os.path.join(sdk_directory, "Device/SiliconLabs")):
        raise Exception(
            "Specified SDK directory does not contain 'Device/' folder.")

    folders = glob.glob(os.path.join(sdk_directory, "Device/SiliconLabs/*"))
    families = []

    for folder in folders:
        if not os.path.isdir(folder):
            continue

        family = os.path.basename(folder)

        # In SDK v5.1.2 additional devices are included which are incomplete.
        # All interesting devices start with EFM32, EFR32 or EZR32.
        if family.upper()[:3] not in ["EFM", "EFR", "EZR"]:
            continue

        families.append({
            "family": family.lower(),
            "family_base": family.lower().split("32", 1)[0] + "32",
            "family|upper": family.upper(),
            "devinfo": parse_device_info(sdk_directory, family),
            "irqs": parse_device_irqs(sdk_directory, family),
        })

    return sorted(families, key=lambda family: family["family"])


def parse_device_irqs(sdk_directory, family):
    """
    Parse IRQ table for the given family. This includes additional vectors
    used by the radio drivers for EZR32 microcontrollers.
    """

    re_irq = re.compile(
        r"^\s+DCD\s+([a-zA-Z0-9_]+_IRQHandler)\s+;\s+(\d+):\s+(.*)$")

    startup_file = os.path.join(
        sdk_directory,
        f"Device/SiliconLabs/{family.upper()}/Source/ARM/",
        f"startup_{family.lower()}.s")

    irq_table = []

    with open(startup_file, "r") as fp:
        for line in fp:
            if "DCD" not in line:
                continue

            # Match the line.
            matches = re_irq.match(line)

            if matches:
                irq_name = matches.group(1)
                number = matches.group(2)
                description = matches.group(3)

                name = irq_name.replace("_IRQHandler", "")
                method_name = "isr_" + name.lower()

                irq_table.append({
                    "irq_name": irq_name,
                    "method_name": method_name,
                    "name": name,
                    "description": description,
                    "number": int(number),
                })

    return sorted(irq_table, key=lambda x: x["number"])


def parse_device_info(sdk_directory, family):
    """
    Parse device information from the *_devinfo.h file. It contains information
    needed for Renode.
    """

    re_reserved = re.compile(r"\[(\d+)\]")
    re_comment = re.compile(r"\/\*\*< (.+) \*\/")
    re_family_id_hex = re.compile(r"(0x[a-fA-F0-9]+)UL")
    re_family_id_dec = re.compile(r"   ([0-9]+)")

    header_file = os.path.join(
        sdk_directory,
        f"Device/SiliconLabs/{family.upper()}/Include",
        f"{family.lower()}_devinfo.h")

    skip = 0
    read = False

    # Parse the file and find lines.
    family_id = 0
    register_lines = []

    search_key = f"#define _DEVINFO_PART_DEVICE_FAMILY_{family.upper()}"

    with open(header_file, "r") as fp:
        for line in fp:
            # Skip lines if requested.
            if skip:
                skip = skip - 1
                continue

            # Register parsing
            elif "typedef struct" in line:
                skip = 1
                read = True
            elif "} DEVINFO_TypeDef" in line:
                read = False
            elif read:
                register_lines.append(line.strip())

            # Family ID parsing (there are two notations).
            elif search_key in line:
                try:
                    family_id = int(
                        re_family_id_hex.search(line).group(1), 16)
                except Exception:
                    family_id = int(
                        re_family_id_dec.search(line).group(1))

    # Parse the data.
    registers = []
    offset = 0

    for register_line in register_lines:
        if not register_line:
            continue

        if "uint32_t" not in register_line:
            raise Exception("Missing size (expected uint32_t).")

        if "RESERVED" in register_line:
            if "[" in register_line and "]" in register_line:
                offset += int(
                    re_reserved.search(register_line).group(1)) * 4
            else:
                offset += 4
        else:
            registers.append({
                "name": register_line.split(";")[0].split(" ")[-1],
                "description": re_comment.search(
                    register_line).group(1),
                "offset": offset
            })

            offset += 4

    return {
        "registers": registers,
        "family_id": family_id,
        "size": offset + 4,
    }


def parse_cpus(sdk_directory, svds_directory, family):
    """
    Index all available CPUs of a family. Parse the source files and for the
    information needed.

    Some of the information is generic to the whole family, but cannot be
    parsed otherwise.
    """

    re_hex = re.compile(r".*(0x[a-fA-F0-9]+).*")
    re_irq = re.compile(r"\s*([a-zA-Z0-9_]+)\s* = (-?\d+).*")

    cpus = []

    includes = glob.glob(os.path.join(
        sdk_directory,
        "Device/SiliconLabs/%s/Include/*.h" % family["family"].upper()))

    for include in includes:
        # Only looking for device header files.
        if "_" in os.path.basename(include):
            continue

        cpu_series = None
        flash_base = None
        flash_size = None
        sram_base = None
        sram_size = None
        architecture = None
        architecture_short = None
        crypto = False
        radio = False
        trng = False
        mpu = False
        fpu = False
        devinfo_base = None
        devinfo_size = None

        with open(include, "r") as fp:
            for line in fp:
                if "#define" in line:
                    if "FLASH_BASE" in line:
                        flash_base = int(re_hex.match(line).group(1), 16)
                    elif "FLASH_SIZE" in line:
                        flash_size = int(re_hex.match(line).group(1), 16)
                    elif "SRAM_BASE" in line:
                        sram_base = int(re_hex.match(line).group(1), 16)
                    elif "SRAM_SIZE" in line:
                        sram_size = int(re_hex.match(line).group(1), 16)
                    elif "_SILICON_LABS_32B_SERIES_0" in line:
                        cpu_series = 0
                    elif "_SILICON_LABS_32B_SERIES_1" in line:
                        cpu_series = 1
                    elif "_SILICON_LABS_32B_SERIES_2" in line:
                        cpu_series = 2
                    elif "CRYPTO_PRESENT" in line:
                        crypto = True
                    elif "TRNG_PRESENT" in line:
                        trng = True
                    elif "_SILICON_LABS_EFR32_RADIO_TYPE" in line:
                        radio = True
                    elif "__MPU_PRESENT" in line and "1" in line:
                        mpu = True
                    elif "__FPU_PRESENT" in line and "1" in line:
                        fpu = True
                    elif "DEVINFO_BASE" in line and "0x" in line:
                        devinfo_base = int(re_hex.match(line).group(1), 16)

                elif "Cortex-M4" in line:
                    architecture = "m4"
                    architecture_short = "m4"
                elif "Cortex-M3" in line:
                    architecture = "m3"
                    architecture_short = "m3"
                elif "Cortex-M0+" in line:
                    architecture = "m0plus"
                    architecture_short = "m0+"
                elif "Cortex-M0" in line:
                    architecture = "m0"
                    architecture_short = "m0"

        if not flash_size or not sram_size:
            raise Exception("Missing flash/ram size in include %s" % include)

        cpu_name = os.path.basename(include).split(".")[0]

        cpu = {
            "cpu": cpu_name,
            "flash_base": flash_base,
            "flash_size": flash_size,
            "sram_base": sram_base,
            "sram_size": sram_size,
            "devinfo_base": devinfo_base,
            "devinfo_size": devinfo_size,
            "peripherals": parse_svd(
                svds_directory, family["family"], cpu_name),
        }

        # Sanity checks: CPUs in same family must have the same
        # characteristics.
        check = ["fpu", "mpu", "architecture", "cpu_series"]

        for key in check:
            if key in family:
                if family[key] != locals()[key]:
                    raise Exception(
                        f"Sanity check failed: "
                        f"{key} changed within the same family.")

        family.update({
            "fpu": fpu,
            "mpu": mpu,
            "architecture": architecture,
            "architecture_short": architecture_short,
            "cpu_series": cpu_series,
            "crypto": crypto,
            "trng": trng,
            "radio": radio,
        })

        cpu.update(family)
        cpus.append(cpu)

    return sorted(cpus, key=lambda cpu: cpu["cpu"])


def parse_svd(svds_directory, family, cpu):
    """
    Parse the SVD files (if available) and return the peripherals.

    The data is returned from cache if available, to speedup the parsing
    process.
    """

    if not svds_directory:
        return []

    svd_file = os.path.join(
        svds_directory, family.upper(), "%s.svd" % (cpu.upper()))
    cache_key = hashlib.md5(svd_file.encode("ascii")).hexdigest()
    cache_file = os.path.join("cache", cache_key)

    if not os.path.isfile(svd_file):
        return []

    if not os.path.isfile(cache_file):
        device = SVDParser.for_xml_file(svd_file).get_device()

        with open(cache_file, "w") as fp:
            json.dump([
                peripheral.to_dict() for peripheral in device.peripherals
            ], fp)

    with open(cache_file, "r") as fp:
        return json.load(fp)
