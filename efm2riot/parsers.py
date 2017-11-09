from cmsis_svd.parser import SVDParser

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
            "family_display_name": family.upper(),
            "device_info": parse_device_info(sdk_directory, family)
        })

    return families

def parse_device_info(sdk_directory, family):
    """
    Parse device information from the *_devinfo.h file. It contains information
    needed for Renode.
    """

    re_reserved = re.compile(r"\[(\d+)\]")
    re_comment = re.compile(r"\/\*\*< (.+) \*\/")
    re_family_id_hex = re.compile(r"(0x[a-fA-F0-9]+)UL")
    re_family_id_dec = re.compile(r"   ([0-9]+)")

    header_file = os.path.join(sdk_directory,
        f"Device/SiliconLabs/{family}/Include", f"{family}_devinfo.h")

    skip = 0
    read = False

    # Parse the file and find lines.
    family_id = 0
    register_lines = []

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

            # Family ID parsing.
            elif f"#define _DEVINFO_PART_DEVICE_FAMILY_{family.upper()}" in line:
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


def parse_cpus(sdk_directory, svds_directory, family,
               min_ram_size, min_flash_size):
    """
    Index all available CPUs of a family. Parse the source files and for the
    information needed.
    """

    re_hex = re.compile(r".*(0x[a-fA-F0-9]+).*")
    re_irq = re.compile(r"\s*([a-zA-Z0-9_]+)\s* = (-?\d+).*")

    cpus = []

    includes = glob.glob(os.path.join(
        sdk_directory,
        "Device/SiliconLabs/%(family)s/Include/*.h" % family))

    for include in includes:
        # Only looking for device header files.
        if "_" in os.path.basename(include):
            continue

        cpu_platform = None
        flash_size = None
        ram_size = None
        architecture = None
        crypto = False
        trng = False
        mpu = False
        fpu = False
        irqs = {}
        max_irq = None
        devinfo_base = None

        in_irq = False

        with open(include, "r") as fp:
            for line in fp:
                if "#define" in line:
                    if "FLASH_SIZE" in line:
                        flash_size = int(re_hex.match(line).group(1), 16)
                    elif "SRAM_SIZE" in line:
                        ram_size = int(re_hex.match(line).group(1), 16)
                    elif "_SILICON_LABS_32B_SERIES_0" in line:
                        cpu_platform = 1
                    elif "_SILICON_LABS_32B_SERIES_1" in line:
                        cpu_platform = 2
                    elif "CRYPTO_PRESENT" in line:
                        crypto = True
                    elif "TRNG_PRESENT" in line:
                        trng = True
                    elif "__MPU_PRESENT" in line and "1" in line:
                        mpu = True
                    elif "__FPU_PRESENT" in line and "1" in line:
                        fpu = True
                    elif "DEVINFO_BASE" in line and "0x" in line:
                        devinfo_base = int(re_hex.match(line).group(1), 16)

                elif "Cortex-M4" in line:
                    architecture = "m4"
                elif "Cortex-M3" in line:
                    architecture = "m3"
                elif "Cortex-M0+" in line:
                    architecture = "m0plus"
                elif "Cortex-M0" in line:
                    architecture = "m0"
                elif "typedef enum IRQn" in line:
                    in_irq = True
                elif "} IRQn_Type;" in line:
                    in_irq = False

                if in_irq:
                    irq = re_irq.match(line)

                    if irq:
                        irqs[int(irq.group(2))] = irq.group(1)
                        max_irq = int(irq.group(2))

        if not flash_size or not ram_size:
            raise Exception("Missing flash/ram size in include %s" % include)

        # Fix the IRQ to be a full list
        irq_table = []

        for number in range(max_irq + 1):
            if number in irqs:
                irq_name = irqs[number]

                name = irq_name.replace("_IRQn", "")
                method_name = "isr_" + name.lower()

                irq_table.append({
                    "irq_name": irq_name,
                    "method_name": method_name,
                    "name": name,
                    "number": number,
                    "reserved": False
                })
            else:
                irq_table.append({
                    "number": number,
                    "reserved": True
                })

        if ram_size >= min_ram_size and flash_size >= min_flash_size:
            cpu_name = os.path.basename(include).split(".")[0]

            cpu = {
                "cpu": cpu_name,
                "cpu_platform": cpu_platform,
                "flash_size": flash_size,
                "ram_size": ram_size,
                "crypto": crypto,
                "trng": trng,
                "fpu": fpu,
                "mpu": mpu,
                "devinfo_base": devinfo_base,
                "peripherals": parse_svd(
                    svds_directory, family["family"], cpu_name),
            }

            # Sanity checks: CPUs in same family must have the same
            # characteristics.
            if "architecture" in family:
                if family["architecture"] != architecture:
                    raise Exception("Architecture changed.")

            # IRQ maps of all CPUs must be merged, since a single CPU may not
            # have all IRQs mapped.
            if "irqs" in family:
                other_irq_table = {}

                for irq in (irq_table + family["irqs"]):
                    if irq["number"] not in other_irq_table:
                        other_irq_table[irq["number"]] = irq

                    if other_irq_table[irq["number"]]["reserved"] and not \
                            irq["reserved"]:
                        other_irq_table[irq["number"]] = irq

                irq_table = sorted(
                    other_irq_table.values(), key=lambda irq: irq["number"])

            family.update({
                "architecture": architecture,
                "irqs": irq_table,
            })

            cpu.update(family)
            cpus.append(cpu)

    return cpus


def parse_svd(svds_directory, family, cpu):
    """
    Parse the SVD files (if available) and return the peripherals.

    The data is returned lazy, to speedup the parsing process.
    """

    def _lazy():
        if not svds_directory:
            return

        svd_file = os.path.join(
            svds_directory, family.upper(), "%s.svd" % (cpu.upper()))

        if not os.path.isfile(svd_file):
            return

        parser = SVDParser.for_xml_file(svd_file)

        return parser.get_device().to_dict()["peripherals"]

    return _lazy
