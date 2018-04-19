#ifndef SUPERTUX_PHYSICS_SHAPES_RECTANGLE_HPP_INCLUDED
#define SUPERTUX_PHYSICS_SHAPES_RECTANGLE_HPP_INCLUDED
#include "physics/shape.hpp"
/**
 *  This shape represents axis aligned bounding boxes.
 *
 */
class RectangleShape : public Shape {
public:
  RectangleShape();
  /** 
   *  Initializes with a specific rectangle (e.g.) an objects bbox
   */
  RectangleShape(Rectf& bbox);
  const Rectf& getAABB()
  {
    return rectangle;
  }
  
  void set_size(int w, int h)
  {
    rectangle.set_width(w);
    rectangle.set_height(h);
  }
  
  void set_position(Vector position)
  {
    rectangle.move(position);
  }
  
  void fillManifold(Manifold* M);
  
  ~RectangleShape(){}
private:
  Rectf& rectangle;
};
#endif
