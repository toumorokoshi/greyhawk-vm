#include "type.hpp"
#include <map>

namespace VM {

  GType* getArrayType(GType* elementType) {
    static std::map<GType*, GType*> arrayTypes;
    if (arrayTypes.find(elementType) == arrayTypes.end()) {
      arrayTypes[elementType] = new GType { ARRAY, "Array<" + elementType->name + ">",
                                            new GType*[1] { elementType }};
    }
    return arrayTypes[elementType];
  }

  GType* getBoolType() {
    auto static boolType = new GType { BOOL, "Bool", NULL };
    return boolType;
  }

  GType* getFloatType() {
    auto static floatType = new GType { FLOAT, "Float", NULL };
    return floatType;
  }

  GType* getInt32Type() {
    auto static intType = new GType { INT32, "Int32", NULL };
    return intType;
  }

  GType* getStringType() {
    auto static stringType = new GType { STRING, "String", NULL };
    return stringType;
  }

  GType* getNoneType() {
    auto static noneType = new GType { NONE, "None", NULL };
    return noneType;
  }
}