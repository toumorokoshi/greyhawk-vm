/// ghvm types can be categorized between two types: primitives and structs
/// structs are constructed from primitives. Primitives are:
/// * integer
/// * float
/// * bool
/// number types will be split into sizings in the future.
/// It would be nice if structs were similary to how they are in c,
/// where fields that fit inside a word can be compacted.
use std::fmt;

pub enum Type {
    Int,
    Float,
    Array(Box<Type>)
}

impl fmt::Display for Type {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        match self {
            &Type::Int => write!(f, "Int"),
            &Type::Float => write!(f, "Float"),
            &Type::Array(ref t) => write!(f, "Array<{0}>", t)
        }
    }
}
