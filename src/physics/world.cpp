#include "physics/world.hpp"
#include "physics/SimpleBroadPhase.hpp"
#include "util/log.hpp"
void World::setIterations(int i)
{
        m_iterations = std::max(i,1);
}

void World::addBody(Body* b)
{
  log_debug << "Adding body" << std::endl;
        bodies.push_back(b);
  log_debug << "Add finished" << std::endl;
}

void World::removeBody(Body* b)
{
        //bodies.remove(bodies.find(b));
}

void World::timestep(float dt)
{
        log_debug << "World is timestepping" << std::endl;
        // Initialize manifolds
        std::vector< Manifold > manifolds;
        manifolds = broad->generateContacts(bodies);
        for(auto& manifold: manifolds)
        {
                // Initialize the manifold
                if(manifold.A->get_shape() == NULL || manifold.B->get_shape() == NULL)
                  continue;
                manifold.A->get_shape()->fillManifold(&manifold);
        }
        // Manifold information has been generated, let's solve
        for(int i = 0; i<m_iterations; i++)
        {
                for(auto& manifold: manifolds)
                {
                        // Apply impulse
                        manifold.solve();
                }
        }
        // Integrate Velocity 
        for(auto& b : bodies)
        {
          b->step(dt);
        }
        // Correct positions 
        for(auto& m : manifolds)
        {
          //m.solve();
        }
        log_debug << "Resetting forces" << std::endl;
        // Clear all forces 
        for(auto b:bodies)
        {
          b->set_force( Vector(0, 0) );
        }
        log_debug << "Forces reset complete" << std::endl;
        // Timestep completed
        log_debug << "World timestep done." << std::endl;
}

void World::setBroadphase(BroadPhase* broadp)
{
        broad = broadp;
}