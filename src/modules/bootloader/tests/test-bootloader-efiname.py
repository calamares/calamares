# Calamares Boilerplate
import libcalamares
libcalamares.globalstorage = libcalamares.GlobalStorage(None)
libcalamares.globalstorage.insert("testing", True)

# Module prep-work
from src.modules.bootloader import main

# Specific Bootloader test
g = main.get_efi_suffix_generator("derp@@SERIAL@@")
assert g is not None
for n in range(10):
    print(g.next())
assert g.next() == "derp11"

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

# Check two invalid things
try:
    g = main.get_efi_suffix_generator("derp")
    raise TypeError("Shouldn't get generator")
except ValueError as e:
    pass

try:
    g = main.get_efi_suffix_generator("derp@@HEX@@")
    raise TypeError("Shouldn't get generator")
except ValueError as e:
    pass
