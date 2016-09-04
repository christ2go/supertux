#include "storage/PowerupStore.hpp"


void
PowerupStore::load(const ReaderObject& read )
{
  auto mapping = read.get_mapping();
  ReaderCollection items;
  if(!mapping.get("powerups",items))
  {
      log_fatal << "Ill formed powerup data";
      throw std::runtime_error("Ill formed powerup storage data.");
  }
  for(const auto& item:items.get_objects())
  {
      if(!(item.get_name() == "powerup")) {
          log_fatal << "Ill formed powerup storage (Exspected \"(powerup ...)\" in Items)).";
          throw std::runtime_error("Ill formed save-data file (Exspected Item in Items)).");
      }

      auto imap = item.get_mapping();
      std::string type;
      int anm;
      imap.get("type",type);
      imap.get("anmount",anm);
      powerups[Player::string_to_bonus(type)] = anm;

  }
}

void
PowerupStore::store(Writer* serializer)
{
  serializer->start_list("powerups");
  for(auto pair:powerups)
  {
    serializer->start_list("powerup");
    serializer->write("type",Player::bonus_to_string(pair.first));
    serializer->write("anmount",pair.second);
    serializer->end_list("powerup");
  }
  serializer->end_list("powerups");
}

void
PowerupStore::add(BonusType bonus)
{
  if(powerups[bonus])
  {
    powerups[bonus]++;
  }else{
    powerups[bonus] = 1;
  }
}

std::vector<std::shared_ptr<InventoryItem>>
PowerupStore::getInventory()
{
  std::vector<std::shared_ptr<InventoryItem>> vect;
  for(std::pair<BonusType,int> pair:powerups)
  {
    if(pair.second > 0)
    {
      std::shared_ptr<PowerUpInventoryWrapper> i(new PowerUpInventoryWrapper(*this,pair.first));
      vect.push_back(i);
    }
  }
  return vect;
}
