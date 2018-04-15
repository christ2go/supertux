#ifndef SUPERTUX_HPP_PHYSICS_UTIL_INCLUDED
#define SUPERTUX_HPP_PHYSICS_UTIL_INCLUDED
/**
 *  Calculates the size of the interval intersection between [a,b] and [c,d]
 *
 */
double interval_overlap(double a, double b,double c, double d)
{
  double astart = std::min(a,b);
  double aend   = std::max(a,b);
  double bstart = std::min(c,d);
  double bend   = std::max(c,d);

  double istart = std::max(astart,bstart);
  double iend   = std::min(aend,bend);
  if(istart >= iend)
    return 0;
  return iend-istart;
}
#endif
