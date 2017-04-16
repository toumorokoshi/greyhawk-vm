#![feature(plugin, box_syntax, box_patterns)]

#[macro_use]
extern crate lazy_static;

mod builtins;
mod function;
mod module;
mod scope;
mod ops;
mod types;
mod vm;

pub use function::{Function, VMFunction};
pub use module::{Module, ModuleFile};
pub use ops::{Op, OpList};
pub use scope::{
    LocalObject,
    Scope, ScopeInstance
};
pub use vm::{VM, Object};
pub use types::{NONE_TYPE, INT_TYPE};
