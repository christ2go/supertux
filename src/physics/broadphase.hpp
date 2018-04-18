/**
 * Interface for broadphase data structure.
 * Implements a method to generate Manifolds from a list of bodies.
 */
 #ifndef SUPERTUX_PHYSICS_BROADPHASE_HPP_INCLUDED
 #define SUPERTUX_PHYSICS_BROADPHASE_HPP_INCLUDED
 #include "physics/body.hpp"
 #include "physics/manifold.hpp"
 class BroadPhase {
 public: 
  virtual std::vector< Manifold > generateContacts(std::vector<Body*>& b) = 0;
  virtual ~BroadPhase(){};
 };
 #endif
