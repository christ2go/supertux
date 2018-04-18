#ifndef SUPERTUX_PHYSICS_BODY_HPP_INCLUDED
#define SUPERTUX_PHYSICS_BODY_HPP_INCLUDED
#include "math/vector.hpp"
#include "physics/shape.hpp"
/**
 *  Bodies are the main class for everything physics related.
 *  A body stores an objects position, movement and velocity in the current world.
 */

enum Body_Type {
  BODY_DYNAMIC, /** default rigid bodies */
  BODY_KINEMATIC, /** does not collide with static bodies, used for moving platforms */
  BODY_STATIC /** static bodies, do not move */
};

class Body {
public:
  Body();
  // Applies a force to the object
  void applyForce(Vector forceT);

  void set_force(Vector Nforce);
  
  float get_mass() const;

  float get_inv_mass() const;

  float get_friction() const;

  Vector get_position() const;

  Vector get_force() const;

  Vector get_velocity() const;

  void set_velocity(Vector vel);
  // Simulate movement (integrate Forces)
  void step(float dt);

  // Methods for convinience
  void set_velocity_x();
  void set_velocity_y();

  void set_shape(Shape* new_shape);

  void set_type(Body_Type t);
  Shape* get_shape() const;
  // Apply impulse of magnitude j
  void applyLinearImpulse(float j);
  // Methods for setting and getting position 
  void set_pos(const Vector& pos);
private:
  Vector position;
  Vector velocity;
  // F
  Vector force;
  // don't save acceleration (A, can be derived via F = m*A)
  Vector get_acceleration();
  // mass of the body
  float mass;
  // Also store the inverse mass
  float inv_mass;
  // Store friction
  float friction = 1;
  // A group used for determining if this body can collide with different body.
  int collision_group;
  // Gravity modifier
  float gravityModifier = 1.0;
  // Restitution (0 for many objects in supertux)
  float restitution;
  // Allow objects not to use gravity.
  bool useGravity = true;
  // Stores the last movement (updated whenever step() is called)
  Vector movement;
  // Shape of the object (e.g. bounding box or slope or polygon)
  Shape* shape;
  // Type of the body
  Body_Type type;
};
#endif
