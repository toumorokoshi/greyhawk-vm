#![feature(plugin, box_syntax, box_patterns)]

#[macro_use]
extern crate lazy_static;

// mod builtins;
mod core;
mod function;
mod module;
// mod scope;
mod ops;
mod types;
mod vm;

pub use function::{Function};
pub use module::{Module};
pub use ops::{Op, OpList};
/* pub use scope::{
    LocalObject,
    Scope, ScopeInstance
}; */
pub use vm::{VM};
pub use types::{Type};
pub use core::{Register, RegList};

#[cfg(test)]
mod tests;
