use std::collections::HashMap;
use super::Function;

pub struct Module {
    functions: HashMap<String, Function>
}

impl Module {
    pub fn new() -> Module {
        return Module {
            functions: HashMap::new()
        };
    }
}
