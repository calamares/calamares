#! /usr/bin/env python3
#
# SPDX-FileCopyrightText: 2020 Adriaan de Groot <groot@kde.org>
# SPDX-License-Identifier: BSD-2-Clause
#
usage = """
Validates a Calamares config file -- YAML syntax -- against a schema.

The schema is also written in YAML syntax, but the schema itself
is JSON-schema. This is possible because all JSON is YAML, and most
YAML is JSON. The limited subset of YAML that Calamares uses is
JSON-representable, anyway.

Usage:
    configvalidator.py <schema> <file> ...
    configvalidator.py -m <module>
    configvalidator.py -x

Exits with value 0 on success, otherwise:
    1 on missing dependencies
    2 on invalid command-line arguments
    3 on missing files
    4 if files have invalid syntax
    5 if files fail to validate
Use -x as only command-line argument to check the imports only.

Use -m <module> as shorthand for standard paths in src/modules/<module>/
"""

# The schemata originally lived outside the Calamares repository,
# without documented tooling. By putting them in the repository
# with the example files and explicit tooling, there's a better
# chance of them catching problems and acting as documentation.

dependencies = """
Dependencies for this tool are: py-yaml and py-jsonschema.

    https://pyyaml.org/
    https://github.com/Julian/jsonschema

Simple installation is `pip install pyyaml jsonschema`
"""

ERR_IMPORT, ERR_USAGE, ERR_FILE_NOT_FOUND, ERR_SYNTAX, ERR_INVALID = range(1,6)

### DEPENDENCIES
#
#
try:
    from jsonschema import validate, SchemaError, ValidationError
    from jsonschema import draft7_format_checker
    from yaml import safe_load, YAMLError
except ImportError as e:
    print(e)
    print(dependencies)
    exit(ERR_IMPORT)

from os.path import exists
import sys

### INPUT VALIDATION
#
#
if len(sys.argv) < 3:
    # Special-case: called with -x to just test the imports
    if len(sys.argv) == 2 and sys.argv[1] == "-x":
        exit(0)
    print(usage)
    exit(ERR_USAGE)

if len(sys.argv) == 3 and sys.argv[1] == "-m":
    module = sys.argv[2]
    schema_file_name = f"src/modules/{module}/{module}.schema.yaml"
    config_file_names = [ f"src/modules/{module}/{module}.conf" ]
else:
    schema_file_name = sys.argv[1]
    config_file_names = sys.argv[2:]

if not exists(schema_file_name):
    print(usage)
    print("\nSchema file '{}' does not exist.".format(schema_file_name))
    exit(ERR_FILE_NOT_FOUND)
for f in config_file_names:
    if not exists(f):
        print(usage)
        print("\nYAML file '{}' does not exist.".format(f))
        exit(ERR_FILE_NOT_FOUND)

### FILES SYNTAX CHECK
#
#
with open(schema_file_name, "r") as data:
    try:
        schema = safe_load(data)
    except YAMLError as e:
        print("Schema error: {} {}.".format(e.problem, e.problem_mark))
        print("\nSchema file '{}' is invalid YAML.".format(schema_file_name))
        exit(ERR_SYNTAX)

try:
    validate(instance={}, schema=schema)
# While developing the schemata, get full exceptions from schema failure
except SchemaError as e:
    print(e)
    print("\nSchema file '{}' is invalid JSON-Schema.".format(schema_file_name))
    exit(ERR_INVALID)
except ValidationError:
    # Just means that empty isn't valid, but the Schema itself is
    pass

configs = []
for f in config_file_names:
    config = None
    with open(f, "r") as data:
        try:
            config = safe_load(data)
        except YAMLError as e:
            print("YAML error: {} {}.".format(e.problem, e.problem_mark))
            print("\nYAML file '{}' is invalid.".format(f))
            exit(ERR_SYNTAX)
    if config is None:
        print("YAML file '{}' is empty.".format(f))
    configs.append(config)

assert len(configs) == len(config_file_names), "Not all configurations loaded."

### SCHEMA VALIDATION
#
#
for c, f in zip(configs, config_file_names):
    try:
        validate(instance=c, schema=schema)
    except ValidationError as e:
        print(e)
        print("\nConfig file '{}' does not validate in schema.".format(f))
        exit(ERR_INVALID)
