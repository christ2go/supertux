#include "physics/body.hpp"
#include <iostream>
#include <limits>
#include "supertux/sector.hpp"
#include "util/log.hpp"
void Body::applyForce(Vector forceT)
{
  this->force += forceT;
}

void Body::set_force(Vector Nforce)
{
  this->force = Nforce;
}


float Body::get_mass() const
{
  return mass;
}

float Body::get_inv_mass() const 
{
  return inv_mass;
}

float Body::get_friction() const 
{
  return friction;
}

Vector Body::get_position() const 
{
  return position;
}

Vector Body::get_force() const
{
  return force;
}

Vector Body::get_velocity() const
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
   log_debug << "Moved by gravity" << dt << " " <<  std::endl;
 }
/**
 *  Sets the objects shape.
 */
void Body::set_shape(Shape* new_shape)
{
  shape = new_shape;
}

Shape* Body::get_shape() const
{
  return shape;
}

void Body::set_type(Body_Type t)
{
  type = t;
  if(type == BODY_STATIC || type == BODY_KINEMATIC)
  {
    inv_mass = 0;
    mass = std::numeric_limits<float>::infinity();
  }
}

Vector Body::get_acceleration()
{
  return force*inv_mass;
}

void Body::applyLinearImpulse(float j)
{
  
}

Body::Body():
force( Vector(0,0) )
{
}