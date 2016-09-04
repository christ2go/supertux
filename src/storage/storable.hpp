/**
 * An interface for storable items
 * They must only implement those 2 methods.
 *
 */
#ifndef HEADER_STORABLE_STORAGE_HPP
#define HEADER_STORABLE_STORAGE_HPP
#include "util/reader_collection.hpp"
#include "util/reader_mapping.hpp"
#include "util/writer.hpp"


class Storable
{
  public:
     virtual void load(const ReaderObject& read ) = 0;
     virtual void store(Writer* serializer) = 0;
     virtual std::string getIdentifier() = 0;
     virtual ~Storable() {}
     virtual bool isInventoryItem()
     {
       return false;
     }
     virtual bool isInventoryFactory()
     {
       return false;
     }

};


#endif
