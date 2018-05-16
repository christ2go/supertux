#ifndef SUPERTUX_HEADER_PHYSICS_CONTACT_LISTENER_INCLUDED 
#define SUPERTUX_HEADER_PHYSICS_CONTACT_LISTENER_INCLUDED
#include "physics/manifold.hpp"
class ContactListener {
  /** 
   * Called whenever a collision with another item is detected.
   */
 public: 
  virtual void notifyContact(Manifold& m);
  virtual ~ContactListener();
};
#endif