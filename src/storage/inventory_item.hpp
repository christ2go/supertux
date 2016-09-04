#include "storage/storable.hpp"
#include <vector>
#include "gui/inventory_dialog.hpp"
#include <functional>
#ifndef HEADER_INVENTORYITEM_STORAGE_HPP
#define HEADER_INVENTORYITEM_STORAGE_HPP

class InventoryItem : public Storable {
  public:
    /**
     *  Should this item be usable inlevel?
     */
    virtual bool inlevel()
    {
      return true;
    };

    virtual bool add() = 0;

    virtual bool isInventoryItem()
    {
      return true;
    }

    virtual bool isStorable()
    {
      return true;
    }
    /**
     * Return true if the objects are combineable
     */
    virtual bool combineable(InventoryItem& comb)
    {
      return false;
    }

    virtual void use() = 0;

    virtual std::shared_ptr<InventoryItem> combine(InventoryItem& comb) = 0;

    std::shared_ptr<InvItem> getItem()
    {
      std::shared_ptr<InvItem> it(new InvItem(*this));
      it->name = getIdentifier();
      it->plural = getIdentifier()+"s";
      return it;
    }
};



class MultipleItem: public InventoryItem {
  public:
    virtual bool add() = 0;
    virtual int getCount() = 0;
};

class InventoryFactory : public Storable {
  public:
    virtual std::vector<std::shared_ptr<InventoryItem>> getInventory() = 0;
    bool isInventoryFactory()
    {
      return true;
    }
};

class FactoryItemWrapper : public InventoryItem {
public:
  void store(Writer* serializer){};
  void load(const ReaderObject& read){};
  bool inlevel()
  {
    return true;
  };
  bool isStorable()
  {
    return false;
  }
  bool add(){
    return true;
  };

  virtual bool isInventoryItem()
  {
    return true;
  }
  /**
   * Return true if the objects are combineable
   */
  virtual void use()
  {

  }

  std::shared_ptr<InventoryItem> combine(InventoryItem& comb)
  {
    std::shared_ptr<InventoryItem> a;
    return a;
  }

};

#endif
