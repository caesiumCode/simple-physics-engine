#ifndef Application_hpp
#define Application_hpp

#include <SFML/Graphics.hpp>

#include "World.hpp"

class Application
{
public:
    Application();
    
    void initialise();
    void run();
    
private:
    void handle_events();
    void draw();
    
private:
    // Physics objects
    sp::World world;
    
    // Timing
    const sf::Time MIN_FRAME_TIME = sf::seconds(1.f/60.f);
    sf::Clock clock_frame;
    sf::Clock clock_physics;
    
    // Rendering objects
    sf::RenderWindow window;
    sf::Event event;
    sf::Transform physics2render;
    
    std::vector<sf::Color> colors;
};

#endif /* Application_hpp */
