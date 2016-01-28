EXTERN_START = """#ifdef __cplusplus
extern "C" {
#endif
"""

EXTERN_STOP = """#ifdef __cplusplus
}
#endif
"""

EXTERN_FIND1 = """extern "C" {"""

EXTERN_FIND2 = " *****************************************************************************/"  # noqa


def add_extern_c(source_file, source):
    """
    Add 'Extern C' to a given source_file.
    """

    if EXTERN_FIND1 in source:
        return source

    # Dirty hack by looking for a string, but it works.
    offset = source.index(EXTERN_FIND2) + len(EXTERN_FIND2) + 1

    part_one = source[:offset]
    part_two = source[offset:]

    return part_one + EXTERN_START + part_two + EXTERN_STOP


def fix_arm_math(source_file, source):
    """
    Add conditional for ARM_MATH_CM define. It is already defined by the
    Cortex definitions in RIOT-OS.
    """

    return source.replace(
        "#define ARM_MATH_CM0PLUS",
        "#ifndef ARM_MATH_CM0PLUS\n#define ARM_MATH_CM0PLUS\n#endif")


def fix_idac_c(source_file, source):
    """
    Fix for unitialized variables in em_idac.c.
    """

    if "em_idac.c" in source_file:
        source = source.replace("uint32_t diCal0;", "uint32_t diCal0 = 0;")
        source = source.replace("uint32_t diCal1;", "uint32_t diCal1 = 0;")

    return source
