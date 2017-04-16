/// ghvm is a register based VM, but has
/// a stack of registers to handle
/// nested functions nevertheless.
///
/// Having a stack that contains the
/// most relevant variables ensures
/// better cache affinity, as the memory
/// associated with loading and operating
/// on variables are found in the same block

struct Stack {
}
