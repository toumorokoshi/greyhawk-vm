# Functions

ghvm supports two types of functions: VMFunctions (vm opcodes), and
native functions (via dynamic library loading).

Functions are stored in a HashMap on the VM itself. The VM handles
creating and releasing functions manually. Using, say, a reference-counted pointer
doesn't work
