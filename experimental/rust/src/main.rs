mod lexer;
mod parser;
mod codegen;
mod vm;

use std::io::{self, Write};
use std::collections::HashMap;

fn main () {
    println!("Greyhawk 0.0.3");
    let vm_instance = vm::VM::new();
    match vm_instance.modules.get("main") {
        Some(module) => {
            repl(module, &vm_instance);
        },
        None => println!("unable to load main module!"),
    }
}

fn repl(module: &vm::Module, vm_instance: &vm::VM) {
    let lexer = lexer::Lexer::new();
    loop {
        std::io::stdout().write(b">>> ");
        std::io::stdout().flush();
        let mut guess = String::new();
        io::stdin().read_line(&mut guess).ok().expect("Failed to read line");
        let function = get_test_function();
        let value = vm_instance.execute_function(module, &function);
    }
}

fn get_test_function() -> vm::Function {
    let ops = Box::new([
        vm::Op::AddConstantInt{register: 0, constant: 15},
    ]);
    return vm::Function::VMFunction{
        register_count: 1,
        ops: ops
    };
}
