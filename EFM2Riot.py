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
        "--dist", action="store", default="dist/", help="output folder")

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

    # Start with a clean output directory.
    tasks.clean_dist(dist_directory)

    # Index all families.
    families = parsers.parse_families(sdk_directory)

    # Index all CPUs.
    cpus = []

    for family in families:
        cpus.extend(parsers.parse_cpus(sdk_directory, family))

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
    tasks.copy_static(root_directory, dist_directory, sdk_directory)

    # Process templates.
    tasks.copy_templates(
        root_directory, dist_directory, sdk_directory, cpus, families, boards)

    # Process patches.
    tasks.copy_patches(
        root_directory, dist_directory, sdk_directory, cpus, families, boards)

# E.g. `python EFM2Riot.py --sdk /path/to/sdk --dist dist/'.
if __name__ == "__main__":
    sys.exit(main(sys.argv))
