#ifndef SUPERTUX_PHYSICS_MANIFOLD_HPP_INCLUDED
#define SUPERTUX_PHYSICS_MANIFOLD_HPP_INCLUDED
class Body;

#include "math/vector.hpp"
#include "physics/body.hpp"
/**
 * Manifolds store information about collisions.
 * A and B are the bodies colliding.
 * The normal represents the vector along which the collision will be resolved.
 */
struct Manifold {
  Body *A, *B; // Colliding bodies
  Vector normal;
  float penetrationDepth;
  // Contact points
  Vector contacts[2];
  int contactCount;
public:
  Manifold(Body* A, Body* B)
  {
    this->A = A;
    this->B = B;
  }

};
#endif
