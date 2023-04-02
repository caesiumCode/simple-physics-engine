#ifndef Solid_hpp
#define Solid_hpp

#include "Math.hpp"

namespace sp {

enum Shape
{
    CIRCLE,
    SQUARE
};

struct Property
{
    Shape shape;
    bool is_static;
    std::vector<Vector> vertices;
    
    float inv_mass;
    float restitution;
    
    Property()
    {
        shape = CIRCLE;
        is_static = false;
        vertices.clear();
        
        inv_mass = 1.f;
        restitution = 0.5f;
    }
    
    float get_radius() const
    {
        return std::abs(vertices[0].x);
    }
};

struct State
{
    Vector position;
    Vector velocity;
    
    float angle;
    float angular_velocity;
    
    State()
    {
        position = Vector::Zero;
        velocity = Vector::Zero;
        
        angle = 0;
        angular_velocity = 0;
    }
};

class Solid
{
public:
    
public:
    Solid();
    
    void create_circle(float radius);
    void create_square(float side);
    
    void set_position(Vector position);
    void set_static(bool state);
    
    const Property& get_property() const;
    const State& get_state() const;
    
    void step(Vector amount);
    
    static bool check_collision(const Solid& solid1, const Solid& solid2);
    static void solve_collision(Solid& solid1, Solid& solid2);
    
private:
    Property property;
    State state;
};

}

#endif /* Solid_hpp */
