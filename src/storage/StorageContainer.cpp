#include "storage/StorageContainer.hpp"

bool
StorageContainer::add(std::shared_ptr<Storable> item)
{
  log_debug << "Storing: " << item->getIdentifier() << std::endl;
  if(m_items.count(item->getIdentifier()) == 0)
  {
      log_debug << "Assigning: " << std::endl;
      std::string name;
      name = item->getIdentifier();
      log_debug << name << std::endl;
      m_items.insert(std::make_pair(name,item));
  }
  return !(bool)m_items.count(item->getIdentifier());
}

Storable*
StorageContainer::get(const std::string& name)
{
  auto ptr = m_items[name].get();
  if(ptr) {
      return ptr;
  } else {
      return NULL;
  }
}

void
StorageContainer::load(ReaderCollection& reader)
{
  for(auto const& item:reader.get_objects())
  {
    // Check if item with id exists in our collection, then load it
    std::string name;
    item.get_mapping().get("type",name);
    // Check if item with type exists in table
    if(m_items[name].get())
    {
      m_items[name].get()->load(item);
    }else{
      log_warning << "Tried to load collectitem which isn't registered in this Version!" << std::endl;
    }
  }
}

void
StorageContainer::store(Writer* serializer)
{
  log_debug << "Storing Container objects" << std::endl;
  for ( auto &myPair : m_items )
  {
    log_debug << "Storing " << myPair.first << std::endl;
    serializer->start_list("item");
    myPair.second.get()->store(serializer);
    serializer->write("type",myPair.second.get()->getIdentifier());
    serializer->end_list("item");
  }
}
