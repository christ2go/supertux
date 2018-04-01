#include "physics/shapes/RectangleShape.hpp"

/**
 *  Fills the manifold
 */
void RectangleShape::fillManifold(Manifold* manifold)
{
  if(manifold->B->getType() == ShapeType.RectangleShape)
  {
    // Collision with another rectangle
    
  }
}
