from efm2riot import configuration, tasks, parsers

import argparse
import sys
import os


def parse_arguments():
    """
    Parse commandline arguments.
    """

    parser = argparse.ArgumentParser()

    # Add options
    parser.add_argument(
        "--sdk", action="store", help="path to EFM32 SDK")
    parser.add_argument(
        "--svds", action="store", help="path to EFM32 SVDs folder")
    parser.add_argument(
        "--dist", action="store", default="dist/", help="output folder")
    parser.add_argument(
        "--development", action="store_true", default=False,
        help="copy features under development")

    # Parse command line
    return parser.parse_args(), parser


def main(argv):
    """
    Prepare a the EFM32 port for RIOT-OS, given the EFM32 SDK.
    """

    # Parse command line arguments.
    arguments, parser = parse_arguments()

    root_directory = os.path.join(os.path.dirname(__file__), "efm2riot")
    dist_directory = arguments.dist
    sdk_directory = arguments.sdk
    svds_directory = arguments.svds

    # Start with a clean output directory.
    tasks.clean_dist(dist_directory)

    # Index all families.
    families = parsers.parse_families(sdk_directory)

    # Index all CPUs.
    cpus = []

    for family in families:
        cpus.extend(
            parsers.parse_cpus(
                sdk_directory,
                svds_directory,
                family,
                configuration.MIN_RAM,
                configuration.MIN_FLASH))

    sys.stdout.write(
        "Found %d CPUs in %d families (filtered).\n" % (
            len(cpus), len(families)))

    # Extend boards with families and CPUs.
    boards = []

    for board in configuration.BOARDS:
        for cpu in cpus:
            if cpu["cpu"] == board["cpu"]:
                board.update(cpu)
                boards.append(board)

                break
        else:
            raise Exception(
                "Unable to match CPU with board %s" % board["board"])

    # Copy static files.
    tasks.copy_static(
        root_directory, dist_directory, sdk_directory, arguments.development)

    # Process templates.
    tasks.copy_templates(
        root_directory, dist_directory, sdk_directory, cpus, families, boards,
        arguments.development)

    # Process patches.
    tasks.copy_patches(
        root_directory, dist_directory, sdk_directory, cpus, families, boards)


# E.g. `python3 EFM2RIOT.py --sdk /path/to/sdk --dist dist/'.
if __name__ == "__main__":
    sys.exit(main(sys.argv))
