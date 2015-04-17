#include "type.hpp"
#include "environment.hpp"
#include "function.hpp"
#include <map>

namespace VM {

  GType* getArrayType(GType* elementType) {
    static std::map<GType*, GType*> arrayTypes;
    if (arrayTypes.find(elementType) == arrayTypes.end()) {
      arrayTypes[elementType] = new GType {
        .classifier = ARRAY,
        .name = "Array<" + elementType->name + ">",
        .subTypes = new GType*[1] { elementType }};
    }
    return arrayTypes[elementType];
  }

  GType* getBoolType() {
    auto static boolType = new GType { BOOL, "Bool", NULL };
    return boolType;
  }

  GType* getClassType() {
    auto static classType = new GType { CLASS, "Class", NULL };
    return classType;
  };

  GType* getCharType() {
    auto static charType = new GType { CHAR, "Char", NULL };
    return charType;
  };

  GType* getFloatType() {
    auto static floatType = new GType { FLOAT, "Float", NULL };
    return floatType;
  }

  GType* getFunctionType() {
    auto static functionType = new GType { FUNCTION, "Float", NULL };
    return functionType;
  }

  GType* getInt32Type() {
    auto static intType = new GType { INT32, "Int32", NULL };
    return intType;
  }

  GType* getFileHandleType() {
    auto static fileHandleType = new GType { FILEHANDLE, "FileHandle", NULL };
    return fileHandleType;
  }

  GType* getStringType() {
    return getArrayType(getCharType());
  }

  GType* getNoneType() {
    auto static noneType = new GType { NONE, "None", NULL };
    return noneType;
  }

  GEnvironmentInstance* GType::instantiate() {
    auto instance = environment->createInstance(*parentEnv);
    // we instantiate all the methods, binding them to the current context.
    for (int i = 0; i < functionCount; i++) {
      // methods are instantiate after type.
      int methodIndex = i + attributeCount;
      instance->locals[methodIndex].asFunction = new GFunctionInstance {
        .function = environment->functions[i],
        .parentEnv = *instance
      };
    }
    return instance;
  }
}
