#include "World.hpp"

namespace sp
{

World::World()
{
    solids.clear();
}

void World::create(float x_min, float x_max, float y_min, float y_max)
{
    this->borders = {x_min, x_max, y_min, y_max};
}

void World::add_circle(Vector position, float radius)
{
    Solid solid;
    
    solid.create_circle(radius);
    solid.set_position(position);
    
    solids.push_back(solid);
}

void World::add_square(Vector position, float side)
{
    Solid solid;
    
    solid.create_square(side);
    solid.set_position(position);
    
    solids.push_back(solid);
}

const std::vector<Solid>& World::get_solids() const
{
    return solids;
}

const BoundingBox& World::get_borders() const
{
    return borders;
}

Solid& World::get_solid(int i)
{
    return solids[i];
}

void World::update(float dt)
{
    for (int i = 0; i < solids.size(); i++)
    {
        for (int j = i+1; j < solids.size(); j++)
        {
            bool collision = Solid::check_collision(solids[i], solids[j]);
            
            if (collision) Solid::solve_collision(solids[i], solids[j]);
        }
    }
}

}
