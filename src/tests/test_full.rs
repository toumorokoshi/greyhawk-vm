use std::rc::Rc;
use super::super::{
    Function, NativeFunction,  VMFunction,
    Value,
    VM, Type, Op
};

/// tests the full scenario
#[test]
fn test_full() {
    let mut vm = VM::new();
    let mut function = VMFunction::new();
    function.return_type = Type::Int;
    function.registers.push(Type::Int);
    function.registers.push(Type::Int);
    function.ops.push(Op::IntLoad{register: 0, constant: 10});
    function.ops.push(Op::IntLoad{register: 1, constant: 20});
    function.ops.push(Op::IntAdd{lhs: 1, rhs: 0, target: 1});
    function.ops.push(Op::Return{register: 1});
    function.return_type = Type::Int;
    let wrapped_func = Function::VM(Rc::new(function));
    let result = wrapped_func.execute(&mut vm, vec![]);
    println!("{}", result);
    assert!(result == 30);
}

fn native_func(vm: &mut VM, mut args: Vec<Value>) -> Value {
    return 15;
}

#[test]
/// test the native function call
fn test_native_func() {
    let mut vm = VM::new();
    let wrapped_func = Function::Native(Rc::new(native_func));
    let result = wrapped_func.execute(&mut vm, vec![]);
    println!("{}", result);
    assert!(result == 15);}
