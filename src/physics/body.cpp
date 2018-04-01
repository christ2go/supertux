#include "physics/body.hpp"
#include <iostream>
#include <limits>
#include "supertux/sector.hpp"

void Body::applyForce(Vector forceT)
{
  this->force += forceT;
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

Vector Body::get_position()
{
  return position;
}

Vector Body::get_force()
{
  return force;
}

Vector Body::get_velocity()
{
  return velocity;
}

void Body::set_velocity(Vector vel)
{
  velocity = vel;
}

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
   if(useGravity)
   {
     // Gravity only affects the x movement
     gravity.x = Sector::current()->get_gravity() * gravityModifier * 100.0f;
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
void Body::setStatic()
{
  inv_mass = 0;
  mass = std::numeric_limits<float>::infinity();
}
/**
 *  Sets the objects shape.
 */
void Body::set_shape(Shape* new_shape)
{
  shape = new_shape;
}
