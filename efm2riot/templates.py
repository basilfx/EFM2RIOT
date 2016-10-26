from jinja2 import Environment, FileSystemLoader, StrictUndefined, nodes
from jinja2.ext import Extension

import os


class StripExtension(Extension):
    tags = ["strip"]

    def parse(self, parser):
        """
        Parse the strip block.
        """

        lineno = next(parser.stream).lineno

        # Parse arguments. First argument is number of indents, second is the
        # number of space indents.
        args = [parser.parse_expression()]

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

    def strip(self, count, newlines, caller):
        """
        Helper method that reindent each line.
        """

        lines = []
        to_strip = "    " * count

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

    def _to_freq(freq):
        if freq > 1000000 and freq % 1000000 == 0:
            return "%d MHz" % (freq / 1000000)
        elif freq > 1000000:
            return "%.1f MHz" % (freq / 1000000.0)
        else:
            return "%.3f kHz" % (freq / 1000.0)

    root_dir = os.path.join(os.path.dirname(__file__), "..")
    file_dir = os.path.abspath(os.path.dirname(__file__))
    environment = Environment(
        loader=FileSystemLoader([root_dir, file_dir, "/"]),
        undefined=StrictUndefined,
        extensions=[StripExtension],
        lstrip_blocks=True,
        trim_blocks=True,
        keep_trailing_newline=True)

    environment.filters["align"] = lambda x, y: ("%-" + str(y) + "s") % x
    environment.filters["to_kb"] = lambda x: str(int(x) / 1024)
    environment.filters["to_freq"] = _to_freq

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

    with open(output_file, "w") as fp:
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
