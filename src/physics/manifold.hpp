#ifndef SUPERTUX_PHYSICS_MANIFOLD_HPP_INCLUDED
#define SUPERTUX_PHYSICS_MANIFOLD_HPP_INCLUDED
#include "math/vector.hpp"
#include "supertux/collision.hpp"
using namespace collision;
class Body;
#define EPSILON 0.001
/**
 * Manifolds store information about collisions.
 * A and B are the bodies colliding.
 * The normal represents the vector along which the collision will be resolved.
 * (The normal is a unit vector.)
 */
struct Manifold {
        std::shared_ptr<Body> A, B; // Colliding bodies
        // TODO Store collisionHits in manifold (one for A and one for B)
        CollisionHit hit_a, hit_b;
        Vector normal; 
        float penetrationDepth;
public:
        Manifold(std::shared_ptr<Body> A, std::shared_ptr<Body> B)
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
