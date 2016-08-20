EXTERN_START = "\r\n#ifdef __cplusplus\r\nextern \"C\" {\r\n#endif\r\n\r\n"
EXTERN_STOP = "#ifdef __cplusplus\r\n}\r\n#endif\r\n\r\n"

EXTERN_FIND1 = "extern \"C\" {\r\n"
EXTERN_FIND2 = " *****************************************************************************/\r\n"  # noqa


def add_extern_c(source_file, source):
    """
    Add 'Extern C' to a given source_file.
    """

    # Don't add it if file already contains it.
    if EXTERN_FIND1 in source:
        return source

    # Dirty hack by looking for a string, but it works.
    offset = source.index(EXTERN_FIND2) + len(EXTERN_FIND2)

    part_one = source[:offset]
    part_two = source[offset:]

    return part_one + EXTERN_START + part_two + EXTERN_STOP


def fix_arm_math(source_file, source):
    """
    Add conditional for ARM_MATH_CM definition. It is already defined by the
    Cortex definitions of RIOT-OS.
    """

    return source.replace(
        "#define ARM_MATH_CM0PLUS",
        "#ifndef ARM_MATH_CM0PLUS\r\n#define ARM_MATH_CM0PLUS\r\n#endif")
