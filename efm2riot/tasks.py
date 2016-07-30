from efm2riot import configuration, templates

import shutil
import glob
import sys
import os


def clean_dist(dist_directory):
    """
    Clean the output folder.
    """

    # Remove the old folder.
    shutil.rmtree(dist_directory, ignore_errors=True)

    # Create a new one
    os.mkdir(dist_directory)


def copy_static(root_directory, dist_directory, sdk_directory):
    """
    Copy all static files from source to target.
    """

    for static in configuration.STATICS:
        context = {
            "root": root_directory,
            "sdk": sdk_directory,
            "dist": dist_directory
        }

        source = templates.from_string(static["source"], context)
        target = templates.from_string(static["target"], context)
        target = os.path.join(dist_directory, target)

        # Perform the action.
        sys.stdout.write("Copying '%s'\n" % source)

        if static["type"] == "directory":
            recursive_overwrite(source, target)
        else:
            shutil.copy(source, target)


def copy_templates(root_directory, dist_directory, sdk_directory,
                   cpus, families, boards):
    """
    Copy all the templates.
    """

    def _process(when, contexts):
        for context in contexts:
            for template in configuration.TEMPLATES:
                if template["when"] == when:
                    context.update({
                        "root": root_directory,
                        "sdk": sdk_directory,
                        "dist": dist_directory
                    })

                    source = templates.from_string(template["source"], context)
                    target = templates.from_string(template["target"], context)
                    target = os.path.join(dist_directory, target)

                    # Compute filters
                    filters = {}

                    if "filters" in template:
                        for expression in template["filters"].iterkeys():
                            new_expression = templates.from_string(
                                expression, context)

                            filters[new_expression] = \
                                template["filters"][expression]

                    # Perform the action.
                    sys.stdout.write("Processing '%s'\n" % source)

                    if template["type"] == "file":
                        if source in filters:
                            if not filters[source](contexts):
                                sys.stdout.write("Filtered")
                                continue

                        templates.from_file(source, target, context)
                    elif template["type"] == "glob":
                        for source_file in glob.glob(source):
                            if os.path.isfile(source_file):
                                if source_file in filters:
                                    if not filters[source_file](context):
                                        sys.stdout.write("Filtered")
                                        continue

                                target_file = os.path.join(
                                    target, os.path.basename(source_file))

                                templates.from_file(
                                    source_file, target_file, context)
                    else:
                        raise Exception(
                            "Unsupported template: %s", template["type"])

    _process("per_family", families)
    _process("per_cpu", cpus)
    _process("per_board", boards)
    _process("once", [{
        "families": [family["family"] for family in families],
        "cpus": [cpu["cpu"] for cpu in cpus],
        "boards": [board["board"] for board in boards]
    }])


def copy_patches(root_directory, dist_directory, sdk_directory,
                 cpus, families, boards):
    """
    Copy all the patches.
    """

    def _process(when, contexts):
        for context in contexts:
            for patch in configuration.PATCHES:
                if patch["when"] == when:
                    context.update({
                        "root": root_directory,
                        "sdk": sdk_directory,
                        "dist": dist_directory
                    })

                    source = templates.from_string(patch["source"], context)
                    target = templates.from_string(patch["target"], context)
                    target = os.path.join(dist_directory, target)

                    # Perform the action.
                    sys.stdout.write("Patching '%s'\n" % source)

                    if patch["type"] == "file":
                        with open(source, "r") as fp:
                            content = fp.read()

                        for method in patch["methods"]:
                            content = method(source, content)

                        with open(target, "w") as fp:
                            fp.write(content)
                    elif patch["type"] == "glob":
                        for source_file in glob.glob(source):
                            if os.path.isfile(source_file):
                                target_file = os.path.join(
                                    target, os.path.basename(source_file))

                                with open(source_file, "r") as fp:
                                    content = fp.read()

                                for method in patch["methods"]:
                                    content = method(source, content)

                                with open(target_file, "w") as fp:
                                    fp.write(content)
                    else:
                        raise Exception("Not supported")

    _process("per_family", families)
    _process("per_cpu", cpus)
    _process("per_board", boards)
    _process("once", [{
        "families": [family["family"] for family in families],
        "cpus": [cpu["cpu"] for cpu in cpus],
        "boards": [board["board"] for board in boards]
    }])


def recursive_overwrite(source, target, ignore=None):
    """
    Wrapper for shutil.copytree that can merge source and target.
    """

    if os.path.isdir(source):
        if not os.path.isdir(target):
            os.makedirs(target)
        files = os.listdir(source)

        if ignore:
            ignored = ignore(source, files)
        else:
            ignored = set()

        for f in files:
            if f not in ignored:
                recursive_overwrite(
                    os.path.join(source, f), os.path.join(target, f), ignore)
    else:
        shutil.copyfile(source, target)
