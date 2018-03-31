#include "physics/body.hpp"

void Body::applyForce(Vector force)
{
  this->force += force;
}

float Body::get_mass()
{
  return mass;
}

float Body::get_inv_mass()
{
  return inv_mass;
}

float Body::get_friction()
{
  return friction;
}

Vector get_position();

Vector get_force();

Vector get_velocity();

void set_velocity(Vector vel);

/**
 * Calculates the bodies next movement.
 * Uses semi-explicit euler integration.
 */
 void Body::step(float dt)
 {
   // Static objects do not move
   if(get_inv_mass() == 0.0)
    return;
   // Declare a Vector for gravity.
   Vector gravity(0,0);
   Vector acceleration = get_acceleration();
   if(gravity_enabled)
   {
     // Gravity only affects the x movement
     gravity.x = Sector::current()->get_gravity() * gravity_modifier * 100.0f;
   }
   velocity += (acceleration+gravity) * dt;
   // Save last movement (for later)
   movement = velocity*dt;
   position += movement;
 }
/**
 *  Sets this object to be static
 *  Static objects have infinite mass, and an inverse mass of zero.
 *  Can be used for all objects in collision group static.
 */
void Body::set_static()
{
  m_inv_mass = 0;
  m_mass = std::numeric_limits<float>::infinity;
}
