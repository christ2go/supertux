#include "physics/world.hpp"
#include "physics/SimpleBroadPhase.hpp"
#include "util/log.hpp"
void PhysicWorld::setIterations(int i)
{
        m_iterations = std::max(i,1);
}

void PhysicWorld::addBody(Body* b)
{
    bodies.push_back(b);
}

void PhysicWorld::removeBody(Body* b)
{
        //bodies.remove(bodies.find(b));
}

void PhysicWorld::timestep(float dt)
{
      log_debug << "PhysicWorld is timestepping" << std::endl;
        // Initialize manifolds
        std::vector< Manifold > manifolds;
        
        manifolds = broad->generateContacts(bodies);
        
        for(auto& manifold: manifolds)
        {
                // Initialize the manifold
                if(manifold.A->get_shape() == NULL || manifold.B->get_shape() == NULL)
                  continue;
                manifold.A->get_shape()->fillManifold(&manifold);
                // Alert both objects of the contact 
                if(manifold.A->get_contact_listener() != NULL)
                {
                  manifold.A->get_contact_listener()->notifyContact(manifold);
                }
                if(manifold.B->get_contact_listener() != NULL)
                {
                  manifold.B->get_contact_listener()->notifyContact(manifold);
                }
        }
        
        // Manifold information has been generated, let's solve
        for(int i = 0; i<m_iterations; i++)
        {
                for(auto& manifold: manifolds)
                {
                  // TODO Check if manifold is enabled
                        // Apply impulse
                        manifold.solve();
                }
        }
        // Integrate Velocity 
        for(auto& b : bodies)
        {
          b->step(dt);
          b->move();
        }
        // Correct positions 
      for(auto& m : manifolds)
       {
          m.solve();
       }
      log_debug << "Resetting forces" << std::endl;
        // Clear all forces 
        for(auto b:bodies)
        {
          b->set_force( Vector(0, 0) );
        }
        log_debug << "Forces reset complete" << std::endl;
        // Timestep completed
        log_debug << "PhysicWorld timestep done." << std::endl;
}

void PhysicWorld::setBroadphase(std::unique_ptr<BroadPhase> broadp)
{
  broad = std::move(broadp);
}

PhysicWorld::PhysicWorld(){
  broad = std::make_unique<SimpleBroadPhase>();
}
