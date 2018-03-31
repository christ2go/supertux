#ifndef SUPERTUX_PHYSICS_BODY_HPP_INCLUDED
#define SUPERTUX_PHYSICS_BODY_HPP_INCLUDED
/**
 *  Bodies are the main class for everything physics related.
 *  A body stores an objects position, movement and velocity in the current world.
 */
class Body {
public:
  // Applies a force to the object
  void applyForce(Vector force);

  float get_mass();

  float get_inv_mass();

  float get_friction();

  Vector get_position();

  Vector get_force();

  Vector get_velocity();

  void set_velocity(Vector vel);
  // Simulate movement (integrate Forces)
  void step(float dt);
  // Set an object to be static (used for walls, etc)
  void setStatic();
private:
  Vector position;
  Vector velocity;
  // F
  Vector force;
  // save acceleration (A, can be derived via F = m*A)
  Vector get_acceleration();
  // mass of the body
  float mass;
  // Also store the inverse mass
  float inv_mass;
  // Store friction
  float friction;
  // A group used for determining if this body can collide with different body.
  int collision_group;
  // Gravity modifier
  float gravity;
  // Restitution (0 for many objects in supertux)
  float restitution;
  // Allow objects not to use gravity.
  bool useGravity;
  // Stores the last movement (updated whenever step() is called)
  Vector movement;
};
#endif
