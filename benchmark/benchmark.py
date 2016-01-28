from pyparsing import Regex, Literal, ZeroOrMore, SkipTo, Group, \
    ParseException, StringEnd

import multiprocessing
import collections
import subprocess
import argparse
import json
import sys
import os

# GCC *.map file grammar for parsing code size per file
hex_word = Regex(r"0x[a-f0-9]+").setParseAction(lambda x: int(x[0], 16))

address = hex_word ^ Literal("[!provide]")
size = hex_word
meta = SkipTo(address ^ StringEnd()).setParseAction(lambda x: x[0].strip())

line_a = Group(address + size)
line_b = Group(address + size + meta) + ZeroOrMore(Group(address + meta))
line_c = Group(address + meta)

grammar = SkipTo(address ^ StringEnd()) + (
    line_a ^ line_b ^ line_c ^ StringEnd())


def parse_arguments():
    """
    Parse commandline arguments.
    """

    parser = argparse.ArgumentParser()

    # Add options
    parser.add_argument(
        "--riot", action="store", help="path to RIOT-OS", required=True)
    parser.add_argument(
        "--profile", action="store", help="profile file", required=True)
    parser.add_argument(
        "-o", "--output", action="store", help="path to output file",
        required=True)

    # Parse command line
    return parser.parse_args(), parser


def parse_map(map_file):
    """
    """

    sections = [
        "Preamble",
        "Allocating common symbols",
        "Discarded input sections",
        "Memory Configuration",
        "Linker script and memory map",
        "OUTPUT",
        "Cross Reference Table"
    ]
    current_section = None

    # Variables for section four
    in_segment = False
    current_segment = []

    # Counters
    text_segment = collections.defaultdict(int)
    data_segment = collections.defaultdict(int)
    bss_segment = collections.defaultdict(int)

    def parse_segment(segment):
        try:
            tokens = grammar.parseString(" ".join(segment))
        except ParseException as e:
            print e.markInputline("|")
            raise e

        if len(tokens) > 1:
            if tokens[0].startswith(".text"):
                if len(tokens[1]) == 3:
                    address, size, source_file = tokens[1]
                    source_file = source_file.split("(")[0]

                    text_segment[source_file] += size
            elif tokens[0].startswith(".data"):
                if len(tokens[1]) == 3:
                    address, size, source_file = tokens[1]
                    source_file = source_file.split("(")[0]

                    data_segment[source_file] += size
            elif tokens[0].startswith(".bss"):
                if len(tokens[1]) == 3:
                    address, size, source_file = tokens[1]
                    source_file = source_file.split("(")[0]

                    bss_segment[source_file] += size

    with open(map_file, "r") as fp:
        for line in fp:
            line = line.strip()

            if line in sections:
                current_section = sections.index(line)

                # Parse previous segment
                if current_segment:
                    parse_segment(current_segment)

            if current_section == 4:
                if line.startswith(".") or line.startswith("*"):
                    in_segment = True

                    # Parse previous segment
                    if current_segment:
                        parse_segment(current_segment)
                        current_segment = []

                # Add lines to segment
                if in_segment:
                    current_segment.append(line)

    return {
        "text": text_segment,
        "data": data_segment,
        "bss": bss_segment
    }


def compile_job(id, riot_directory, board, application, setting):
    """
    Compile one given setting.
    """

    failed = False
    result = {
        "id": id,
        "board": board,
        "application": application,
        "setting": setting,
    }
    arguments_a = [
        "make",
        "BOARD=%s" % board,
        "QUIET=1",
        "clean"
    ]
    arguments_b = [
        "make",
        "-j%d" % multiprocessing.cpu_count() / 2,
        "BOARD=%s" % board,
        "QUIET=1"
    ] + setting

    print arguments_b

    # Compile the job
    try:
        subprocess.check_output(
            arguments_a, cwd=os.path.join(riot_directory, application))
    except subprocess.CalledProcessError:
        failed = True

    if not failed:
        try:
            output = subprocess.check_output(
                arguments_b, cwd=os.path.join(riot_directory, application))
        except subprocess.CalledProcessError:
            failed = True

    # Extract information
    if not failed:
        sizes = map(str.strip, output.split("\n")[-2].split("\t"))
        segments = parse_map(sizes[5].replace(".elf", ".map"))

        result.update({
            "failed": False,
            "text": sizes[0],
            "data": sizes[1],
            "bss": sizes[2],
            "dec":  sizes[3],
            "segments": segments
        })
    else:
        result.update({
            "failed": True
        })

    return result


def main():
    """
    Run all applications for all boards using all settings.
    """

    # Parse command line arguments.
    arguments, parser = parse_arguments()

    # Import profile file.
    profile = {}
    execfile(arguments.profile, profile)

    # Prepare all jobs.
    jobs = []

    for board in profile["BOARDS"]:
        for application in profile["APPLICATIONS"]:
            for setting in profile["SETTINGS"]:
                jobs.append((
                    arguments.riot,
                    board,
                    application,
                    setting
                ))

    # Run all jobs. This is not done in parallel, because the compile script
    # will occupy all cores.
    results = []

    for index, job in enumerate(jobs, start=1):
        sys.stdout.write("Compiling job %d of %d\n" % (index, len(jobs)))

        try:
            results.append(compile_job(index, *job))
        except KeyboardInterrupt:
            sys.stdout.write("Compilation interrupted, saving results.\n")
            break

    # Write results to file
    with open(arguments.output, "w") as fp:
        json.dump(results, fp, indent=4)

    # Done
    sys.stdout.write("Done!\n")

if __name__ == "__main__":
    sys.exit(main())
