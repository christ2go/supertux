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
private:
  float x1, y1, x2, y2;
};
#endif
