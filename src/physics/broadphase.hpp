/**
 * Interface for broadphase data structure.
 * Implements a method to generate Manifolds from a list of bodies.
 */
 #ifndef SUPERTUX_PHYSICS_BROADPHASE_HPP_INCLUDED
 #define SUPERTUX_PHYSICS_BROADPHASE_HPP_INCLUDED
 #include "physics/body.hpp"
 #include "physic/manifold.hpp"
 class BroadPhase {
  virtual std::vector< Manifold > generateContacts(std::vector<Body>& b);
 };
 #endif
