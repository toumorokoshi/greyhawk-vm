use std::rc::Rc;
use super::{Register, RegList, Type, OpList};

pub type NativeFunction = fn(&[Register]) -> Register;

pub enum Function {
    VM(Rc<Function>),
    Native(Rc<NativeFunction>)
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
