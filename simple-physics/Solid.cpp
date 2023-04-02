#include "Solid.hpp"


namespace sp
{

Solid::Solid()
{
    
}

void Solid::create_circle(float radius)
{
    this->property.shape = CIRCLE;
    this->property.vertices.clear();
    this->property.vertices = {{radius, 0.f}};
}

void Solid::create_square(float side)
{
    this->property.shape = SQUARE;
    this->property.vertices.clear();
    this->property.vertices = {
        {-side/2.f, side/2.f},
        {side/2.f,  side/2.f},
        {side/2.f,  -side/2.f},
        {-side/2.f, -side/2.f}
    };
}

void Solid::set_position(Vector position)
{
    this->state.position = position;
}

void Solid::set_static(bool state)
{
    this->property.is_static = state;
    this->property.inv_mass = 0;
}

const Property& Solid::get_property() const
{
    return property;
}

const State& Solid::get_state() const
{
    return state;
}


void Solid::step(Vector amount)
{
    state.position += amount;
}

bool Solid::check_collision(const Solid& solid1, const Solid& solid2)
{
    if (solid1.property.shape == CIRCLE)
    {
        if (solid2.property.shape == CIRCLE)
        {
            float min_dist = solid1.property.get_radius() + solid2.property.get_radius();
            Vector direction = solid2.state.position - solid1.state.position;
            
            return direction.norm2() <= min_dist * min_dist;
        }
        else if (solid2.property.shape == SQUARE)
        {
            
        }
    }
    if (solid1.property.shape == SQUARE)
    {
        if (solid2.property.shape == CIRCLE)
        {
            float min_dist = solid1.property.get_radius() + solid2.property.get_radius();
            Vector direction = solid2.state.position - solid1.state.position;
            
            return direction.norm2() <= min_dist * min_dist;
        }
        else if (solid2.property.shape == SQUARE)
        {
            
        }
    }
    
    return false;
}

void Solid::solve_collision(Solid& solid1, Solid& solid2)
{
    if (solid1.property.shape == CIRCLE)
    {
        if (solid2.property.shape == CIRCLE)
        {
            Vector direction = solid2.state.position - solid1.state.position;
            
            float min_dist = solid1.property.get_radius() + solid2.property.get_radius();
            float dist = direction.norm();
            
            direction /= dist;
            direction *= min_dist - dist;
            
            float total_inv_mass = solid1.property.inv_mass + solid2.property.inv_mass;
            
            solid1.state.position -= (solid1.property.inv_mass / total_inv_mass) * direction;
            solid2.state.position += (solid2.property.inv_mass / total_inv_mass) * direction;
        }
    }
}

}
