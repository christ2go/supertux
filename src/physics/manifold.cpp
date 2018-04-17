#include "physics/manifold.hpp"
#include "physics/body.hpp"

void Manifold::solve()
{
        // If both objects are static/kinematic do not resolve
        if((A->get_inv_mass()+B->get_inv_mass()) <= EPSILON )
        {
          return;
        }

        // TODO If both objects are moving objects check if move should be aborted or continued
        // use the generated CollisionHits
        
        Vector relativeVel = B->get_position()-A->get_position();
        // Are the objects moving away from one another?
        if(relativeVel*this->normal > 0)
        {
          return;
        }
        // Restitution
        float e = std::min(1,1);
        // Calculate the impulse
        float numerator = (-(1+e))*(relativeVel*this->normal);
        float j = numerator/(A->get_inv_mass()+B->get_inv_mass());
        // Apply linear impulse to push the bodies apart (scale the impulse by inverse mass)
        // (so that static bodies will not move)
        A->applyLinearImpulse(-j*A->get_inv_mass());
        B->applyLinearImpulse(j*B->get_inv_mass());
        // Friction modification

        // Done with the collision handling.
}
