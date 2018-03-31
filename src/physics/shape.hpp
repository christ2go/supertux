enum ShapeType {
  AABB = 0
};
class Shape {
    /**
     *  Holds information about an objects shape
     */
   private:
     ShapeType typ;
   public:
     ShapeType getType()
     {
       return typ;
     }
     /**
      * Every shape has to implement this method,
      * which will check for a collision against a different shape.
      */
     virtual void fillManifold(Manifold* M) = 0;
     /**
      * Returns a smallest axis aligned rectangle containing the whole shape.
      * Used for broad phase collision detection.
      */
     virtual Rectf getAABB();
};
