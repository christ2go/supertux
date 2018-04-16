#ifndef SUPERTUX_HEADER_PHYSICS_WORLD_INCLUDED
#define SUPERTUX_HEADER_PHYSICS_WORLD_INCLUDED
/**
 *  The world contains all physical objects.
 *
 */
#include "physics/body.hpp"
#include "physics/broadphase.hpp"
#include <vector>
class World {
public:
  World();
  void addBody(Body& b);
  void removeBody(Body& b);
  // Main method: advances the simulation by time
  void timestep(float dt);
  // Sets the number of iterations used for collision response.
  void setIterations(int i);
  // Used to set the algorithm used for Broadphase
  void setBroadphase(BroadPhase& broadp);
private:
  // List of all bodies currently in the world
  std::vector<Body> bodies;
  // Number of iterations
  int m_iterations;
  // Class used for broadphase
  BroadPhase& broad;
};
#endif
