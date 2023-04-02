#ifndef Math_hpp
#define Math_hpp

#include <cmath>
#include <vector>
#include <random>
#include <iostream>

#include <SFML/Graphics.hpp>

namespace sp
{

struct Vector
{
    float x;
    float y;
    
    static const Vector Zero;
    
    Vector()                    {this->x = 0; this->y = 0;}
    Vector(float x, float y)    {this->x = x; this->y = y;}
    
    sf::Vector2f to_sfml() const
    {
        return sf::Vector2f(this->x, this->y);
    }
    
    float norm()
    {
        return std::sqrt(x*x + y*y);
    }
    
    float norm2()
    {
        return x*x + y*y;
    }
    
    void normalise()
    {
        float norm = this->norm();
        this->x /= norm;
        this->y /= norm;
    }
    
    void operator+=(const Vector& v)
    {
        this->x += v.x;
        this->y += v.y;
    }
    
    void operator-=(const Vector& v)
    {
        this->x -= v.x;
        this->y -= v.y;
    }
    
    void operator*=(float mult)
    {
        this->x *= mult;
        this->y *= mult;
    }
    
    void operator/=(float mult)
    {
        this->x /= mult;
        this->y /= mult;
    }
    
    
    friend Vector operator+(const Vector& u, const Vector& v)
    {
        return Vector(u.x + v.x, u.y + v.y);
    }
    
    friend Vector operator-(const Vector& u, const Vector& v)
    {
        return Vector(u.x - v.x, u.y - v.y);
    }
    
    friend Vector operator*(float mult, const Vector& v)
    {
        return Vector(mult * v.x, mult * v.y);
    }
};

struct Tranform
{
    Vector translation;
    float cos;
    float sin;
    
    Tranform(Vector t, float angle)
    {
        this->translation = t;
        this->cos = std::cos(angle);
        this->sin = std::sin(angle);
    }
};

struct BoundingBox
{
    float x_min;
    float x_max;
    float y_min;
    float y_max;
    
    float get_width()
    {
        return x_max - x_min;
    }
    
    float get_height()
    {
        return y_max - y_min;
    }
};

class Random
{
public:
    static float Uniform(float inf, float sup)
    {
        return std::uniform_real_distribution<float>(inf, sup)(re);
    }
    
    static int Uniform(int inf, int sup)
    {
        return std::uniform_int_distribution<int>(inf, sup)(re);
    }
    
    static Vector Uniform(const BoundingBox& bb)
    {
        float x = std::uniform_real_distribution<float>(bb.x_min, bb.x_max)(re);
        float y = std::uniform_real_distribution<float>(bb.y_min, bb.y_max)(re);
        return Vector(x, y);
    }
    
private:
    Random(){}
    
    static std::random_device rd;
    static std::default_random_engine re;
};

}

#endif /* Math_hpp */
