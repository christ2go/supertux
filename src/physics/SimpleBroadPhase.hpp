#ifndef SUPERTUX_HEADER_PHYSICS_SIMPLE_BROADPHASE_HPP_INCLUDED
#define SUPERTUX_HEADER_PHYSICS_SIMPLE_BROADPHASE_HPP_INCLUDED
class SimpleBroadPhase : BroadPhase {
public:
  std::vector< Manifold > generateContacts(std::vector<Body>& b)
  {
    std::vector< Manifold > manifolds();
    // Iterate over all pairs of bodies and check if bounding boxes overlap
    for(auto i = b.begin(); i != b.end(); ++i)
    {
      for(auto j = i+1; j != b.end(); ++j)
      {
        // Check if bounding box intersects
        Rectf a = (*i).getAABB();
        Rectf b = (*j).getAABB();
        // Check if x axis overlaps
        max_ax = std::max(a.left, a.right);
        max_bx = std::max(b.left, b.right);

        min_ax = std::min(a.left, a.right);
        min_bx = std::min(b.left, b.right);

        max_ay = std::max(a.bottom, a.top);
        max_by = std::max(b.bottom, b.top);

        min_ay = std::min(a.bottom, a.top);
        min_by = std::min(b.bottom, b.top);

        // Check if y axis overlap
        if(max_ax < min_bx || min_ax > max_bx)
          return false;
        if(max_ay < min_by || min_ay > max_by)
          return false;
        // Both overlap => Initialize Manifold
        manifolds.emplace_back(*i,*j);
      }
    }
  }
};
#endif
