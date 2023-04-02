#include "Application.hpp"

Application::Application()
{
    window.create(sf::VideoMode(2000, 1500), "Simple Physics Library Demo");
}

void Application::initialise()
{
    sp::BoundingBox borders = {0, 20, 0, 15};
    world.create(borders.x_min, borders.x_max, borders.y_min, borders.y_max);
    world.add_circle({0, 0}, 0.5);
    world.get_solid(0).set_static(true);
    colors.push_back(sf::Color::Red);
    
    float width = window.getSize().x;
    float height = window.getSize().y;
    
    float scale_x = width / (borders.x_max - borders.x_min);
    float scale_y = height / (borders.y_max - borders.y_min);
    float scale = 0.8f * std::min(scale_x, scale_y);
    
    physics2render = sf::Transform::Identity;
    physics2render.translate(-borders.x_min, -borders.y_min);
    physics2render.scale(scale, -scale);
    physics2render.translate(0, -borders.y_max);
    
    for (int i = 0; i < 20; i++)
    {
        world.add_circle(sp::Random::Uniform(borders), sp::Random::Uniform(0.1f, 1.f));
        colors.push_back(sf::Color(sp::Random::Uniform(0, 255), sp::Random::Uniform(0, 255), sp::Random::Uniform(0, 255)));
    }
    
    for (int i = 0; i < 5; i++)
    {
        world.add_square(sp::Random::Uniform(borders), sp::Random::Uniform(0.1f, 1.f));
        colors.push_back(sf::Color(sp::Random::Uniform(0, 255), sp::Random::Uniform(0, 255), sp::Random::Uniform(0, 255)));
    }
}

void Application::run()
{    
    while (window.isOpen())
    {
        // Frame timing
        clock_frame.restart();
        
        handle_events();
        
        // Update physics
        float dt = clock_physics.restart().asSeconds();
        world.update(dt);

        window.clear();
        draw();
        window.display();
        
        // Frame timing
        sf::sleep(MIN_FRAME_TIME - clock_frame.restart());
    }
}


void Application::handle_events()
{
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed) window.close();
        
        else if (event.type == sf::Event::KeyPressed)
        {
            switch (event.key.code)
            {
                default:
                    break;
            }
        }
    }
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))     world.get_solid(0).step({-0.1, 0});
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))    world.get_solid(0).step({0.1, 0});
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))     world.get_solid(0).step({0, -0.1});
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))       world.get_solid(0).step({0, 0.1});
}

void Application::draw()
{
    sp::BoundingBox borders = world.get_borders();
    sf::RectangleShape border_entity;
    border_entity.setSize(sf::Vector2f(borders.get_width(), borders.get_height()));
    border_entity.setPosition(0, 0);
    border_entity.setFillColor(sf::Color(58, 68, 77));
    
    window.draw(border_entity, physics2render);
    
    for (int i = 0; i < world.get_solids().size(); i++)
    {
        const sp::Solid& solid = world.get_solids()[i];
        
        if (solid.get_property().shape == sp::CIRCLE)
        {
            sf::CircleShape entity;
            entity.setRadius(solid.get_property().get_radius());
            entity.setPosition(solid.get_state().position.x, solid.get_state().position.y);
            entity.setFillColor(colors[i]);
            entity.setOutlineThickness(0.05);
            entity.setOutlineColor(sf::Color::White);
            entity.setOrigin(entity.getRadius(), entity.getRadius());
            
            window.draw(entity, physics2render);
        }
        else if (solid.get_property().shape == sp::SQUARE)
        {
            sf::ConvexShape entity(4);
            
            sf::Vector2f position;
            
            float half_side = solid.get_property().get_radius();
            float side = 2 * half_side;
            
            sf::Vector2f pos;
            
            for (int i = 0; i < 4; i++)
            {
                pos = solid.get_property().vertices[i].to_sfml();
                entity.setPoint(i, pos);
            }
            
            entity.setPosition(solid.get_state().position.to_sfml());
            entity.setFillColor(colors[i]);
            entity.setOutlineThickness(0.05);
            entity.setOutlineColor(sf::Color::White);
            window.draw(entity, physics2render);
        }
    }
}
