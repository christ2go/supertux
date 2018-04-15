#include "physics/shapes/RectangleShape.hpp"

/**
 *  Fills the manifold with collision data
 */
void RectangleShape::fillManifold(Manifold* manifold)
{
  // Collision with another rectangle
  if(manifold->B->getType() == ShapeType.RectangleShape)
  {
    Vector n = manifold->A->get_position()-manifold->B->get_position();
    // Both axes overlap => calculate penetration for each axis
    // by projecting rectangles onto that axis and check for overlap
    float penetrationX = interval_overlap(0,0,1,1);
    // Use axis of least penetration for collision resolution
    float penetrationY = interval_overlap(0,1,0.5,1);
    if(penetrationX > penetrationY)
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
        manifold->normal.y = 1;
      }
    }

  }
}
