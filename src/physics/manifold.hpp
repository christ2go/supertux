#ifndef SUPERTUX_PHYSICS_MANIFOLD_HPP_INCLUDED
#define SUPERTUX_PHYSICS_MANIFOLD_HPP_INCLUDED
#include "math/vector.hpp"
class Body;
#define EPSILON 0.001
/**
 * Manifolds store information about collisions.
 * A and B are the bodies colliding.
 * The normal represents the vector along which the collision will be resolved.
 * (The normal is a unit vector.)
 */
struct Manifold {
        Body *A, *B; // Colliding bodies
        Vector normal;
        float penetrationDepth;
public:
        Manifold(Body* A, Body* B)
        {
                this->A = A;
                this->B = B;
                // Initialize normal to be zero.
                normal = Vector(0,0);
        }

        void solve();
        void positionalCorrection();

};
#endif
