from jinja2 import Environment, FileSystemLoader, StrictUndefined, nodes
from jinja2.ext import Extension
from jinja2.lexer import Token

import os


class StripExtension(Extension):
    tags = ["strip"]

    def parse(self, parser):
        """
        Parse the strip block.
        """

        lineno = next(parser.stream).lineno

        # Parse arguments. First argument is number of indents, second is the
        # indent string (optional, defaults to "    ").
        args = [parser.parse_expression()]

        if parser.stream.skip_if("comma"):
            strip_next_newline = parser.parse_expression().value
        else:
            strip_next_newline = False

        # Parse until end of block.
        body = parser.parse_statements(
            ["name:end" + self.tags[0]], drop_needle=True)

        # If strip_next_newline, remove the first newline of next token so it
        # doesn't leave two empty lines.
        if strip_next_newline:
            while True:
                token = parser.stream.next()

                if token.type == "data":
                    if token.value.startswith("\n") and token.value[1:]:
                        args.append(nodes.Const(True))
                        parser.stream.push(
                            Token(token.lineno, token.type, token.value[1:]))
                    else:
                        args.append(nodes.Const(False))

                    # Continue to first data block only.
                    break
                parser.stream.push(token)
        else:
            args.append(nodes.Const(False))

        # Return a `CallBlock` that will call the reindent method.
        return nodes.CallBlock(
            self.call_method("strip", args), [], [], body
        ).set_lineno(lineno)

    def strip(self, count, add_newline_on_data, caller):
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

        # Add extra newline if there is data. The parser has removed the next
        # whiteline in advance, so that we do not generat two empty lines.
        if add_newline_on_data and data:
            data = data + "\n"

        return data


def create_environment():
    """
    Create a new Jinja2 render environment.
    """

    root_dir = os.path.join(os.path.dirname(__file__), "..")
    file_dir = os.path.abspath(os.path.dirname(__file__))
    environment = Environment(
        loader=FileSystemLoader([root_dir, file_dir, "/"]),
        undefined=StrictUndefined,
        extensions=[StripExtension],
        lstrip_blocks=True,
        trim_blocks=True)

    environment.filters["align"] = lambda x, y: ("%-" + str(y) + "s") % x
    environment.filters["to_kb"] = lambda x: str(int(x) / 1024)
    environment.filters["to_freq"] = lambda x: \
        ("%d MHz" % (x / 1000000)) if x > 1000000 else \
        ("%.3f kHz" % (x / 1000.0))

    return environment


def from_file(input_file, output_file, context):
    """
    Render the input_file for a given context and store it to output file.

    Additionally, patches (callbacks that accept a filename and source) can be
    applied.
    """

    output = create_environment().get_template(input_file).render(**context)

    # Save output
    if not os.path.isdir(os.path.dirname(output_file)):
        os.makedirs(os.path.dirname(output_file))

    with open(output_file, "w") as fp:
        fp.write(output.encode("utf-8"))


def from_string(input_string, context):
    """
    Render a input_string for a given context. Return the output.
    """

    return create_environment().from_string(input_string).render(**context)
