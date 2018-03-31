#ifndef SUPERTUX_PHYSICS_MANIFOLD_HPP_INCLUDED
#define SUPERTUX_PHYSICS_MANIFOLD_HPP_INCLUDED
/**
 * Manifolds store information about collisions.
 * A and B are the bodies colliding.
 * The normal represents the vector along which the collision will be resolved. 
 */
struct Manifold {
  Body* A, B; // Colliding bodies
  Vector normal;
  float penetrationDepth;

public:
  Manifold(Body* A, Body* B)
  {
    this->A = A;
    this->B = B;
  }

};
#endif
