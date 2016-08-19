#include "storage/PowerupStore.hpp"

void
PowerupStore::addFireflower()
{
  fireflowers++;
}

void
PowerupStore::addIceflower()
{
  airflowers++;
}


void
PowerupStore::addEarthflower()
{
  earthflowers++;
}

void
PowerupStore::addAirflower()
{
  airflowers++;
}



bool
PowerupStore::useIceflower()
{
  if(iceflowers > 0)
  {
    iceflowers--;
    return true;
  }
  return false;
}

bool
PowerupStore::useAirflower()
{
  if(airflowers > 0)
  {
    airflowers--;
    return true;
  }
  return false;
}

bool
PowerupStore::useFireflower()
{
  if(fireflowers > 0)
  {
    fireflowers--;
    return true;
  }
  return false;
}

bool
PowerupStore::useEarthflower()
{
  if(earthflowers > 0)
  {
    earthflowers--;
    return true;
  }
  return false;
}

void
PowerupStore::load(const ReaderObject& read )
{
  if(!read.get_mapping().get("fire",fireflowers)) fireflowers = 0;
  if(!read.get_mapping().get("earth",earthflowers)) earthflowers = 0;
  if(!read.get_mapping().get("air",airflowers)) airflowers = 0;
  if(!read.get_mapping().get("ice",iceflowers)) iceflowers = 0;
}

void
PowerupStore::store(Writer* serializer)
{
  serializer->write("fire",fireflowers);
  serializer->write("ice",iceflowers);
  serializer->write("air",airflowers);
  serializer->write("earth",earthflowers);
}
