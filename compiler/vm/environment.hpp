#include <iostream>
#include <map>
#include <vector>
#include "ops.hpp"
#include "type.hpp"
#include "object.hpp"

#ifndef VM_CONTEXT_HPP
#define VM_CONTEXT_HPP

namespace VM {

  struct GEnvironmentInstance;
  struct GFunction;

  typedef std::map<std::string, GType*> GTypeMap;

  // we use a class instead of a struct
  // so we can encapsulate things for now,
  // until a good mechanism is decided.
  class GEnvironment {
  public:
    // globals data
    std::map<std::string, int> globalsTable;
    GType** globalsTypes;
    int* indicesInParent;
    int globalsCount;

    // function data
    std::map<std::string, GFunction*> functionByName;
    std::map<int, int> functionTable;
    std::vector<GFunction*> functions;
    int functionCount;

    // class data
    std::map<std::string, GType*> typeByName;
    std::vector<GType*> types;
    int typeCount;

    // locals data
    std::map<std::string, int> localsTable;
    std::vector<GType*> localsTypes;
    int localsCount;

    // get the index of an object
    // negative = global scope (GLOBAL_LOAD)
    // positive = local scope (LOAD)
    GIndex* getObject(std::string name) {
      if (localsTable.find(name) != localsTable.end()) {
        int index = localsTable[name];
        return new GIndex{
          .registerNum = index,
          .type = localsTypes[index]
        };
      }

      if (globalsTable.find(name) != globalsTable.end()) {
        int index = globalsTable[name];
        return new GIndex {
          .indexType = GLOBAL,
          .registerNum = index,
          .type = globalsTypes[index]
        };
      }

      return NULL;
    }

    GIndex* addObject(std::string name, GType* type) {
      auto index = allocateObject(type);
      localsTable[name] = index->registerNum;
      return index;
    }

    GIndex* allocateObject(GType* type) {
      localsTypes.push_back(type);
      return new GIndex {
        .registerNum = localsCount++,
        .type = type
      };
    }

    // function methods

    int allocateFunction(GFunction* func) {
      functions.push_back(func);
      return functionCount++;
    }

    int addFunction(std::string name, GFunction* func) {
      int index = allocateFunction(func);
      functionByName[name] = func;
      return index;
    }

    GFunction* getFunction(std::string name) {
      if (functionByName.find(name) != functionByName.end()) {
        return functionByName[name];
      }
      return NULL;
    }

    // class methods
    GIndex* addClass(std::string name, GType* type) {
      typeByName[name] = type;
      return allocateClass(type);
   }

    GIndex* allocateClass(GType* type) {
      types.push_back(type);
      return new GIndex {
        .registerNum = typeCount++,
        .type = getClassType()
      };
    }

    GType* getClass(std::string name) {
      if (typeByName.find(name) != typeByName.end()) {
        return typeByName[name];
      }
      return NULL;
    }

    GEnvironmentInstance* createInstance(GEnvironmentInstance&);
    GEnvironment* createChild();
  };

  struct GEnvironmentInstance {
    GEnvironment* environment;
    GValue** globals;
    GValue* locals;

    GValue getValue(std::string);

    GEnvironmentInstance* createChildScope(GEnvironmentInstance&);
  };

  GEnvironment* getEmptyEnvironment();
  GEnvironmentInstance& getEmptyEnvironmentInstance();
}
#endif
