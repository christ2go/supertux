#include "storage/storable.hpp"
#include "object/player.hpp"
#ifndef HEADER_STORABLE_POWERUPSTORAGE_HPP
#define HEADER_STORABLE_POWERUPSTORAGE_HPP

class PowerupStore: public Storable
{
private:
  std::map<BonusType,int> powerups;
public:
  PowerupStore():
  powerups()
  {}
  ~PowerupStore(){}
  void load(const ReaderObject& read );
  void store(Writer* serializer);
  void add(BonusType bonus);
  std::string getIdentifier()
  {
    return "powerupstore";
  }
};

#endif
