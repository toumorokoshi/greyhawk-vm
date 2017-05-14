use super::super::{
    FunctionBuilder, Type
};

#[test]
fn test_get_insert_local_val() {
    let mut builder = FunctionBuilder::new();
    let name = String::from("foo");
    let object = builder.get_insert_local_var(&Type::Int, &name);
    let object_next = builder.get_insert_local_var(&Type::Int, &name);
    assert_eq!(object.register, object_next.register);
}
