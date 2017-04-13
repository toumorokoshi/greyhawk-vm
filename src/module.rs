use super::{Scope, ScopeInstance, OpList};
// use std::collections::HashMap;

pub struct Module {
    pub scope: Scope,
    pub scope_instance: ScopeInstance
}

/// represents the data
/// a module has on disk
pub struct ModuleFile {
    pub scope: Scope,
    pub ops: Vec<OpList>
}
