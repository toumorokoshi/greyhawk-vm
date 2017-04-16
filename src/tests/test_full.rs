use super::super::{VM, Function, Types, Op};

/// tests the full scenario
#[test]
fn test_full() {
    let mut vm = VM::new();
    let mut function = VMFunction::new(Type::Int);
    function.registers.push(Type::Int);
    function.registers.push(Type::Int);
    function.ops.push(Op::IntLoad(0, 10));
    function.ops.push(Op::IntLoad(1, 20));
    function.ops.push(Op::IntAdd(1, 0, 1));
    function.ops.push(Op::Return(1));
    let result = vm.execute_function(function);
    assert!(result, 30);
}
