#ifndef SUPERTUX_HEADER_PHYSICS_SHAPE_HPP_INCLUDED
#define SUPERTUX_HEADER_PHYSICS_SHAPE_HPP_INCLUDED
#include "physics/manifold.hpp"
#include "math/rectf.hpp"
enum ShapeType {
  TRectangleShape = 0
};
class Shape {
    /**
     *  Holds information about an objects shape
     */
   private:
     ShapeType typ;
     Vector position;
   public:
     ShapeType getType()
     {
       return typ;
     }
     /**
      * Every shape has to implement this method,
      * which will check for a collision against a different shape.
      * Convention: The manifolds Shape A is this Shape.
      */
     virtual void fillManifold(Manifold* M) = 0;
     /**
      * Returns a smallest axis aligned rectangle containing the whole shape.
      * Used for broad phase collision detection.
      */  
     virtual const Rectf& getAABB() = 0;
     /** 
      * Sets the objects position.
      */
     void update_position(Vector pos)
     {
       position = pos;
     }
     
     virtual void move(Vector movement)
     {
       position += movement;
     }
     
     Vector get_position()
     {
       return position;
     }
    virtual ~Shape(){}
};
#endif
