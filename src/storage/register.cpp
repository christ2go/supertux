#include "storage/StorageContainer.hpp"
void registerStorageitems(StorageContainer* container)
{
  std::shared_ptr<Storable> powerup(new PowerupStore());
  container->add(std::move(powerup));
}
