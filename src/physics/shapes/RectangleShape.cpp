#include "physics/shapes/RectangleShape.hpp"

/**
 *  Fills the manifold with collision data
 */
void RectangleShape::fillManifold(Manifold* manifold)
{
  // Collision with another rectangle
  if(manifold->B->getType() == ShapeType.RectangleShape)
  {
    // Get the shapes
    RectangleShape* shape_a = this;
    RectangleShape* shape_b = static_cast<RectangleShape>(B->get_shape());
    // AABB is the actual shape for Rectangles
    auto aabb_a = shape_a->getAABB();
    auto aabb_b = shape_b->getAABB();
    Vector n = manifold->A->get_position()-manifold->B->get_position();
    // Both axes overlap => calculate penetration for each axis
    // by projecting rectangles onto that axis and check for overlap
    float penetrationX = interval_overlap(aabb_a.left, aabb_a.right, aabb_b.left, aabb_b.right);
    float penetrationY = interval_overlap(aabb_a.bottom, aabb_a.top, aabb_b.bottom, aabb_b.top);
    // Use axis of least penetration for collision resolution
    if(penetrationX >= penetrationY)
    {
      manifold->penetrationDepth = penetrationY;
      if(n.y > 0){
        manifold->normal.y = -1;
      }else{
        manifold->normal.y = 1;
      }
    }else{
      manifold->penetrationDepth = penetrationX;
      if(n.x > 0)
      {
        manifold->normal.x = -1;
      }else{
        manifold->normal.x = 1;
      }
    }

  }
}
