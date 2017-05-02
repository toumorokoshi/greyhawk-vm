use std::rc::Rc;
use super::{Register, RegList, Type, OpList, Value, ValueList, VM};

pub type NativeFunction = fn(&mut VM, Vec<Value>) -> Value;

pub enum Function {
    VM(Rc<VMFunction>),
    Native(Rc<NativeFunction>)
}

impl Function {
    pub fn execute(&self, vm: &mut VM, mut args: ValueList) -> Value {
        match self {
            &Function::VM(ref func) => {
                let target_size = args.len() + func.registers.len();
                args.resize(target_size, 0);
                vm.execute_instructions(args, &func.ops)
            },
            &Function::Native(ref func) => {
                func(vm, args)
            }
        }
    }
}

pub struct VMFunction {
    pub registers: Vec<Type>,
    pub return_type: Type,
    pub ops: OpList
}

impl VMFunction {
    pub fn new() -> VMFunction {
        return VMFunction {
            registers: Vec::new(),
            ops: OpList::new(),
            return_type: Type::None
        };
    }

    pub fn print_ops(&self) {
        for ref op in &self.ops {
            println!("  {0}", op);
        }
    }
}
