/// builders are designed to assist with the construction of objects
/// that are used n ghvm
use super::{Function, Type, OpList, Op};

pub struct BuildObject {
    pub typ: Type, // the type of object
    pub register: usize // the register where the object lives
}

pub struct FunctionBuilder {
    pub registers: Vec<Type>,
    pub ops: OpList,
    pub return_type: Option<Type>,
}

impl FunctionBuilder {
    pub fn new() -> FunctionBuilder {
        return FunctionBuilder{
            registers: Vec::new(),
            ops: OpList::new(),
            return_type: None
        }
    }

    pub fn allocate_local(&mut self, typ: Type) -> BuildObject {
        self.registers.push(typ.clone());
        return BuildObject {
            typ: typ.clone(), register: self.registers.len() - 1
        }
    }

    pub fn add_return(&mut self, obj: &BuildObject) {
        if let Some(ref rt) = self.return_type {
            if *rt != obj.typ {
                panic!("mismatch on return type.");
            }
        }
        self.return_type = Some(obj.typ.clone());
        self.ops.push(Op::Return{register: obj.register});
    }

    pub fn build(&mut self) -> Function {
        let mut function = Function::new();
        match self.return_type {
            Some(ref t) => {function.return_type = t.clone();},
            None => {function.return_type = Type::None}
        }
        function.registers = self.registers.to_owned();
        function.ops = self.ops.to_owned();
        return function;
    }
}
