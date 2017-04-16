use super::{Register, RegList, Type, OpList};

pub struct Function {
    pub registers: Vec<Type>,
    pub return_type: Type,
    pub ops: OpList
}

impl Function {
    pub fn new(return_type: Type) -> Function {
        return Function {
            registers: Vec::new(),
            ops: OpList::new(),
            return_type: return_type
        };
    }

    pub fn print_ops(&self) {
        for ref op in &self.ops {
            println!("  {0}", op);
        }
    }
}
