#ifndef HEADER_SUPERTUX_SCRIPTING_INVENTORY_HPP
#define HEADER_SUPERTUX_SCRIPTING_INVENTORY_HPP
#ifndef SCRIPTING_API
#include <string>
#include <squirrel.h>
#include <sqrat.h>
#include "storage/ScriptInventoryItem.hpp"
#define __custom(x)
#endif

namespace scripting {

  class Inventory {
    public:
      Inventory();
      bool hasItem(const std::string itemname);
      // Add can only accept ScriptableInventoryItems
      /**
       * @typecheck ttx
       */
      bool isInventoryItem();
  };
}

#endif
