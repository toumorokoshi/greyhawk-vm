#![feature(plugin, box_syntax, box_patterns)]

#[macro_use]
extern crate lazy_static;
extern crate getopts;
extern crate yaml_rust;
use std::io::prelude::*;
use std::fs::File;

pub mod vm;
use yaml_rust::{Yaml};

use yaml_rust::emitter::YamlEmitter;
use std::env;

fn main () {
    let args: Vec<String> = env::args().collect();
    let matches = match setup_opts().parse(&args[1..]) {
        Ok(m) => {m},
        Err(f) => {panic!(f.to_string())},
    };
    match matches.free.len() {
        1 => execute_file(&matches.free[0]),
        _ => println!("Invalid Args"),
    }
}

fn setup_opts() -> getopts::Options {
    let mut opts = getopts::Options::new();
    opts.optflag("h", "help", "print this help menu");
    return opts;
}

fn print_yaml(yaml: Yaml) {
    let mut out_str = String::new();
    {
        let mut emitter = YamlEmitter::new(&mut out_str);
        emitter.dump(&yaml).unwrap();
    }
    println!("{}", out_str);
}

fn execute_file(path: &String) {
    let mut vm_instance = vm::VM::new();
    let mut file = File::open(path).unwrap();
    let mut content = String::new();
    file.read_to_string(&mut content).unwrap();
    // TODO: execute VM.
}
