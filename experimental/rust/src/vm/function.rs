use super::VM;
use super::Object;
use super::ops;
use super::scope;
use std::rc::Rc;

pub struct VMFunction {
    pub scope: scope::Scope,
    pub ops: Vec<ops::Op>
}

pub enum Function {
    NativeFunction{
        function: fn() -> i32,
        typ: super::types::TypeRef
    },
    VMFunction(VMFunction)
}

impl Function {
    pub fn call(&self, vm: &mut VM) -> Object {
        match self {
            &Function::NativeFunction{function, ref typ} => {
                return Object{
                    value: function(),
                    typ: typ.clone()
                };
            },
            &Function::VMFunction(ref f) => {
                let mut scopeInstance = f.scope.create_instance();
                let return_register = vm.execute_instructions(&mut scopeInstance, &f.ops[..]);
                return Object{
                    value: scopeInstance.registers[return_register],
                    typ: f.scope.types[return_register].clone()
                };
            },
        }
    }
}
