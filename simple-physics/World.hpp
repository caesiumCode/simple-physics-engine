#ifndef World_hpp
#define World_hpp

#include "Math.hpp"
#include "Solid.hpp"

namespace sp {

class World
{
public:
    World();
    
    void create(float x_min, float x_max, float y_min, float y_max);
    
    void add_circle(Vector position, float radius);
    void add_square(Vector position, float side);
    
    const std::vector<Solid>&   get_solids() const;
    const BoundingBox&          get_borders() const;
    
    Solid& get_solid(int i);
    
    void update(float dt);
    
private:
    BoundingBox borders;
    
    std::vector<Solid> solids;
};

}

#endif /* World_hpp */
