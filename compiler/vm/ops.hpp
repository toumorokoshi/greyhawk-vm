#include "object.hpp"

#ifndef VM_OP_HPP
#define VM_OP_HPP


namespace VM {

  // these are all the instruction supported by the vm.
  enum GOPCODE {
    ARRAY_ALLOCATE,
    ARRAY_SET_VALUE,
    ARRAY_LOAD_VALUE,
    ARRAY_LOAD_LENGTH,
    ADD_INT,
    ADD_FLOAT,
    DIVIDE_FLOAT,
    DIVIDE_INT,
    BRANCH,
    EXECUTE,
    END,
    FILEHANDLE_WRITE,
    FUNCTION_CREATE,
    FUNCTION_CALL,
    GO,
    GLOBAL_LOAD,
    GLOBAL_WRITE,
    INSTANCE_CREATE,
    INSTANCE_LOAD_ATTRIBUTE,
    INSTANCE_STORE_ATTRIBUTE,
    INT_TO_FLOAT,
    LABEL,
    LOAD_CONSTANT_BOOL,
    LOAD_CONSTANT_FILEHANDLE,
    LOAD_CONSTANT_FLOAT,
    LOAD_CONSTANT_INT,
    LOAD_CONSTANT_STRING,
    LOAD_MODULE,
    LOAD_MODULE_VALUE,
    LENGTH,
    LESS_THAN_INT,
    MULTIPLY_FLOAT,
    MULTIPLY_INT,
    PRINT_CHAR,
    PRINT_FLOAT,
    PRINT_INT,
    PRINT_STRING,
    SET,
    SUBTRACT_FLOAT,
    SUBTRACT_INT,
    TYPE_LOAD,
    RETURN,
    RETURN_NONE,
  };

  typedef union {
    int registerNum;
    int positionDiff;
    int size;
    int asInt32;
    bool asBool;
    double asFloat;
    FILE* asFile;
    const char* asString;
  } GOPARG;

  typedef struct {
    GOPCODE op;
    GOPARG* args;
  } GInstruction;
}

#endif
