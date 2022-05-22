# SPDX-FileCopyrightText: no
# SPDX-License-Identifier: CC0-1.0
#
# Calamares Boilerplate
import libcalamares
libcalamares.globalstorage = libcalamares.GlobalStorage(None)
libcalamares.globalstorage.insert("testing", True)

# Module prep-work
from src.modules.bootloader import main

# Specific Bootloader test
g = main.get_efi_suffix_generator("derp@@SERIAL@@")
assert g is not None
assert g.next() == "derp"  # First time, no suffix
for n in range(9):
    print(g.next())
# We called next() 10 times in total, starting from 0
assert g.next() == "derp10"

g = main.get_efi_suffix_generator("derp@@RANDOM@@")
assert g is not None
for n in range(10):
    print(g.next())
# it's random, nothing to assert

g = main.get_efi_suffix_generator("derp@@PHRASE@@")
assert g is not None
for n in range(10):
    print(g.next())
# it's random, nothing to assert

# Check invalid things
try:
    g = main.get_efi_suffix_generator("derp")
    raise TypeError("Shouldn't get generator (no indicator)")
except ValueError as e:
    pass

try:
    g = main.get_efi_suffix_generator("derp@@HEX@@")
    raise TypeError("Shouldn't get generator (unknown indicator)")
except ValueError as e:
    pass

try:
    g = main.get_efi_suffix_generator("derp@@SERIAL@@x")
    raise TypeError("Shouldn't get generator (trailing garbage)")
except ValueError as e:
    pass

try:
    g = main.get_efi_suffix_generator("derp@@SERIAL@@@@RANDOM@@")
    raise TypeError("Shouldn't get generator (multiple indicators)")
except ValueError as e:
    pass


# Try the generator (assuming no calamares- test files exist in /tmp)
import os
assert "calamares-single" == main.change_efi_suffix("/tmp", "calamares-single")
assert "calamares-serial" == main.change_efi_suffix("/tmp", "calamares-serial@@SERIAL@@")
try:
    os.makedirs("/tmp/calamares-serial", exist_ok=True)
    assert "calamares-serial1" == main.change_efi_suffix("/tmp", "calamares-serial@@SERIAL@@")
finally:
    os.rmdir("/tmp/calamares-serial")
