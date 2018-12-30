EXTERN_START = "\n#ifdef __cplusplus\nextern \"C\" {\n#endif\n\n"
EXTERN_STOP = "#ifdef __cplusplus\n}\n#endif\n\n"

EXTERN_FIND1 = "extern \"C\" {\n"
EXTERN_FIND2A = " ******************************************************************************/\n"  # noqa
EXTERN_FIND2B = " *****************************************************************************/\n"  # noqa


def add_extern_c(source_file, source):
    """
    Add 'Extern C' to a given source_file.
    """

    # Patches only work with newline versions of the file.
    if "\r\n" in source:
        raise Exception(
            "You need to convert all Gecko SDK sources to Linux file endings "
            "first (use something like dos2unix).")

    # Don't add it if file already contains it.
    if EXTERN_FIND1 in source:
        return source

    # Dirty hack by looking for a string, but it works.
    if EXTERN_FIND2A in source:
        offset = source.index(EXTERN_FIND2A) + len(EXTERN_FIND2A)
    elif EXTERN_FIND2B in source:
        offset = source.index(EXTERN_FIND2B) + len(EXTERN_FIND2B)
    else:
        raise Exception("Unable to find the marker in '%s'." % source_file)

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
        "#ifndef ARM_MATH_CM0PLUS\n#define ARM_MATH_CM0PLUS\n#endif")
