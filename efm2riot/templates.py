from jinja2 import Environment, FileSystemLoader, StrictUndefined, nodes
from jinja2.ext import Extension

import os
import re


class AlignWithExtension(Extension):
    tags = ["align_with"]

    def parse(self, parser):
        """
        Parse an `align_with` block.
        """

        lineno = next(parser.stream).lineno

        # Parse arguments. First argument is the character to align with.
        args = [parser.parse_expression()]

        # Parse until end of block.
        body = parser.parse_statements(
            ["name:end" + self.tags[0]], drop_needle=True)

        # Return a `CallBlock` that will call the reindent method.
        return nodes.CallBlock(
            self.call_method("align_with", args), [], [], body
        ).set_lineno(lineno)

    def align_with(self, character, caller):
        """
        Helper method that aligns each line.
        """

        lines = []
        longest = 0

        for line in caller().split("\n"):
            if not line:
                continue

            parts = line.split(character, 1)

            if len(parts) != 2:
                print(parts)
                raise Exception(
                    f"Line does not contain split character '{character}'.")

            longest = max(longest, len(parts[0]))

            lines.append(parts)

        # Align all lines.
        data = ""

        for line in lines:
            extended = line[0] + (" " * (longest - len(line[0])))

            data += extended + character + line[1] + "\n"

        return data


class StripExtension(Extension):
    tags = ["strip"]

    def parse(self, parser):
        """
        Parse a `strip` block.
        """

        lineno = next(parser.stream).lineno

        # Parse arguments. First argument is number of indents, second is the
        # number of space indents.
        args = [parser.parse_expression()]

        # Newlines argument.
        if parser.stream.skip_if("comma"):
            args.append(nodes.Const(parser.parse_expression().value))
        else:
            args.append(nodes.Const(False))

        # Width argument.
        if parser.stream.skip_if("comma"):
            args.append(nodes.Const(parser.parse_expression().value))
        else:
            args.append(nodes.Const(False))

        # Parse until end of block.
        body = parser.parse_statements(
            ["name:end" + self.tags[0]], drop_needle=True)

        # Return a `CallBlock` that will call the reindent method.
        return nodes.CallBlock(
            self.call_method("strip", args), [], [], body
        ).set_lineno(lineno)

    def strip(self, count, newlines, width, caller):
        """
        Helper method that reindent each line.
        """

        if not width:
            width = 4

        lines = []
        to_strip = " " * width * count

        for line in caller().split("\n"):
            if line[:len(to_strip)] == to_strip:
                line = line[len(to_strip):]

            lines.append(line)

        # Re-join all lines.
        data = "\n".join(lines)

        # The strip block can add special markers to remove redundant newlines.
        # They are removed in an additional pass. Not the best solution, but
        # one that works.
        if newlines is True:
            newlines = ">"

        if not data:
            if newlines:
                if "<" in newlines:
                    data = data + "{{##<<##}}"
                if ">" in newlines:
                    data = data + "{{##>>##}}"

        return data


def create_environment():
    """
    Create a new Jinja2 render environment.
    """

    def _align(value, align):
        return ("%-" + str(align) + "s") % value

    def _ralign(value, align):
        return ("%" + str(align) + "s") % value

    def _hex(value, align=None):
        if align:
            return ("0x%0" + str(align) + "x") % value
        else:
            return ("0x%x" % value)

    def _freq(freq):
        if freq > 1000000 and freq % 1000000 == 0:
            return "%d MHz" % (freq / 1000000)
        elif freq > 1000000:
            return "%.1f MHz" % (freq / 1000000.0)
        else:
            return "%.3f kHz" % (freq / 1000.0)

    def _search(value, regex):
        return re.search(regex, value).groups()

    def _match(value, regex):
        return re.match(regex, value).groups()

    def _select(source, **attributes):
        result = []

        for item in source:
            for key, value in attributes.items():
                if not re.match(value, item[key]):
                    break
            else:
                result.append(item)

        return result

    def _find(source, **attributes):
        for item in source:
            for key, value in attributes.items():
                if item[key] != value:
                    break
            else:
                return item

    root_dir = os.path.join(os.path.dirname(__file__), "..")
    file_dir = os.path.abspath(os.path.dirname(__file__))
    environment = Environment(
        loader=FileSystemLoader([root_dir, file_dir, "/"]),
        undefined=StrictUndefined,
        extensions=[AlignWithExtension, StripExtension],
        lstrip_blocks=True,
        trim_blocks=True,
        keep_trailing_newline=True)

    environment.filters["align"] = _align
    environment.filters["ralign"] = _ralign
    environment.filters["hex"] = _hex
    environment.filters["freq"] = _freq
    environment.filters["search"] = _search
    environment.filters["match"] = _match
    environment.filters["select"] = _select
    environment.filters["find"] = _find

    return environment


def from_file(input_file, output_file, context):
    """
    Render the input_file for a given context and store it to output file.

    Additionally, patches (callbacks that accept a filename and source) can be
    applied.
    """

    output = create_environment().get_template(input_file).render(**context)

    # Whitespace control (see strip extension).
    output = output.replace("\n{{##<<##}}", "")
    output = output.replace("{{##>>##}}\n", "")
    output = output.replace("{{##<<##}}", "")
    output = output.replace("{{##>>##}}", "")

    # Save output
    if not os.path.isdir(os.path.dirname(output_file)):
        os.makedirs(os.path.dirname(output_file))

    with open(output_file, "wb") as fp:
        fp.write(output.encode("utf-8"))


def from_string(input_string, context):
    """
    Render a input_string for a given context. Return the output.
    """

    output = create_environment().from_string(input_string).render(**context)

    # Whitespace control (see strip extension).
    output = output.replace("\n{{##<<##}}", "")
    output = output.replace("{{##>>##}}\n", "")
    output = output.replace("{{##<<##}}", "")
    output = output.replace("{{##>>##}}", "")

    return output
