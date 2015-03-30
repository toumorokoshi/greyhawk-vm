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

    std::map<std::string, GFunction*> functionByName;
    std::map<int, int> functionTable;
    std::vector<GFunction*> functions;
    int functionCount;

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
          .isGlobal = true,
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

}
#endif