#include "storage/storable.hpp"
#ifndef HEADER_STORABLE_POWERUPSTORAGE_HPP
#define HEADER_STORABLE_POWERUPSTORAGE_HPP

class PowerupStore: public Storable
{
private:
  int fireflowers = 0;
  int airflowers = 0;
  int iceflowers = 0;
  int earthflowers = 0;
public:
  void addFireflower();
  void addIceflower();
  void addAirflower();
  void addEarthflower();

  bool useFireflower();
  bool useIceflower();
  bool useAirflower();
  bool useEarthflower();
  PowerupStore(){}
  ~PowerupStore(){}
  void load(const ReaderObject& read );
  void store(Writer* serializer);
  std::string getIdentifier()
  {
    return "powerupstore";
  }
};

#endif
