#include "physics/world.hpp"

void World::setIterations(int i)
{
  if(i <= 0)
    return;
  m_iterations = i;
}

void World::addBody(Body& b)
{
  bodies.push_back(b);
}

void World::removeBody(Body& b)
{
  bodies.remove(bodies.find(b));
}

void World::timestep(float dt)
{
  // Initialize manifolds
  std::vector< Manifold > manifolds;
  manifolds = broad.generateContacts(bodies);
}

void World::setBroadphase(BroadPhase& broadp)
{
  broad = broadp;
}
