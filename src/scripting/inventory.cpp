#include "scripting/inventory.hpp"
#include <string>
namespace scripting {
  Inventory::Inventory()
  {

  }
  bool Inventory::hasItem(const std::string itemname)
  {
    return false;
  }

  bool Inventory::isInventoryItem()
  {
    return true;
  }

}
