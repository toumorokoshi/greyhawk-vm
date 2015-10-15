pub enum Op {
    IntAdd{lhs: usize, rhs: usize, target: usize},
    IntLoad{ register: usize, constant: i32},
    FloatAdd{lhs: usize, rhs: usize, target: usize},
    FloatLoad { register: usize, constant: f32},
    Return{register: usize},
}
