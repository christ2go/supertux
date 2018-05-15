#ifndef SUPERTUX_HEADER_PHYSICS_SIMPLE_BROADPHASE_HPP_INCLUDED
#define SUPERTUX_HEADER_PHYSICS_SIMPLE_BROADPHASE_HPP_INCLUDED
class SimpleBroadPhase : public BroadPhase {
public:
  std::vector< Manifold > generateContacts(std::vector< Body*  >& list)
  {
    std::vector< Manifold > manifolds;
    // Iterate over all pairs of bodies and check if bounding boxes overlap
    for(auto i = list.begin(); i != list.end(); ++i)
    {
      for(auto j = i+1; j != list.end(); ++j)
      {
        // Check if bounding box intersects
        Rectf a = (*i)->get_shape()->getAABB();
        Rectf b = (*j)->get_shape()->getAABB();
        // Check if x axis overlaps
        double max_ax = std::max(a.get_left(), a.get_right());
        double max_bx = std::max(b.get_left(), b.get_right());

        double min_ax = std::min(a.get_left(), a.get_right());
        double min_bx = std::min(b.get_left(), b.get_right());

        double max_ay = std::max(a.get_bottom(), a.get_top());
        double max_by = std::max(b.get_bottom(), b.get_top());

        double min_ay = std::min(a.get_bottom(), a.get_top());
        double min_by = std::min(b.get_bottom(), b.get_top());

        // Check if y axis overlap
        if(max_ax < min_bx || min_ax > max_bx)
          continue;
        if(max_ay < min_by || min_ay > max_by)
          continue;
        // Both overlap => Initialize Manifold
        manifolds.emplace_back(*i,*j);
      }
    }
    return manifolds;
  }
  
  ~SimpleBroadPhase()
  {
    
  }
};
#endif
