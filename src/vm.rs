use std::collections::HashMap;
use std::rc::Rc;
use std::mem;

// for some reason, wildcards (*) don't work.
use super::{Function, Module, Op};

pub struct VM {
    pub modules: HashMap<&'static str, Module>,
}

impl VM {
    pub fn new() -> VM {
        return VM {modules: HashMap::new()};
    }

    pub fn execute_instructions(&mut self, reg_count: usize, ops: &[Op]) -> i64 {
        // TODO: once rust supports allocating
        // variable length arrays on the stack, use that
        // instead. This is heap allocated which can be significantly
        // less performant.
        let mut registers = vec![0 as i64; reg_count];
        let return_value = 0 as usize;
        let mut i = 0;
        while i < ops.len() {
            let ref op = ops[i];
            match op {
                &Op::Assign{source, target} => {
                    registers[target] = registers[source];
                },
                &Op::ArrayCreate{target, length_source} => unsafe {},
                &Op::ArraySet{source, target, index_source} => unsafe {},
                &Op::ArrayLoad{source, target, index_source} => unsafe {},
                &Op::BoolNot{source, target} => {
                    registers[target] = if registers[source] != 1 { 1 } else { 0 };
                },
                &Op::Branch{condition, if_false} => {
                    if registers[condition] == 0 {
                        // -1 to allow an increment at the end of the
                        // function.
                        i = if_false - 1;
                    }
                },
                // &Op::Call{ref func, ref args, target} => {};
                &Op::IntAdd{lhs, rhs, target} => registers[target] = registers[lhs] + registers[rhs],
                &Op::IntCmp{lhs, rhs, target} => registers[target] = if registers[lhs] == registers[rhs] {1} else {0},
                &Op::IntSub{lhs, rhs, target} => registers[target] = registers[lhs] - registers[rhs],
                &Op::IntMul{lhs, rhs, target} => registers[target] = registers[lhs] * registers[rhs],
                &Op::IntDiv{lhs, rhs, target} => registers[target] = registers[lhs] / registers[rhs],
                &Op::IntLoad{register, constant} => registers[register] = constant,
                &Op::IntLessEqual{lhs, rhs, target} => registers[target] = if registers[lhs] <= registers[rhs] {1} else {0},
                &Op::IntLessThan{lhs, rhs, target} => registers[target] = if registers[lhs] < registers[rhs] {1} else {0},
                &Op::FloatAdd{lhs, rhs, target} => unsafe {
                    registers[target] = mem::transmute::<f64, i64>(
                        mem::transmute::<i64, f64>(registers[lhs]) +
                        mem::transmute::<i64, f64>(registers[rhs]),
                    );
                },
                &Op::FloatCmp{lhs, rhs, target} => unsafe {
                    registers[target] = if
                        mem::transmute::<i64, f64>(registers[lhs]) ==
                        mem::transmute::<i64, f64>(registers[rhs])
                    { 1 } else { 0 };
                },
                &Op::FloatSub{lhs, rhs, target} => unsafe {
                    registers[target] = mem::transmute::<f64, i64>(
                        mem::transmute::<i64, f64>(registers[lhs]) -
                        mem::transmute::<i64, f64>(registers[rhs]),
                    );
                },
                &Op::FloatMul{lhs, rhs, target} => unsafe {
                    registers[target] = mem::transmute::<f64, i64>(
                        mem::transmute::<i64, f64>(registers[lhs]) *
                        mem::transmute::<i64, f64>(registers[rhs]),
                    );
                },
                &Op::FloatDiv{lhs, rhs, target} => unsafe {
                    registers[target] = mem::transmute::<f64, i64>(
                        mem::transmute::<i64, f64>(registers[lhs]) /
                        mem::transmute::<i64, f64>(registers[rhs]),
                    );
                },
                &Op::FloatLoad{register, constant} => unsafe {
                    registers[register] = mem::transmute::<f64, i64>(constant)
                },
                &Op::FloatLessEqual{lhs, rhs, target} => unsafe {
                    registers[target] = if
                        mem::transmute::<i64, f64>(registers[lhs]) <=
                        mem::transmute::<i64, f64>(registers[rhs])
                    { 1 } else { 0 };
                },
                &Op::FloatLessThan{lhs, rhs, target} => unsafe {
                    registers[target] = if
                        mem::transmute::<i64, f64>(registers[lhs]) <
                        mem::transmute::<i64, f64>(registers[rhs])
                    { 1 } else { 0 };
                },
                &Op::Goto{position} => {
                    i = position - 1;
                },
                &Op::Noop{} => {},
                // TODO: incomplete. ends up as the null pointer right now.
                &Op::StringLoad{register, ref constant} => unsafe {
                    registers[register] = mem::transmute::<Rc<String>, i64>(constant.clone());
                },
                &Op::Return{register} => { return registers[register]; },
            };
            i +=1;
        }
        0
    }

    pub fn execute_function(&mut self, func: &Function) -> i64 {
        self.execute_instructions(
            func.registers.len(), &func.ops
        )
    }
}
