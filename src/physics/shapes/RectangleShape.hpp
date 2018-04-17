#ifndef SUPERTUX_PHYSICS_SHAPES_RECTANGLE_HPP_INCLUDED
#define SUPERTUX_PHYSICS_SHAPES_RECTANGLE_HPP_INCLUDED
#include "physics/shape.hpp"
/**
 *  This shape represents axis aligned bounding boxes.
 *
 */
class RectangleShape : Shape {
public:
  RectangleShape();
  const Rectf& getAABB()
  {
    return rectangle;
  }
private:
  Rectf rectangle;
};
#endif
