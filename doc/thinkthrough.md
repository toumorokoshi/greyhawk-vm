# Think Through

These are various challenges that GHVM should address or enable, but
are not completely accomplished within the vm design.


## Tight Datastructure Packing

Many virtual machines are designed with flexibility in mind without a
strong regard for compactedness or cache affinity. For example, almost
all objects in Python are behind some sort of pointer.

This makes performance incredibly difficult, for both memory
conservation, and CPU via cache affinity.

One part of the puzzle is ensuring data structures can be packed
tightly.

# Arrays

- array need a type to help pack and to allocate memory. How do we represent that in the VM?

# Interop

Module files from one language should be compatible with module files
from others. This enable re-use.
