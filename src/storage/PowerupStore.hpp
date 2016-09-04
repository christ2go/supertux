#include "storage/storable.hpp"
#include "object/player.hpp"
#include "storage/inventory_item.hpp"
#ifndef HEADER_STORABLE_POWERUPSTORAGE_HPP
#define HEADER_STORABLE_POWERUPSTORAGE_HPP

class PowerupStore: public InventoryFactory
{
private:
  std::map<BonusType,int> powerups;
  class PowerUpInventoryWrapper : public FactoryItemWrapper
  {
    private:
      BonusType my_bonus;
      PowerupStore& m_factory;

    public:
      PowerUpInventoryWrapper(PowerupStore & p,BonusType t):
        my_bonus(t),
        m_factory(p)
      {
      }

      void use()
      {

      }

      std::string getIdentifier()
      {
        return "powerupstore_item_wrapper";
      }
  };

public:
  PowerupStore():
  powerups()
  {}
  ~PowerupStore(){}
  void load(const ReaderObject& read );
  void store(Writer* serializer);
  void add(BonusType bonus);
  std::vector<std::shared_ptr<InventoryItem>>  getInventory();
  std::string getIdentifier()
  {
    return "powerupstore";
  }
};

#endif
