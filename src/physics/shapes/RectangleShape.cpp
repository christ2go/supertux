#include "physics/shapes/RectangleShape.hpp"
#include "physics/body.hpp"
#include "physics/shape.hpp"
#include "physics/utils.hpp"

RectangleShape::RectangleShape(Rectf& bbox):
rectangle(bbox)
{
  rectangle = bbox;
}

/**
 *  Fills the Manifold with collision data
 */
void RectangleShape::fillManifold(Manifold* M)
{
  // Collision with another rectangle
  if(M->B->get_shape()->getType() == TRectangleShape)
  {
    // Get the shapes
    RectangleShape* shape_a = this;
    RectangleShape* shape_b = static_cast<RectangleShape*>(M->B->get_shape());
    // AABB is the actual shape for Rectangles
    auto aabb_a = shape_a->getAABB();
    auto aabb_b = shape_b->getAABB();
    Vector n = M->A->get_position()-M->B->get_position();
    // Both axes overlap => calculate penetration for each axis
    // by projecting rectangles onto that axis and check for overlap
    float penetrationX = interval_overlap(aabb_a.get_left(), aabb_a.get_right(), aabb_b.get_left(), aabb_b.get_right());
    float penetrationY = interval_overlap(aabb_a.get_bottom(), aabb_a.get_top(), aabb_b.get_bottom(), aabb_b.get_top());
    // Use axis of least penetration for collision resolution
    if(penetrationX >= penetrationY)
    {
      M->penetrationDepth = penetrationY;
      if(n.y > 0){
        M->normal.y = -1;
      }else{
        M->normal.y = 1;
      }
    }else{
      M->penetrationDepth = penetrationX;
      if(n.x > 0)
      {
        M->normal.x = -1;
      }else{
        M->normal.x = 1;
      }
    }

  }
}
