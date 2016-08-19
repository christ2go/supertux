#ifndef HEADER_STORABLE_STORAGECONTAINER_HPP
#define HEADER_STORABLE_STORAGECONTAINER_HPP
#include "storage/storable.hpp"
#include <map>
#include <memory>
#include "util/log.hpp"
#include "storage/PowerupStore.hpp"
class StorageContainer;
void registerStorageitems(StorageContainer* container);

class StorageContainer
{
  public:
    bool add(std::shared_ptr<Storable> item);
    Storable* get(const std::string& name);
    void load(ReaderCollection& reader);
    void store(Writer* serializer);
    StorageContainer():
      m_items()
    {
      log_debug << "Constructing StorageContainer" << std::endl;
      registerStorageitems(this);
    }
  private:
    std::map<std::string,std::shared_ptr<Storable>> m_items;
};


#endif
