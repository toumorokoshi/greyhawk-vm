# Goals

ghvm is driven by a core set of goals.

## Minimize need for native code

Many VMs acknowledge that writing extremely high performance code in
the VM itself is difficult, and suggest writing code in some native
language (typically C) for performance improvements instead.

Requiring a lower level language should not be required to increase
performance. A majority of these cases should be enabled within
the VM itself:

* cache affinity by tightly packing data.
* instantiating objects on the stack instead of the heap.
