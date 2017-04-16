use super::super::{VM, Function, Type, Op};

/// tests the full scenario
#[test]
fn test_full() {
    let mut vm = VM::new();
    let mut function = Function::new(Type::Int);
    function.registers.push(Type::Int);
    function.registers.push(Type::Int);
    function.ops.push(Op::IntLoad{register: 0, constant: 10});
    function.ops.push(Op::IntLoad{register: 1, constant: 20});
    function.ops.push(Op::IntAdd{lhs: 1, rhs: 0, target: 1});
    function.ops.push(Op::Return{register: 1});
    let result = vm.execute_function(&function);
    println!("{}", result);
    assert!(result == 30);
}
