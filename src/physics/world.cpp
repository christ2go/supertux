#include "physics/world.hpp"

void World::setIterations(int i)
{
  m_iterations = std::max(i,1);
}

void World::addBody(Body& b)
{
  bodies.push_back(b);
}

void World::removeBody(Body& b)
{
  //bodies.remove(bodies.find(b));
}

void World::timestep(float dt)
{
  // Initialize manifolds
  std::vector< Manifold > manifolds;
  manifolds = broad.generateContacts(bodies);
  for(auto& manifold: manifolds)
  {
    // Initialize the manifold
    manifold.A->get_shape()->fillManifold(manifold);
  }
  // Manifold information has been generated, let's solve
  for(int i = 0;i<m_iterations;i++)
  {
    for(auto& manifold: manifolds)
    {
      // Apply impulse
      
      // Positional correction
    }
  }

}

void World::setBroadphase(BroadPhase& broadp)
{
  broad = broadp;
}
