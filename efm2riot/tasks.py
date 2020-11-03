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
    os.makedirs(dist_directory)


def copy_static(root_directory, dist_directory, sdk_directory, development):
    """
    Copy all static files from source to target.
    """

    for static in configuration.STATICS:
        context = {
            "development": development,
            "dist": dist_directory,
            "root": root_directory,
            "sdk": sdk_directory,
        }

        source = templates.from_string(static["source"], context)
        target = templates.from_string(static["target"], context)
        target = os.path.join(dist_directory, target)

        # Compute filters.
        ignored = []

        if "filters" in static:
            for expression in static["filters"].keys():
                new_expression = templates.from_string(
                    expression, context)

                if not static["filters"][expression](context):
                    ignored.append(new_expression)

        # Perform the action.
        sys.stdout.write("Copying '%s'\n" % source)

        if static["type"] == "directory":
            recursive_overwrite(source, target, ignored)
        else:
            if source not in ignored:
                shutil.copy(source, target)


def copy_templates(root_directory, dist_directory, sdk_directory,
                   cpus, families, boards, development):
    """
    Copy all the templates.
    """

    def _process(when, contexts, label_func):
        for context in contexts:
            for template in configuration.TEMPLATES:
                if template["when"] == when:
                    context.update({
                        "development": development,
                        "dist": dist_directory,
                        "root": root_directory,
                        "sdk": sdk_directory,
                    })

                    source = templates.from_string(template["source"], context)
                    target = templates.from_string(template["target"], context)
                    target = os.path.join(dist_directory, target)

                    # Compute filters.
                    filters = {}

                    if "filters" in template:
                        for expression in template["filters"].keys():
                            new_expression = templates.from_string(
                                expression, context)

                            filters[new_expression] = \
                                template["filters"][expression]

                    # Perform the action.
                    sys.stdout.write(
                        "Processing '%s' for '%s'\n" % (
                            source, label_func(context)))

                    if template["type"] == "file":
                        if source in filters:
                            if not filters[source](context):
                                continue

                        templates.from_file(source, target, context)
                    elif template["type"] == "glob":
                        for source_file in glob.glob(source):
                            if os.path.isfile(source_file):
                                if source_file in filters:
                                    if not filters[source_file](context):
                                        continue

                                target_file = os.path.join(
                                    target, os.path.basename(source_file))

                                templates.from_file(
                                    source_file, target_file, context)
                    else:
                        raise Exception(
                            "Unsupported template: %s", template["type"])

    _process("per_family", families, lambda c: c["family"])
    _process("per_cpu", cpus, lambda c: c["cpu"])
    _process("per_board", boards, lambda c: c["board"])
    _process(
        "once",
        [{
            "families": [family["family"] for family in families],
            "cpus": [cpu["cpu"] for cpu in cpus],
            "boards": [board["board"] for board in boards]
        }],
        lambda c: "once")


def copy_patches(root_directory, dist_directory, sdk_directory,
                 cpus, families, boards):
    """
    Copy all the patches.
    """

    def _process(when, contexts, label_func):
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
                    sys.stdout.write(
                        "Patching '%s' for '%s'\n" % (
                            source, label_func(context)))

                    if patch["type"] == "file":
                        with open(source, "r") as fp:
                            content = fp.read()

                        for method in patch["methods"]:
                            content = method(source, content)

                        if not os.path.isdir(target):
                            os.makedirs(target)

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

                                if not os.path.isdir(target):
                                    os.makedirs(target)

                                with open(target_file, "w") as fp:
                                    fp.write(content)
                    else:
                        raise Exception("Not supported")

    _process("per_family", families, lambda c: c["family"])
    _process("per_cpu", cpus, lambda c: c["cpu"])
    _process("per_board", boards, lambda c: c["board"])
    _process(
        "once",
        [{
            "families": [family["family"] for family in families],
            "cpus": [cpu["cpu"] for cpu in cpus],
            "boards": [board["board"] for board in boards]
        }],
        lambda c: "once")


def recursive_overwrite(source, target, ignored=None):
    """
    Wrapper for shutil.copytree that can merge source and target.
    """

    if os.path.isdir(source):
        if not os.path.isdir(target):
            os.makedirs(target)
        files = os.listdir(source)

        if ignored is None:
            ignored = set()

        for f in files:
            if os.path.join(source, f) not in ignored:
                recursive_overwrite(
                    os.path.join(source, f), os.path.join(target, f), ignored)
    else:
        shutil.copyfile(source, target)
